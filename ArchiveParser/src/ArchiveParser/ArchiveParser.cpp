#include "ArchiveParser.h"

#include <fstream>
#include <map>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/files.h>
#include <cryptopp/base64.h>
#include <cryptopp/zlib.h>
#include <cassert>

#include "PackTraits.h"
#include "ParserUtils.h"

/*
* Using keys & parsing strategy from https://github.com/Wunkolo/Maple2Tools & http://forum.xentax.com/viewtopic.php?f=10&t=18090
*/

void DecryptStream(const unsigned char* encoded, uint64_t encodedSize, const uint8_t* iv, const uint8_t* key, void* decoded, uint64_t decodedSize, bool isCompressed)
{
	CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption decryptor;

	decryptor.SetKeyWithIV(key, 32, iv);

	if (isCompressed)
	{
		CryptoPP::ArraySource(
			static_cast<const CryptoPP::byte*>(encoded),
			encodedSize, true,
			new CryptoPP::Base64Decoder(
				new CryptoPP::StreamTransformationFilter(
					decryptor,
					new CryptoPP::ZlibDecompressor(
						new CryptoPP::ArraySink(static_cast<CryptoPP::byte*>(decoded), decodedSize)
					)
				)
			)
		);
	}
	else
	{
		CryptoPP::ArraySource(
			static_cast<const CryptoPP::byte*>(encoded),
			encodedSize, true,
			new CryptoPP::Base64Decoder(
				new CryptoPP::StreamTransformationFilter(
					decryptor,
					new CryptoPP::ArraySink(static_cast<CryptoPP::byte*>(decoded), decodedSize)
				)
			)
		);
	}
}

namespace Archive
{
	void ArchiveParser::ParseFileList()
	{
		size_t current = 0;

		Files.clear();
		FileMap.clear();
		Directories.clear();
		DirectoryMap.clear();

		std::string lastDirectory;
		std::string path;
		std::string subPath;

		for (size_t i = 0; i < FileListBuffer.size(); ++i)
		{
			for (i; i < FileListBuffer.size() && (FileListBuffer[i] == '\n' || FileListBuffer[i] == '\r'); ++i);

			if (i >= FileListBuffer.size()) break;

			size_t index = 0;

			for (i; i < FileListBuffer.size() && FileListBuffer[i] != ','; ++i)
			{
				index = index * 10 + (FileListBuffer[i] - '0');
			}

			assert(FileListBuffer[i] == ',');

			++i;

			path.clear();

			size_t j = 0;
			for (j = 0; i + j < FileListBuffer.size() && FileListBuffer[i + j] != ',' && FileListBuffer[i + j] != '\n' && FileListBuffer[i + j] != '\r'; ++i)
				path.push_back(FileListBuffer[i + j]);

			if (FileListBuffer[i + j] == ',')
			{
				i += j + 1;

				path.clear();

				for (j = 0; i + j < FileListBuffer.size() && FileListBuffer[i + j] != '\r' && FileListBuffer[i + j] != '\n'; ++j)
					path.push_back(FileListBuffer[i + j]);
			}


			assert(FileListBuffer[i + j] == '\r' || FileListBuffer[i + j] == '\n');

			for (size_t i = 0; i < path.size(); ++i)
				if (path[i] >= 'A' && path[i] <= 'Z')
					path[i] += 'a' - 'A';

			Files.push_back({});

			FileEntry& file = Files.back();
			file.Index = index;
			file.Location = Files.size() - 1;
			file.Path = path;

			FileMap.insert(std::make_pair(file.Path, nullptr));

			i += j;

			size_t parentDir = path.size();

			for (parentDir; parentDir > 0 && path[parentDir - 1] != '/'; --parentDir);

			path.resize(parentDir);
			subPath.resize(parentDir + 1);

			if (parentDir == 0 || lastDirectory == path)
			{
				if (parentDir > 0)
					file.Parent = (DirectoryEntry*)-1ll;

				continue;
			}

			int level = 0;

			for (size_t i = 0; i < parentDir; ++i)
			{
				subPath[i] = path[i];

				if (path[i] == '/' && strncmp(lastDirectory.c_str(), path.c_str(), i) != 0)
				{
					subPath.resize(i);

					if (DirectoryMap.find(subPath) != DirectoryMap.end()) continue;

					Directories.push_back({});

					DirectoryEntry& directory = Directories.back();
					directory.Path = subPath;
					directory.Index = Directories.size() - 1;

					if (level > 0)
						directory.Parent = (DirectoryEntry*)-1ll;

					DirectoryMap.insert(std::make_pair(subPath, nullptr));

					subPath.resize(parentDir + 1);
					subPath[i] = '/';
				}

				if (path[i] == '/')
					++level;
			}

			if (level > 0)
				file.Parent = (DirectoryEntry*)-1ll;

			lastDirectory = std::move(path);
		}

		FileIndexMap.clear();

		for (DirectoryEntry& directory : Directories)
		{
			DirectoryMap[directory.Path] = &directory;
			DirectoryMap.insert(std::make_pair(directory.Path / "", &directory));

			if (directory.Parent == (DirectoryEntry*)-1ll)
			{
				directory.Parent = DirectoryMap[std::move(directory.Path.parent_path())];
			}
			else
			{
				directory.Parent = &RootDirectory;
			}

			directory.DirectoryIndices.reserve(directory.Directories.size());
			directory.FileIndices.reserve(directory.Files.size());
			directory.Parent->Directories.insert(std::move(std::make_pair(std::move(directory.Path.filename()), &directory)));
			directory.Parent->DirectoryIndices.push_back(directory.Index);
		}

		for (FileEntry& file : Files)
		{
			FileMap[file.Path] = &file;
			FileIndexMap.insert(std::make_pair(file.Index, &file));

			if (file.Parent == (DirectoryEntry*)-1ll)
			{
				file.Parent = DirectoryMap[std::move(file.Path.parent_path())];
			}
			else
			{
				file.Parent = &RootDirectory;
			}

			file.Parent->Files.insert(std::move(std::make_pair(std::move(file.Path.filename()), &file)));
			file.Parent->FileIndices.push_back(file.Location);
		}
	}

