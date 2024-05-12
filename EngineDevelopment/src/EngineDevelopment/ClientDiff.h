#pragma once

#include <string>
#include <filesystem>
#include <vector>

#include <ArchiveParser/ArchiveReader.h>

namespace fs = std::filesystem;

struct ClientVisitor
{
	Archive::ArchiveReader Reader;
	fs::path ClientPath;

	bool IsFile = false;
	bool IsEncrypted = false;
	std::string Hash;
	std::string Contents;

	fs::path LastEntry;
	Archive::ArchiveReader::Path LastEntryArchive;
	fs::path LastEntryDirectory;
	bool LastEntryWasFile = false;
	size_t LastDepth = 1;

	struct ClientSubPath
	{
		size_t Index = 0;
		fs::path Path;
		std::vector<fs::path> SubPaths;
	};

	std::vector<ClientSubPath> ClientPathStack;

	struct ArchiveSubPath
	{
		size_t Index = 0;
		Archive::ArchiveReader::Path Path;
		std::vector<Archive::ArchiveReader::Path> SubPaths;
	};

	fs::path ArchivePath;

	std::vector<ArchiveSubPath> ArchivePathStack;

	void StepArchive(bool quiet = false);
	void EnterArchive(const fs::path& m2dPath, bool quiet = false);
	void StepDirectory(bool quiet = false);
	void EnterClient(const fs::path& clientPath, bool quiet = false);
	void Step(bool quiet = false);
	void DumpClient(const fs::path& clientPath);
	void LoadFile();
	void LoadFileRaw();
	size_t GetDepth() const;
};

void dumpClientData(const fs::path& clientPath);
bool diffClientData(const fs::path& clientPath1, const fs::path& clientPath2);
int clientDiffMain(int argc, char** argv);