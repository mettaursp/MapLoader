#include <filesystem>
#include <string>
#include <fstream>
#include <iostream>

#include <openssl/evp.h>
#include <ArchiveParser/ArchiveReader.h>

namespace fs = std::filesystem;

void loadFile(const fs::path& filePath, std::string& contents)
{
	if (!fs::is_regular_file(filePath))
	{
		std::cout << "path '" << filePath << "' is not a file" << std::endl;

		throw "not a file";
	}

	std::ifstream file(filePath);

	std::streampos start = file.tellg();
	file.seekg(0, std::ios::end);
	std::streampos length = file.tellg() - start;
	file.seekg(start);
	contents.resize(length);
	file.read(&contents[0], length);
}

void computeMD5(const std::string& contents, std::string& hash)
{
	EVP_MD_CTX* mdContext = EVP_MD_CTX_new();
	unsigned int md5Length = EVP_MD_size(EVP_md5());

	hash.resize(md5Length);

	EVP_DigestInit_ex(mdContext, EVP_md5(), NULL);
	EVP_DigestUpdate(mdContext, reinterpret_cast<const unsigned char*>(contents.data()), (unsigned int)contents.size());
	EVP_DigestFinal_ex(mdContext, reinterpret_cast<unsigned char*>(hash.data()), &md5Length);
	EVP_MD_CTX_free(mdContext);
}

void convertHashToHex(std::string& hash)
{
	size_t size = hash.size();

	hash.resize(size * 2);

	for (size_t i = size; i > 0; --i)
	{
		unsigned char high = (unsigned char)hash[i - 1] >> 4;
		unsigned char low = (unsigned char)hash[i - 1] & 0xF;

		char highDigit = high < 10 ? '0' + high : 'a' + high - 10;
		char lowDigit = low < 10 ? '0' + low : 'a' + low - 10;

		hash[2 * (i - 1)] = highDigit;
		hash[2 * (i - 1) + 1] = lowDigit;
	}
}

void computeMD5Hex(const std::string& contents, std::string& hash)
{
	computeMD5(contents, hash);
	convertHashToHex(hash);
}

int comparePaths(const fs::path& left, const fs::path& right)
{
	const std::wstring& leftString = left.native();
	const std::wstring& rightString = right.native();

	const wchar_t* leftStr = leftString.c_str();
	const wchar_t* rightStr = rightString.c_str();

	size_t length = std::min(leftString.size(), rightString.size());

	for (size_t i = 0; i < length; ++i)
	{
		if (leftStr[i] < rightStr[i])
		{
			// (left < right) == false
			return -1;
		}

		if (leftStr[i] > rightStr[i])
		{
			// (left < right) == false
			return 1;
		}
	}

	size_t leftLength = leftString.size();
	size_t rightLength = rightString.size();

	if (leftLength < rightLength)
	{
		return -1;
	}

	if (leftLength > rightLength)
	{
		return 1;
	}

	return 0;
}

bool pathLessThan(const fs::path& left, const fs::path& right)
{
	return comparePaths(left, right) < 0;
}

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

fs::path sanitize(const fs::path& path)
{
	std::wstring output = path;

	std::replace(output.begin(), output.end(), '\\', '/');

	return output;
}

void ClientVisitor::LoadFile()
{
	Hash.clear();

	IsFile = LastEntryWasFile;
	IsEncrypted = false;

	if (!IsFile)
	{
		return;
	}

	if (LastEntryDirectory == "")
	{
		LastEntryArchive.Read(Contents);
	}
	else
	{
		loadFile(LastEntryDirectory, Contents);
	}
}

void ClientVisitor::LoadFileRaw()
{
	IsFile = LastEntryWasFile;
	IsEncrypted = false;

	if (!IsFile)
	{
		return;
	}

	if (LastEntryDirectory == "")
	{
		IsEncrypted = true;

		LastEntryArchive.ReadRaw(Contents);
	}
	else
	{
		loadFile(LastEntryDirectory, Contents);
	}
}