	template <typename Traits>
	void ArchiveParser::DumpHeaderStream()
	{
		Version = Traits::Version;

		const unsigned char* buffer = streamOf<unsigned char>(ArchiveBuffer.data()) + 4;
		typename Traits::StreamType header = *reinterpret_cast<const Traits::StreamType*>(buffer);

		buffer += sizeof(Traits::StreamType);

		FileListBuffer.clear();
		FileListBuffer.resize(header.FileListSize);

		DecryptStream(
			buffer,
			header.FileListEncodedSize,
			Traits::IV_LUT[header.FileListCompressedSize % std::extent<std::remove_cvref_t<decltype(Traits::IV_LUT)>, 0u>::value],
			Traits::Key_LUT[header.FileListCompressedSize % std::extent<std::remove_cvref_t<decltype(Traits::Key_LUT)>, 0u>::value],
			FileListBuffer.data(),
			header.FileListSize,
			header.FileListSize != header.FileListCompressedSize
		);

		buffer += header.FileListEncodedSize;

		std::map<size_t, fs::path> entries;

		Files.reserve(header.TotalFiles);
		FileMap.reserve(header.TotalFiles);

		ParseFileList();

		std::vector<typename Traits::FileHeaderType> FATable;
		FATable.resize(header.TotalFiles, typename Traits::FileHeaderType{});

		DecryptStream(
			buffer,
			header.FATEncodedSize,
			Traits::IV_LUT[header.FATCompressedSize % std::extent<std::remove_cvref_t<decltype(Traits::IV_LUT)>, 0u>::value],
			Traits::Key_LUT[header.FATCompressedSize % std::extent<std::remove_cvref_t<decltype(Traits::Key_LUT)>, 0u>::value],
			FATable.data(),
			header.TotalFiles * sizeof(Traits::FileHeaderType),
			header.FATSize != header.FATCompressedSize
		);

		for (size_t i = 0; i < FATable.size(); ++i)
		{
			const Traits::FileHeaderType& fileHeader = FATable[i];

			const auto& fileIndex = FileIndexMap.find(fileHeader.FileIndex);

			if (fileIndex == FileIndexMap.end())
				continue;

			FileEntry& file = *fileIndex->second;

			file.EncodedSize = fileHeader.EncodedSize;
			file.CompressedSize = fileHeader.CompressedSize;
			file.Size = fileHeader.Size;
			file.Offset = fileHeader.Offset;
			file.Compression = fileHeader.Compression;
		}
	}

