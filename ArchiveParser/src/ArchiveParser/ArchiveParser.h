#pragma once

#include <filesystem>
#include <fstream>
#include <unordered_map>

#include "PackTraits.h"

namespace fs = std::filesystem;

struct evp_cipher_ctx_st;

size_t decompressionBufferSize(size_t expectedSize);

namespace Archive
{
	struct DecryptionContext
	{
		evp_cipher_ctx_st* Decryptor = nullptr;
		std::vector<unsigned char> Decrypted;
		std::vector<unsigned char> DecodedBlockData;
	};

	class ArchiveParser
	{
	public:
		ArchiveParser();
		ArchiveParser(const fs::path& path);
		~ArchiveParser();

		void Load(const fs::path& path, bool cacheHeaderBuffer = false);
		void Load(bool cacheHeaderBuffer = false);
		void Unload();

		const fs::path& GetArchivePath() const { return ArchivePath; }
		const fs::path& GetHeaderPath() const { return HeaderPath; }
		bool IsOpen() const;
		bool IsValidPath() const;
		void ReleaseUnused();
		bool HasDirectory(const fs::path& path) const;
		bool HasFile(const fs::path& path) const;
		bool HasPath(const fs::path& path) const;
		size_t FileCount() { return Files.size(); }
		size_t DirectoryCount() { return Directories.size(); }
		size_t GetFileIndex(const fs::path& path) const;
		size_t GetDirectoryIndex(const fs::path& path) const;
		size_t GetChildFiles(size_t index) const;
		size_t GetChildDirectories(size_t index) const;
		size_t GetChildFile(size_t directoryIndex, size_t index) const;
		size_t GetChildDirectory(size_t directoryIndex, size_t index) const;
		size_t GetTotalBytesRead() const { return TotalBytesRead; }
		size_t GetTotalDiskBytesRead() const { return TotalDiskBytesRead; }
		const fs::path& GetFilePath(size_t index) const;
		const fs::path& GetDirectoryPath(size_t index) const;

		bool ReadFile(const fs::path& path, std::string& contents);
		bool ReadFile(size_t index, std::string& contents);

	private:
		struct DirectoryEntry;
	public:

		struct FileEntry
		{
			size_t Index = (size_t)-1;
			size_t Location = (size_t)-1;
			fs::path Path;
			size_t EncodedSize = 0;
			size_t CompressedSize = 0;
			size_t Size = 0;
			size_t Offset = 0;
			CompressionType Compression = CompressionType::None;
			DirectoryEntry* Parent = nullptr;
		};

		const FileEntry& GetFileEntry(size_t index) { return Files[index]; }

	private:
		struct DirectoryEntry
		{
			size_t Index = (size_t)-1;
			DirectoryEntry* Parent = nullptr;
			fs::path Path;
			std::unordered_map<fs::path, FileEntry*> Files;
			std::unordered_map<fs::path, DirectoryEntry*> Directories;
			std::vector<size_t> DirectoryIndices;
			std::vector<size_t> FileIndices;
		};

		std::ifstream ArchiveFile;
		fs::path ArchivePath;
		fs::path HeaderPath;
		PackVersion Version = PackVersion::MS2F;
		std::string ArchiveBuffer;
		std::string FileListBuffer;

		DirectoryEntry RootDirectory;
		std::vector<FileEntry> Files;
		std::vector<DirectoryEntry> Directories;
		std::unordered_map<size_t, FileEntry*> FileIndexMap;
		std::unordered_map<fs::path, DirectoryEntry*> DirectoryMap;
		std::unordered_map<fs::path, FileEntry*> FileMap;
		DecryptionContext Context;

		size_t TotalBytesRead = 0;
		size_t TotalDiskBytesRead = 0;
		
		bool ProcessHeader();
		void ParseFileList();

		bool ReadFile(const FileEntry& file, std::string& contents);

		template <typename Traits>
		void DumpHeaderStream();

		template <typename Traits>
		bool DumpArchiveStream(const FileEntry& file, std::string& contents);
	};
}