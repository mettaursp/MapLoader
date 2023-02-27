#include "ArchiveReader.h"

template <typename T>
void forEachFile(const fs::path& path, bool recursiveSearch, const T& callback)
{
	for (auto& file : fs::directory_iterator(path))
	{
		if (file.is_directory())
		{
			if (recursiveSearch)
				forEachFile(file.path(), true, callback);

			continue;
		}

		callback(file.path());
	}
}

namespace Archive
{
	ArchiveReader::ArchiveReader(const fs::path& path, bool preindexAll)
	{
		Load(path, preindexAll);
	}

	void ArchiveReader::Load(const fs::path& rawPath, bool preindexAll)
	{
		fs::path path = SanitizePath(rawPath);

		if (!fs::is_directory(path))
			return;

		ArchivePath = path;

		if (!preindexAll)
			return;

		forEachFile(path, true, [this](const fs::path& path)
			{
				if (path.extension() == ".m2h")
				{
					fs::path sanitized = SanitizePath(path);
					size_t archiveSize = ArchivePath.native().size() + 1;
					size_t sanitizedSize = sanitized.native().size();

					if (archiveSize < sanitizedSize)
					{
						GetArchivePath(sanitized.c_str() + archiveSize, true);
					}
				}
			}
		);
	}

	ArchiveReader::Path ArchiveReader::GetRootPath()
	{
		return GetDefaultPath("", nullptr);
	}

	fs::path ArchiveReader::SanitizePath(const fs::path& path)
	{
		size_t pathSize = path.native().size();

		std::wstring out;
		out.resize(pathSize);

		size_t skip = 0;
		bool lastWasSeparator = false;
		const fs::path::value_type* pathString = path.c_str();
		size_t i = 0;

		for (i; i < pathSize; ++i)
		{
			auto character = pathString[i];

			bool isSeparator = character == '\\' || character == '/';

			if (isSeparator && lastWasSeparator)
			{
				++skip;
				continue;
			}

			if (character >= 'A' && character <= 'Z')
				character += 'a' - 'A';

			out[i - skip] = isSeparator ? '/' : character;

			lastWasSeparator = isSeparator;
		}

		if (lastWasSeparator)
			++skip;

		out.resize(i - skip);

		return out;
	}

	ArchiveReader::Path ArchiveReader::GetPath(const fs::path& rawPath, bool indexIfNotLoaded)
	{
		if (ArchivePath.empty())
			return GetDefaultPath("", nullptr);

		fs::path path = SanitizePath(rawPath);

		if (fs::is_regular_file(ArchivePath / path))
		{
			if (path.has_extension())
			{
				fs::path extension = path.extension();

				if (extension == ".m2d" || extension == ".m2h")
				{
					return GetArchivePath(path, indexIfNotLoaded);
				}
			}

			return GetDefaultPath(path, nullptr);
		}

		return GetArchivePath(path, indexIfNotLoaded);
	}

	ArchiveReader::Archive* ArchiveReader::FindArchive(const fs::path& path)
	{
		const fs::path::value_type* pathString = path.c_str();

		for (Archive& archive : Archives)
		{
			const fs::path::value_type* archivePath = archive.Path.c_str();

			if (wcsncmp(pathString, archivePath, archive.Path.native().size()) == 0)
			{
				return &archive;
			}
		}

		return nullptr;
	}

