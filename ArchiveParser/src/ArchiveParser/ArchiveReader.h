#pragma once

#include "ArchiveParser.h"

#include <functional>

namespace Archive
{
	class ArchiveReader
	{
	public:
		struct Path;

		bool Quiet = false;

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
			const ArchiveParser::FileEntry& GetEntry() const { return Parser->GetFileEntry(Index); }

			friend class ArchiveReader;

		private:
			ArchiveReader* Reader = nullptr;
			ArchiveParser* Parser = nullptr;
			fs::path FullPath;
			fs::path ArchivePath;
			size_t Index = (size_t)-1;
			bool ReferencesFile = false;
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

	template <typename T>
	void ForEachFile(const ArchivePath& path, bool recursiveSearch, const T& callback)
	{
		size_t childFiles = path.ChildFiles();
		size_t childDirectories = path.ChildDirectories();

		for (size_t i = 0; i < childFiles; ++i)
			callback(path.ChildFile(i));

		if (recursiveSearch)
			for (size_t i = 0; i < childDirectories; ++i)
				ForEachFile(path.ChildDirectory(i), recursiveSearch, callback);
	}
}