void ClientVisitor::StepArchive(bool quiet)
{
	ArchiveSubPath& stackEntry = ArchivePathStack.back();

	IsFile = stackEntry.Path.IsFile();
	IsEncrypted = false;
	LastEntry = "";
	LastEntryArchive = {};
	LastEntryDirectory = "";
	LastEntryWasFile = false;
	LastDepth = ClientPathStack.size() + ArchivePathStack.size();

	if (IsFile)
	{
		LastEntry = sanitize("Data" / stackEntry.Path.GetPath());
		LastEntryArchive = stackEntry.Path;
		LastEntryWasFile = true;

		if (!quiet)
		{
			stackEntry.Path.Read(Contents);

			computeMD5Hex(Contents, Hash);

			std::cout << LastEntry << " " << Hash << std::endl;
		}

		ArchivePathStack.pop_back();

		return;
	}

	if (stackEntry.SubPaths.size() == 0)
	{
		LastEntry = sanitize("Data" / stackEntry.Path.GetPath());

		if (!quiet)
		{
			std::cout << LastEntry << std::endl;
		}

		size_t childDirectoryCount = stackEntry.Path.ChildDirectories();

		for (size_t i = 0; i < childDirectoryCount; ++i)
		{
			Archive::ArchiveReader::Path child = stackEntry.Path.ChildDirectory(i);

			stackEntry.SubPaths.push_back(child);
		}

		size_t childFileCount = stackEntry.Path.ChildFiles();

		for (size_t i = 0; i < childFileCount; ++i)
		{
			Archive::ArchiveReader::Path child = stackEntry.Path.ChildFile(i);

			stackEntry.SubPaths.push_back(child);
		}

		if (stackEntry.SubPaths.size() == 0)
		{
			ArchivePathStack.pop_back();

			return;
		}

		const auto sortComparator = [](const Archive::ArchiveReader::Path& left, const Archive::ArchiveReader::Path& right)
		{
			return pathLessThan(left.GetPath(), right.GetPath());
		};

		std::sort(stackEntry.SubPaths.begin(), stackEntry.SubPaths.begin() + childDirectoryCount, sortComparator);
		std::sort(stackEntry.SubPaths.begin() + childDirectoryCount, stackEntry.SubPaths.end(), sortComparator);
	}

	if (stackEntry.Index >= stackEntry.SubPaths.size())
	{
		ArchivePathStack.pop_back();

		return;
	}

	++stackEntry.Index;

	ArchivePathStack.push_back({ 0, stackEntry.SubPaths[stackEntry.Index - 1] });
}

void ClientVisitor::EnterArchive(const fs::path& m2dPath, bool quiet)
{
	ArchivePath = m2dPath;
	ArchivePath.replace_extension("");

	ArchivePathStack = { { 0, Reader.GetPath(fs::relative(ArchivePath, ClientPath / "Data")) } };

	StepArchive(quiet);
}

void ClientVisitor::StepDirectory(bool quiet)
{
	ClientSubPath& stackEntry = ClientPathStack.back();

	IsFile = fs::is_regular_file(stackEntry.Path);
	IsEncrypted = false;
	LastEntry = "";
	LastEntryArchive = {};
	LastEntryDirectory = "";
	LastEntryWasFile = false;
	LastDepth = ClientPathStack.size() + ArchivePathStack.size();

	if (IsFile)
	{
		LastEntry = sanitize(fs::relative(stackEntry.Path, ClientPath));
		LastEntryDirectory = stackEntry.Path;
		LastEntryWasFile = true;

		if (!quiet)
		{
			loadFile(stackEntry.Path, Contents);

			computeMD5Hex(Contents, Hash);

			std::cout << LastEntry << " " << Hash << std::endl;
		}

		if (stackEntry.Path.extension() == fs::path(".m2d"))
		{
			fs::path headerPath = stackEntry.Path.replace_extension("m2h");

			if (fs::is_regular_file(headerPath))
			{
				EnterArchive(headerPath, quiet);
			}
		}

		ClientPathStack.pop_back();

		return;
	}

	if (stackEntry.SubPaths.size() == 0)
	{
		LastEntry = sanitize(fs::relative(stackEntry.Path, ClientPath));

		if (!quiet)
		{
			std::cout << LastEntry << std::endl;
		}

		for (auto child = fs::directory_iterator(stackEntry.Path); child != fs::directory_iterator(); ++child)
		{
			stackEntry.SubPaths.push_back(child->path());
		}

		if (stackEntry.SubPaths.size() == 0)
		{
			ClientPathStack.pop_back();

			return;
		}

		std::sort(stackEntry.SubPaths.begin(), stackEntry.SubPaths.end(), pathLessThan);
	}

	if (stackEntry.Index >= stackEntry.SubPaths.size())
	{
		ClientPathStack.pop_back();

		return;
	}

	++stackEntry.Index;

	ClientPathStack.push_back({ 0, stackEntry.SubPaths[stackEntry.Index - 1] });
}

void ClientVisitor::EnterClient(const fs::path& clientPath, bool quiet)
{
	ClientPath = clientPath;

	Reader.Quiet = true;
	Reader.Load(clientPath / "Data", true);

	ClientPathStack = { { 0, clientPath } };

	std::string extension;

	if (clientPath.has_extension() && fs::is_regular_file(clientPath))
	{
		extension = clientPath.extension().string();
	}

	if (extension == ".m2d" || extension == ".m2h")
	{
		EnterArchive(clientPath, quiet);

		return;
	}

	StepDirectory(quiet);
}

