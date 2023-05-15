#include "ArchiveParser.h"

#include <fstream>
#include <map>
#include <cassert>

#define OPENSSL_NO_SOCK

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <zlib.h>

#include "PackTraits.h"
#include "ParserUtils.h"

/*
* Using keys & parsing strategy from https://github.com/Wunkolo/Maple2Tools & http://forum.xentax.com/viewtopic.php?f=10&t=18090
*/

size_t decompressionBufferSize(size_t expectedSize)
{
	return (size_t)((float)(expectedSize) * 1.1f) + 16;
}

void DecryptStream(const unsigned char* encoded, uint64_t encodedSize, const uint8_t* iv, const uint8_t* key, void* decoded, uint64_t decodedSize, bool isCompressed, Archive::DecryptionContext& context)
{
	std::vector<unsigned char>& decrypted = context.Decrypted;
	std::vector<unsigned char>& decodedBlockData = context.DecodedBlockData;

	decrypted.resize(encodedSize);
	decodedBlockData.resize(encodedSize);

	int written = (int)decodedSize;
	int written2 = 0;

	EVP_DecodeBlock(decodedBlockData.data(), encoded, (int)encodedSize);

	EVP_CIPHER_CTX*& decryptor = context.Decryptor;
	
	if (decryptor == nullptr)
	{
		decryptor = EVP_CIPHER_CTX_new();
	}

	unsigned char* decryptedData = isCompressed ? decrypted.data() : reinterpret_cast<unsigned char*>(decoded);

	EVP_CIPHER_CTX_init(decryptor);
	int res1 = EVP_DecryptInit_ex2(decryptor, EVP_aes_256_ctr(), key, iv, NULL);
	int res2 = EVP_DecryptUpdate(decryptor, decryptedData, &written, decodedBlockData.data(), (int)encodedSize);
	int res3 = EVP_DecryptFinal_ex(decryptor, decryptedData, &written2);

	if (!isCompressed) return;

	uLongf sizeUncompressed = (uLongf)decompressionBufferSize(decodedSize);
	int result = uncompress(reinterpret_cast<Bytef*>(decoded), &sizeUncompressed, reinterpret_cast<Bytef*>(decrypted.data()), written);
	switch (result)
	{
	case Z_OK:
		
		break;
	case Z_MEM_ERROR:
		throw "unhandled zlib memory error";
		
		break;
	case Z_BUF_ERROR:
		throw "unhandled zlib buffer error";
		
		break;
		
	default:
		throw "unhandled zlib error";
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
			bool inserted = false;

			for (size_t i = 0; i < parentDir; ++i)
			{
				subPath[i] = path[i];

				bool pathMatches = path[i] == '/' && strncmp(lastDirectory.c_str(), path.c_str(), i) == 0;

				if (pathMatches && (lastDirectory.size() < i - 1 || lastDirectory[i] != '/'))
				{
					pathMatches = false;
				}

				if (path[i] == '/' && !pathMatches)
				{
					subPath.resize(i);

					if (DirectoryMap.find(subPath) != DirectoryMap.end()) continue;

					Directories.push_back({});

					DirectoryEntry& directory = Directories.back();
					directory.Path = subPath;
					directory.Index = Directories.size() - 1;
					inserted = true;

					if (level > 0)
						directory.Parent = (DirectoryEntry*)-1ll;

					DirectoryMap.insert(std::make_pair(subPath, nullptr));

					subPath.resize(parentDir + 1);
					subPath[i] = '/';
				}

				if (path[i] == '/')
					++level;
			}

			if (!inserted && lastDirectory.size() > parentDir && strncmp(lastDirectory.c_str(), path.c_str(), parentDir) != 0 && lastDirectory[parentDir] != '/')
			{
				subPath.resize(parentDir - 1);

				if (DirectoryMap.find(subPath) != DirectoryMap.end()) continue;

				Directories.push_back({});

				DirectoryEntry& directory = Directories.back();
				directory.Path = subPath;
				directory.Index = Directories.size() - 1;

				if (level > 0)
					directory.Parent = (DirectoryEntry*)-1ll;

				DirectoryMap.insert(std::make_pair(subPath, nullptr));
			}

			if (level > 0)
				file.Parent = (DirectoryEntry*)-1ll;

			lastDirectory = std::move(path);
		}

		FileIndexMap.clear();

		for (size_t i = 0; i < Directories.size(); ++i)
		{
			DirectoryEntry& directory = Directories[i];

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
			directory.Parent->Directories.insert(std::make_pair(directory.Path.filename(), &directory));
			directory.Parent->DirectoryIndices.push_back(directory.Index);
		}

		for (size_t i = 0; i < Files.size(); ++i)
		{
			FileEntry& file = Files[i];

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

			file.Parent->Files.insert(std::make_pair(file.Path.filename(), &file));
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
		FileListBuffer.resize(decompressionBufferSize(header.FileListSize));

		DecryptStream(
			buffer,
			header.FileListEncodedSize,
			Traits::IV_LUT[header.FileListCompressedSize % std::extent<std::remove_cvref_t<decltype(Traits::IV_LUT)>, 0u>::value],
			Traits::Key_LUT[header.FileListCompressedSize % std::extent<std::remove_cvref_t<decltype(Traits::Key_LUT)>, 0u>::value],
			FileListBuffer.data(),
			header.FileListSize,
			header.FileListSize != header.FileListCompressedSize,
			Context
		);

		FileListBuffer.resize(header.FileListSize);

		buffer += header.FileListEncodedSize;

		std::map<size_t, fs::path> entries;

		Files.reserve(header.TotalFiles);
		FileMap.reserve(header.TotalFiles);

		ParseFileList();

		std::vector<typename Traits::FileHeaderType> FATable;
		FATable.resize(decompressionBufferSize(header.TotalFiles), typename Traits::FileHeaderType{});

		DecryptStream(
			buffer,
			header.FATEncodedSize,
			Traits::IV_LUT[header.FATCompressedSize % std::extent<std::remove_cvref_t<decltype(Traits::IV_LUT)>, 0u>::value],
			Traits::Key_LUT[header.FATCompressedSize % std::extent<std::remove_cvref_t<decltype(Traits::Key_LUT)>, 0u>::value],
			FATable.data(),
			header.TotalFiles * sizeof(Traits::FileHeaderType),
			header.FATSize != header.FATCompressedSize,
			Context
		);

		FATable.resize(header.TotalFiles);

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

		contents.resize(decompressionBufferSize(file.Size));

		TotalBytesRead += file.Size;
		TotalDiskBytesRead += file.CompressedSize;

		DecryptStream(
			streamOf<unsigned char>(ArchiveBuffer.data()),
			file.EncodedSize,
			Traits::IV_LUT[file.CompressedSize % std::extent<std::remove_cvref_t<decltype(Traits::IV_LUT)>, 0u>::value],
			Traits::Key_LUT[file.CompressedSize % std::extent<std::remove_cvref_t<decltype(Traits::Key_LUT)>, 0u>::value],
			contents.data(),
			contents.size(),
			file.Compression != CompressionType::None || file.CompressedSize != file.Size,
			Context
		);

		contents.resize(file.Size);

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

		TotalBytesRead += fileSize;
		TotalDiskBytesRead += fileSize;

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

	ArchiveParser::ArchiveParser()
	{
	}

	ArchiveParser::ArchiveParser(const fs::path& path) : FileIndexMap(), DirectoryMap(), FileMap()
	{
		Load(path);
	}

	ArchiveParser::~ArchiveParser()
	{
		if (Context.Decryptor != nullptr)
			EVP_CIPHER_CTX_free(Context.Decryptor);

		Context.Decryptor = nullptr;
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