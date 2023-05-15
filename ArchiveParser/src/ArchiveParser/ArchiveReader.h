#pragma once

#include "ArchiveParser.h"

#include <functional>

namespace Archive
{
	class ArchiveReader
	{
	public:
		struct Path;

		ArchiveReader() {}
		ArchiveReader(const fs::path& path, bool preindexAll = false);

		void Load(const fs::path& path, bool preindexAll = false);

		const fs::path& GetPath() const { return ArchivePath; }
		Path GetRootPath();
		Path GetPath(const fs::path& path, bool indexIfNotLoaded = true);
		bool IsValid() const { return !ArchivePath.empty(); }
		size_t GetTotalBytesRead() const;
		size_t GetTotalDiskBytesRead() const;

		struct Path
		{
			Path() {}
			Path(
				ArchiveReader* reader,
				ArchiveParser* parser = nullptr,
				const fs::path& fullPath = {},
				const fs::path& archivePath = {},
				size_t index = (size_t)-1,
				bool referencesFile = false
			);

			bool Loaded() const;
			bool ArchiveLoaded() const;
			bool IsFile() const;
			bool IsDirectory() const;
			bool IsInArchive() const { return Parser != nullptr; }

			void Read(std::string& output) const;

			Path Child(const std::string& child) const;
			Path ChildFile(size_t index) const;
			Path ChildDirectory(size_t index) const;
			size_t ChildFiles() const;
			size_t ChildDirectories() const;

			ArchiveReader& GetReader() const { return *Reader; }
			const fs::path& GetPath() const { return FullPath; }
			const fs::path& GetArchivePath() const { return ArchivePath; }

			friend class ArchiveReader;

		private:
			ArchiveReader* const Reader = nullptr;
			ArchiveParser* const Parser = nullptr;
			const fs::path FullPath;
			const fs::path ArchivePath;
			const size_t Index = (size_t)-1;
			const bool ReferencesFile = false;
		};

		static fs::path SanitizePath(const fs::path& path);

	private:
		struct Archive
		{
			fs::path Path;
			std::unique_ptr<ArchiveParser> Parser;
		};

		fs::path ArchivePath;
		std::vector<Archive> Archives;

		Archive* FindArchive(const fs::path& path);
		Path GetArchivePath(const fs::path& path, bool indexIfNotLoaded);
		Path GetDefaultPath(const fs::path& path, Archive* archive);
		Path GetDefaultParserPath(const fs::path& path, ArchiveParser* parser);
	};

	typedef ArchiveReader::Path ArchivePath;
}