void ClientVisitor::Step(bool quiet)
{
	IsFile = false;
	IsEncrypted = false;

	Contents.clear();

	if (ArchivePathStack.size())
	{
		StepArchive(quiet);
	}
	else if (ClientPathStack.size())
	{
		StepDirectory(quiet);
	}
	else
	{
		LastEntry = "";
		LastEntryArchive = {};
		LastEntryDirectory = "";
		LastEntryWasFile = false;
		LastDepth = 0;
	}
}

void ClientVisitor::DumpClient(const fs::path& clientPath)
{
	EnterClient(clientPath);

	while (GetDepth())
	{
		Step();
	}
}

size_t ClientVisitor::GetDepth() const
{
	return ArchivePathStack.size() + ClientPathStack.size();
}

void dumpClientData(const fs::path& clientPath)
{
	ClientVisitor visitor;

	visitor.DumpClient(clientPath);
}

bool diffClientData(const fs::path& clientPath1, const fs::path& clientPath2)
{
	ClientVisitor visitor1;
	ClientVisitor visitor2;

	visitor1.EnterClient(clientPath1, true);
	visitor2.EnterClient(clientPath2, true);

	std::vector<std::string> removals;
	std::vector<std::string> adds;

	bool foundDiff = false;
	bool addedDiff = false;

	while (visitor1.LastDepth || visitor2.LastDepth)
	{
		if (visitor1.LastEntry == "" && visitor1.LastDepth)
		{
			visitor1.Step(true);

			continue;
		}

		if (visitor2.LastEntry == "" && visitor2.LastDepth)
		{
			visitor2.Step(true);

			continue;
		}

		if (!foundDiff && addedDiff)
		{
			std::cout << "index 0000000..0000000 000000\n";
			std::cout << "--- " << clientPath1.string() << "/diff.txt\n";
			std::cout << "+++ " << clientPath2.string() << "/diff.txt\n";
		}

		foundDiff |= addedDiff;

		if (!addedDiff && (removals.size() || adds.size()))
		{
			std::cout << "@@ -" << removals.size() << " +" << adds.size() << " @@\n";

			for (const std::string& removal : removals)
			{
				std::cout << "-" << removal << "\n";
			}

			for (const std::string& add : adds)
			{
				std::cout << "+" << add << "\n";
			}

			removals.clear();
			adds.clear();
		}

		addedDiff = false;

		size_t depth1 = visitor1.LastDepth;
		size_t depth2 = visitor2.LastDepth;

		fs::path path1 = visitor1.LastEntry;
		fs::path path2 = visitor2.LastEntry;

		if (depth1 == depth2)
		{
			int comparison = comparePaths(path1, path2);

			if (comparison == 0)
			{
				visitor1.LoadFileRaw();
				visitor2.LoadFileRaw();

				if (visitor1.IsFile == visitor2.IsFile)
				{
					if (visitor1.Contents != visitor2.Contents)
					{
						if (visitor1.IsEncrypted)
						{
							visitor1.LoadFile();
						}

						if (visitor2.IsEncrypted)
						{
							visitor2.LoadFile();
						}

						computeMD5Hex(visitor1.Contents, visitor1.Hash);
						computeMD5Hex(visitor2.Contents, visitor2.Hash);

						removals.push_back(path1.string() + " " + visitor1.Hash);
						adds.push_back(path2.string() + " " + visitor2.Hash);

						addedDiff = true;
					}

					visitor1.Step(true);
					visitor2.Step(true);

					continue;
				}

				if (visitor1.IsEncrypted)
				{
					visitor1.LoadFile();
				}

				if (visitor2.IsEncrypted)
				{
					visitor2.LoadFile();
				}

				addedDiff = true;

				ClientVisitor& fileVisitor = visitor1.IsFile ? visitor1 : visitor2;
				ClientVisitor& directoryVisitor = !visitor1.IsFile ? visitor1 : visitor2;
				std::vector<std::string>& fileTarget = visitor1.IsFile ? removals : adds;
				std::vector<std::string>& directoryTarget = !visitor1.IsFile ? removals : adds;

				computeMD5Hex(fileVisitor.Contents, fileVisitor.Hash);

				fileTarget.push_back(fileVisitor.LastEntry.string() + " " + fileVisitor.Hash);
				directoryTarget.push_back(directoryVisitor.LastEntry.string());

				fileVisitor.Step(true);
				directoryVisitor.Step(true);

				//do
				//{
				//	directoryVisitor.Step(true);
				//	directoryVisitor.LoadFile();
				//
				//	if (directoryVisitor.IsFile)
				//	{
				//		computeMD5Hex(directoryVisitor.Contents, directoryVisitor.Hash);
				//
				//		directoryTarget.push_back(directoryVisitor.GetCurrentPath().string() + " " + directoryVisitor.Hash);
				//	}
				//	else
				//	{
				//		directoryTarget.push_back(directoryVisitor.GetCurrentPath().string());
				//	}
				//} while (directoryVisitor.GetDepth() > depth1);

				continue;
			}

			if (comparison < 0)
			{
				visitor1.LoadFile();

				if (visitor1.IsFile)
				{
					computeMD5Hex(visitor1.Contents, visitor1.Hash);

					removals.push_back(path1.string() + " " + visitor1.Hash);
				}
				else
				{
					removals.push_back(path1.string());
				}

				visitor1.Step(true);

				addedDiff = true;

				continue;
			}

			visitor2.LoadFile();

			if (visitor2.IsFile)
			{
				computeMD5Hex(visitor2.Contents, visitor2.Hash);

				adds.push_back(path2.string() + " " + visitor2.Hash);
			}
			else
			{
				adds.push_back(path2.string());
			}

			visitor2.Step(true);

			addedDiff = true;

			continue;
		}

		if (depth1 > depth2)
		{
			visitor1.LoadFile();

			if (visitor1.IsFile)
			{
				computeMD5Hex(visitor1.Contents, visitor1.Hash);

				removals.push_back(path1.string() + " " + visitor1.Hash);
			}
			else
			{
				removals.push_back(path1.string());
			}

			visitor1.Step(true);

			addedDiff = true;

			continue;
		}

		visitor2.LoadFile();

		if (visitor2.IsFile)
		{
			computeMD5Hex(visitor2.Contents, visitor2.Hash);

			adds.push_back(path2.string() + " " + visitor2.Hash);
		}
		else
		{
			adds.push_back(path2.string());
		}

		visitor2.Step(true);

		addedDiff = true;
	}

	if (removals.size() || adds.size())
	{
		if (!foundDiff)
		{
			std::cout << "index 0000000..0000000 000000\n";
			std::cout << "--- " << clientPath1.string() << "/diff.txt\n";
			std::cout << "+++ " << clientPath2.string() << "/diff.txt\n";
		}

		foundDiff = true;

		std::cout << "@@ -" << removals.size() << " +" << adds.size() << " @@\n";

		for (const std::string& removal : removals)
		{
			std::cout << "-" << removal << "\n";
		}

		for (const std::string& add : adds)
		{
			std::cout << "+" << add << "\n";
		}
	}

	return foundDiff;
}

