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

bool comparePaths(const fs::path& left, const fs::path& right)
{
	const std::wstring& leftString = left.native();
	const std::wstring& rightString = right.native();

	const wchar_t* leftStr = leftString.c_str();
	const wchar_t* rightStr = rightString.c_str();

	size_t length = std::min(leftString.size(), rightString.size());

	for (size_t i = 0; i < length; ++i)
	{
		if (leftStr[i] >= rightStr[i])
		{
			// (left < right) == false
			return false;
		}
	}

	// equal to the end of the shorter string so fall back to size comparison
	return leftString.size() < rightString.size();
}

struct ClientVisitor
{
	struct ArchiveSubPath
	{
		size_t Index = 0;
		Archive::ArchiveReader::Path Path;
		std::vector<Archive::ArchiveReader::Path> SubPaths;
	};
};

bool dumpM2D(Archive::ArchiveReader& reader, const fs::path& clientPath, const fs::path& m2dPath)
{
	struct SubPath
	{
		size_t Index = 0;
		Archive::ArchiveReader::Path Path;
		std::vector<Archive::ArchiveReader::Path> SubPaths;
	};

	fs::path archivePath = m2dPath;

	archivePath.replace_extension("");

	std::vector<SubPath> pathStack = { { 0, reader.GetPath(fs::relative(archivePath, clientPath / "Data"))}};

	std::string hash;
	std::string contents;

	while (pathStack.size())
	{
		SubPath& stackEntry = pathStack.back();

		if (stackEntry.Path.IsFile())
		{
			stackEntry.Path.Read(contents);

			computeMD5Hex(contents, hash);

			std::cout << ("Data" / stackEntry.Path.GetPath()) << " " << hash << std::endl;

			pathStack.pop_back();

			continue;
		}

		if (stackEntry.SubPaths.size() == 0)
		{
			std::cout << ("Data" / stackEntry.Path.GetPath()) << std::endl;

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
				pathStack.pop_back();

				continue;
			}

			const auto sortComparator = [](const Archive::ArchiveReader::Path& left, const Archive::ArchiveReader::Path& right)
			{
				return comparePaths(left.GetPath(), right.GetPath());
			};

			std::sort(stackEntry.SubPaths.begin(), stackEntry.SubPaths.begin() + childDirectoryCount, sortComparator);
			std::sort(stackEntry.SubPaths.begin() + childDirectoryCount, stackEntry.SubPaths.end(), sortComparator);
		}

		if (stackEntry.Index >= stackEntry.SubPaths.size())
		{
			pathStack.pop_back();

			continue;
		}

		++stackEntry.Index;

		pathStack.push_back({ 0, stackEntry.SubPaths[stackEntry.Index - 1] });
	}

	return true;
}

void dumpClientData(const fs::path& clientPath)
{
	std::cout << "client root: " << clientPath << std::endl;

	Archive::ArchiveReader reader;

	reader.Quiet = true;
	reader.Load(clientPath / "Data", true);

	struct SubPath
	{
		size_t Index = 0;
		fs::path Path;
		std::vector<fs::path> SubPaths;
	};
	
	std::vector<SubPath> pathStack = { { 0, clientPath } };

	while (pathStack.size())
	{
		SubPath& stackEntry = pathStack.back();

		if (fs::is_regular_file(stackEntry.Path))
		{
			std::string hash;
			std::string contents;

			loadFile(stackEntry.Path, contents);

			computeMD5Hex(contents, hash);

			std::cout << fs::relative(stackEntry.Path, clientPath) << " " << hash << std::endl;

			if (stackEntry.Path.extension() == fs::path(".m2d"))
			{
				fs::path headerPath = stackEntry.Path.replace_extension("m2h");

				if (fs::is_regular_file(headerPath))
				{
					if (!dumpM2D(reader, clientPath, headerPath))
					{
						return;
					}
				}
			}

			pathStack.pop_back();

			continue;
		}

		if (stackEntry.SubPaths.size() == 0)
		{
			std::cout << fs::relative(stackEntry.Path, clientPath) << std::endl;

			for (auto child = fs::directory_iterator(stackEntry.Path); child != fs::directory_iterator(); ++child)
			{
				stackEntry.SubPaths.push_back(child->path());
			}

			if (stackEntry.SubPaths.size() == 0)
			{
				pathStack.pop_back();

				continue;
			}

			std::sort(stackEntry.SubPaths.begin(), stackEntry.SubPaths.end(), comparePaths);
		}

		if (stackEntry.Index >= stackEntry.SubPaths.size())
		{
			pathStack.pop_back();

			continue;
		}

		++stackEntry.Index;

		pathStack.push_back({ 0, stackEntry.SubPaths[stackEntry.Index - 1] });
	}
}

bool diffClientData(const fs::path& clientPath1, const fs::path& clientPath2)
{
	Archive::ArchiveReader reader1;

	reader1.Quiet = true;
	reader1.Load(clientPath1 / "Data", true);

	Archive::ArchiveReader reader2;

	reader2.Quiet = true;
	reader2.Load(clientPath2 / "Data", true);



	return false;
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
		std::cout << "using root path: " << ms2Root.string() << std::endl;
		std::cout << "path found: " << fs::exists(ms2Root) << std::endl;

		if (!fs::exists(ms2Root))
		{
			std::cout << "root path " << ms2Root << " not found" << std::endl;

			return -1;
		}
	}

	if (setSecondRoot)
	{
		std::cout << "using root path 2: " << ms2Root2.string() << std::endl;
		std::cout << "path 2 found: " << fs::exists(ms2Root2) << std::endl;

		if (!fs::exists(ms2Root2))
		{
			std::cout << "root path 2 " << ms2Root << " not found" << std::endl;

			return -1;
		}
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