	template <typename Traits>
	bool ArchiveParser::DumpArchiveStream(const FileEntry& file, std::string& contents)
	{
		ArchiveFile.seekg(file.Offset);

		ArchiveBuffer.clear();
		ArchiveBuffer.resize(file.EncodedSize);

		ArchiveFile.read(ArchiveBuffer.data(), file.EncodedSize);

		contents.resize(file.Size);

		DecryptStream(
			streamOf<unsigned char>(ArchiveBuffer.data()),
			file.EncodedSize,
			Traits::IV_LUT[file.CompressedSize % std::extent<std::remove_cvref_t<decltype(Traits::IV_LUT)>, 0u>::value],
			Traits::Key_LUT[file.CompressedSize % std::extent<std::remove_cvref_t<decltype(Traits::Key_LUT)>, 0u>::value],
			contents.data(),
			contents.size(),
			file.Compression != CompressionType::None || file.CompressedSize != file.Size
		);

		return true;
	}

	bool ArchiveParser::ReadFile(const FileEntry& file, std::string& contents)
	{
		contents.clear();

		if (!IsOpen()) return false;

		switch (Version)
		{
		case PackVersion::MS2F:
			return DumpArchiveStream<PackTraits<PackVersion::MS2F>>(file, contents);

		case PackVersion::NS2F:
			return DumpArchiveStream<PackTraits<PackVersion::NS2F>>(file, contents);

		case PackVersion::OS2F:
			return DumpArchiveStream<PackTraits<PackVersion::OS2F>>(file, contents);

		case PackVersion::PS2F:
			return DumpArchiveStream<PackTraits<PackVersion::PS2F>>(file, contents);

		default:
			return false;
		}

		return false;
	}

	bool ArchiveParser::ReadFile(const fs::path& path, std::string& contents)
	{
		contents.clear();

		const auto& fileIndex = FileMap.find(path.string());

		if (fileIndex == FileMap.end()) return false;

		return ReadFile(*fileIndex->second, contents);
	}

	bool ArchiveParser::ReadFile(size_t index, std::string& contents)
	{
		if (index < Files.size())
			return ReadFile(Files[index], contents);

		return false;
	}

	bool ArchiveParser::ProcessHeader()
	{
		if (!fs::exists(HeaderPath)) return false;

		std::ifstream headerFile(HeaderPath, std::ios::binary);

		if (!headerFile.is_open())
			return false;

		uintmax_t fileSize = fs::file_size(HeaderPath);

		ArchiveBuffer.clear();
		ArchiveBuffer.resize(fileSize);
		headerFile.read(ArchiveBuffer.data(), fileSize);

		if (strncmp(ArchiveBuffer.data() + 1, "S2F", 3) != 0) return false;

		char type = ArchiveBuffer[0];

		switch (type)
		{
		case 'M':
			DumpHeaderStream<PackTraits<PackVersion::MS2F>>();

			break;
		case 'N':
			DumpHeaderStream<PackTraits<PackVersion::NS2F>>();

			break;
		case 'O':
			DumpHeaderStream<PackTraits<PackVersion::OS2F>>();

			break;
		case 'P':
			DumpHeaderStream<PackTraits<PackVersion::PS2F>>();

			break;
		default:
			return false;
		}

		return true;
	}

	ArchiveParser::ArchiveParser(const fs::path& path) : FileIndexMap(), DirectoryMap(), FileMap()
	{
		Load(path);
	}

	void ArchiveParser::Load(const fs::path& path, bool cacheHeaderBuffer)
	{
		if (ArchiveFile.is_open())
		{
			Unload();
		}

		if (!fs::exists(path)) return;

		std::string extension = lower(path.extension().string());

		if (extension != ".m2d" && extension != ".m2h") return;

		if (extension == ".m2d")
		{
			ArchivePath = path;
			HeaderPath = ArchivePath;
			HeaderPath.replace_extension(".m2h");
		}

		if (extension == ".m2h")
		{
			HeaderPath = path;
			ArchivePath = HeaderPath;
			ArchivePath.replace_extension(".m2d");
		}

		if (!IsValidPath()) return;

		if (!ProcessHeader()) return;

		ArchiveFile.open(ArchivePath, std::ios::binary);

		if (!cacheHeaderBuffer)
		{
			ReleaseUnused();
		}
	}