int main(int argc, char** argv)
{
	fs::path ms2Root;
	fs::path ms2Root2;
	bool setFirstRoot = false;
	bool setSecondRoot = false;

	for (int i = 0; i < argc; ++i)
	{
		if (strcmp(argv[i], "--root") == 0 && ++i < argc)
		{
			if (!fs::exists(fs::path(argv[i])))
			{
				std::cout << "failed to find root dir: " << argv[i] << std::endl;

				return -1;
			}

			ms2Root = argv[i];
			setFirstRoot = true;
		}

		if (strcmp(argv[i], "--root2") == 0 && ++i < argc)
		{
			if (!fs::exists(fs::path(argv[i])))
			{
				std::cout << "failed to find root dir: " << argv[i] << std::endl;

				return -1;
			}

			ms2Root2 = argv[i];
			setSecondRoot = true;
		}
	}

	if (setFirstRoot)
	{
		if (!setSecondRoot)
		{
			std::cout << "using root path: " << ms2Root.string() << std::endl;
			std::cout << "path found: " << fs::exists(ms2Root) << std::endl;
		}

		if (!fs::exists(ms2Root))
		{
			std::cout << "root path " << ms2Root << " not found" << std::endl;

			return -1;
		}
	}

	if (setSecondRoot && !fs::exists(ms2Root2))
	{
		std::cout << "root path 2 " << ms2Root << " not found" << std::endl;

		return -1;
	}

	if (setFirstRoot && !setSecondRoot)
	{
		dumpClientData(setFirstRoot ? ms2Root : ms2Root2);
	}
	else if (setFirstRoot && setSecondRoot)
	{
		bool foundDiff = diffClientData(ms2Root, ms2Root2);

		if (foundDiff)
		{
			return 1;
		}
	}
	else if (setSecondRoot && !setFirstRoot)
	{
		std::cout << "only set second root, missing first" << std::endl;

		return -1;
	}

	return -2;
}