	ArchiveReader::Path ArchiveReader::GetArchivePath(const fs::path& path, bool indexIfNotLoaded)
	{
		Archive* archive = FindArchive(path);

		if (archive == nullptr)
		{
			if (fs::is_regular_file(ArchivePath / path))
			{
				fs::path subPath = path;
				Archives.push_back({ subPath.replace_extension("") });

				archive = &Archives.back();
			}
			else
			{
				bool hasExtension = path.has_extension();
				fs::path subPath;
				fs::path archivePath;

				size_t pathSize = path.native().size();
				const fs::path::value_type* pathString = path.c_str();

				for (size_t i = pathSize; i > 0; --i)
				{
					if (i == pathSize && !hasExtension)
					{
						fs::path subPath = pathString;
						subPath += L".m2d";

						if (fs::is_regular_file(ArchivePath / subPath))
						{
							Archives.push_back({ pathString });

							archive = &Archives.back();

							break;
						}
					}

					if (pathString[i - 1] == '/' && i > 1)
					{
						std::wstring subPathString(pathString, i - 1);
						fs::path subPath = subPathString + L".m2d";

						if (fs::is_regular_file(ArchivePath / subPath))
						{
							Archives.push_back({ subPathString });

							archive = &Archives.back();

							break;
						}
					}
				}
			}
		}

		if (archive == nullptr)
		{
			return GetDefaultPath(path, archive);
		}

		if (indexIfNotLoaded && (archive->Parser == nullptr || !archive->Parser->IsOpen()))
		{
			if (archive->Parser == nullptr)
			{
				archive->Parser = std::make_unique<ArchiveParser>();
			}

			fs::path parserPath = archive->Path;

			parserPath += ".m2h";

			archive->Parser->Load(ArchivePath / parserPath);
		}

		const fs::path::value_type* pathString = path.c_str() + archive->Path.native().size();

		if (pathString[0] == '/')
			pathString++;

		fs::path internalPath = pathString;

		if (archive->Parser == nullptr || !archive->Parser->HasPath(internalPath))
		{
			return { this, nullptr, path, std::move(internalPath) };
		}

		bool isFile = archive->Parser->HasFile(internalPath);
		size_t index = (size_t)-1;

		if (isFile)
		{
			index = archive->Parser->GetFileIndex(internalPath);
		}
		else
		{
			index = archive->Parser->GetDirectoryIndex(internalPath);
		}

		return { this, archive->Parser.get(), path, std::move(internalPath), index, isFile };
	}

	ArchiveReader::Path ArchiveReader::GetDefaultPath(const fs::path& path, Archive* archive)
	{
		return { this, archive != nullptr ? archive->Parser.get() : nullptr, path };
	}

	ArchiveReader::Path ArchiveReader::GetDefaultParserPath(const fs::path& path, ArchiveParser* parser)
	{
		return { this, parser, path };
	}

	ArchiveReader::Path::Path(ArchiveReader* reader, ArchiveParser* parser, const fs::path& fullPath, const fs::path& archivePath, size_t index, bool referencesFile) :
		Reader(reader), Parser(parser), FullPath(fullPath), ArchivePath(archivePath), Index(index), ReferencesFile(referencesFile)
	{}

	bool ArchiveReader::Path::Loaded() const
	{
		if (Parser == nullptr)
			return false;

		if (Index == (size_t)-1 && !ArchivePath.empty())
			return false;

		if (!Parser->IsOpen())
			return false;

		return true;
	}

	bool ArchiveReader::Path::ArchiveLoaded() const
	{
		if (Parser == nullptr)
			return false;

		return Parser->IsOpen();
	}

	bool ArchiveReader::Path::IsFile() const
	{
		return Loaded() && ReferencesFile;
	}

	bool ArchiveReader::Path::IsDirectory() const
	{
		return Loaded() && !ReferencesFile;
	}

	void ArchiveReader::Path::Read(std::string& output) const
	{
		if (!IsFile())
			return;

		Parser->ReadFile(Index, output);
	}

	ArchiveReader::Path ArchiveReader::Path::Child(const std::string& child) const
	{
		return Reader->GetPath(FullPath / child);
	}

	ArchiveReader::Path ArchiveReader::Path::ChildFile(size_t index) const
	{
		if (!IsDirectory())
			return Reader->GetDefaultParserPath(FullPath, Parser);

		size_t childFile = Parser->GetChildFile(Index, index);

		if (childFile == (size_t)-1)
			return Reader->GetDefaultParserPath(FullPath, Parser);

		const fs::path& path = Parser->GetFilePath(childFile);

		return { Reader, Parser, SanitizePath(FullPath / path.filename()), path, childFile, true };
	}

	ArchiveReader::Path ArchiveReader::Path::ChildDirectory(size_t index) const
	{
		if (!IsDirectory())
			return Reader->GetDefaultParserPath(FullPath, Parser);

		size_t childDirectory = Parser->GetChildDirectory(Index, index);

		if (childDirectory == (size_t)-1)
			return Reader->GetDefaultParserPath(FullPath, Parser);

		const fs::path& path = Parser->GetDirectoryPath(childDirectory);

		return { Reader, Parser, SanitizePath(FullPath / path.filename()), path, childDirectory, false };
	}

	size_t ArchiveReader::Path::ChildFiles() const
	{
		if (!IsDirectory())
			return 0;

		return Parser->GetChildFiles(Index);
	}

	size_t ArchiveReader::Path::ChildDirectories() const
	{
		if (!IsDirectory())
			return 0;

		return Parser->GetChildDirectories(Index);
	}
}