	void ArchiveParser::Load(bool cacheHeaderBuffer)
	{
		if (ArchiveFile.is_open())
		{
			Unload();
		}

		if (!IsValidPath()) return;

		if (!ProcessHeader()) return;

		ArchiveFile.open(ArchivePath, std::ios::binary);

		if (!cacheHeaderBuffer)
		{
			ReleaseUnused();
		}
	}

	void ArchiveParser::Unload()
	{
		if (ArchiveFile.is_open())
		{
			ArchiveFile.close();

			DirectoryMap.clear();
			FileMap.clear();
			FileIndexMap.clear();
			Directories.clear();
			Files.clear();
			RootDirectory = {};
		}
	}

	bool ArchiveParser::IsOpen() const
	{
		return ArchiveFile.is_open();
	}

	bool ArchiveParser::IsValidPath() const
	{
		if (!fs::exists(HeaderPath) || !fs::exists(ArchivePath)) return false;

		if (!fs::is_regular_file(HeaderPath) || !fs::is_regular_file(ArchivePath)) return false;

		return true;
	}

	bool ArchiveParser::HasDirectory(const fs::path& path) const
	{
		return path == "" || DirectoryMap.find(path) != DirectoryMap.end();
	}

	bool ArchiveParser::HasFile(const fs::path& path) const
	{
		return FileMap.find(path) != FileMap.end();
	}

	bool ArchiveParser::HasPath(const fs::path& path) const
	{
		return HasDirectory(path) || HasFile(path);
	}

	size_t ArchiveParser::GetFileIndex(const fs::path& path) const
	{
		const auto index = FileMap.find(path);

		if (index == FileMap.end())
			return (size_t)-1;

		return index->second->Location;
	}

	size_t ArchiveParser::GetDirectoryIndex(const fs::path& path) const
	{
		const auto index = DirectoryMap.find(path);

		if (index == DirectoryMap.end())
			return (size_t)-1;

		return index->second->Index;
	}

	size_t ArchiveParser::GetChildFiles(size_t index) const
	{
		if (index < Directories.size())
			return Directories[index].Files.size();

		if (index == (size_t)-1)
			return RootDirectory.Files.size();

		return 0;
	}

	size_t ArchiveParser::GetChildDirectories(size_t index) const
	{
		if (index < Directories.size())
			return Directories[index].Directories.size();

		if (index == (size_t)-1)
			return RootDirectory.Directories.size();

		return 0;
	}

	size_t ArchiveParser::GetChildFile(size_t directoryIndex, size_t index) const
	{
		if (directoryIndex >= Directories.size() && directoryIndex != (size_t)-1)
			return (size_t)-1;

		const DirectoryEntry& directory = directoryIndex == (size_t)-1 ? RootDirectory : Directories[directoryIndex];

		if (index < directory.Files.size())
			return directory.FileIndices[index];

		return (size_t)-1;
	}

	size_t ArchiveParser::GetChildDirectory(size_t directoryIndex, size_t index) const
	{
		if (directoryIndex >= Directories.size() && directoryIndex != (size_t)-1)
			return (size_t)-1;

		const DirectoryEntry& directory = directoryIndex == (size_t)-1 ? RootDirectory : Directories[directoryIndex];

		if (index < directory.DirectoryIndices.size())
			return directory.DirectoryIndices[index];

		return (size_t)-1;
	}

	const fs::path& ArchiveParser::GetFilePath(size_t index) const
	{
		static const fs::path emptyPath = "";

		if (index >= Files.size())
			return emptyPath;

		return Files[index].Path;
	}

	const fs::path& ArchiveParser::GetDirectoryPath(size_t index) const
	{
		static const fs::path emptyPath = "";

		if (index >= Directories.size())
			return emptyPath;

		return Directories[index].Path;
	}

	void ArchiveParser::ReleaseUnused()
	{
		ArchiveBuffer.clear();
		ArchiveBuffer.shrink_to_fit();
		FileListBuffer.clear();
		FileListBuffer.shrink_to_fit();

		if (IsOpen()) return;

		Files.clear();
		Files.shrink_to_fit();
		Directories.clear();
		Directories.shrink_to_fit();
		FileIndexMap.clear();
		DirectoryMap.clear();
		FileMap.clear();
	}
}