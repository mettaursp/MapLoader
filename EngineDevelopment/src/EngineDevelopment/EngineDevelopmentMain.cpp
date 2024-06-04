#include <string>
#include <filesystem>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <functional>

#include <tinyxml2/tinyxml2.h>
#include <ArchiveParser/ArchiveReader.h>

struct NodeAttribute
{
	std::string Value;
	bool Optional = false;
	bool InvertIfMissing = false;
	size_t CountNotFound = 0;
	size_t CountNotDefault = 0;
	size_t CountDefault = 0;
};

struct ChildNodeData
{
	size_t Count = 0;
	bool Optional = false;
};

struct NodeType
{
	size_t Count = 0;
	std::unordered_map<std::string, ChildNodeData> RequiredChildNodes;
	std::unordered_map<std::string, NodeAttribute> DefaultAttributes;
};

std::unordered_map<std::string, NodeType> nodeTypes;
const bool onlyPrint = false;
const bool onlyPrintUnknown = false;

void Minify(const std::string& contents, const fs::path& output)
{
	tinyxml2::XMLDocument document(true, tinyxml2::PRESERVE_WHITESPACE);

	document.Parse(contents.c_str(), contents.size());

	struct StackEntry
	{
		const char* Name = "";
		tinyxml2::XMLElement* Node = nullptr;
		std::unordered_map<std::string, size_t> ChildCount;
		const NodeType* TypeData = nullptr;
	};

	std::vector<StackEntry> stack;

	for (tinyxml2::XMLElement* element = document.FirstChildElement(); element; element = element->NextSiblingElement())
	{
		stack.push_back({ element->Name(), element });

		while (stack.size())
		{
			tinyxml2::XMLElement* current = stack.back().Node;

			if (current == nullptr)
			{
				stack.pop_back();
				
				if (stack.size())
				{
					StackEntry& entry = stack.back();
					const char* exitingName = entry.Node->Name();
					const auto& type = nodeTypes.find(exitingName);

					if (type != nodeTypes.end())
					{
						for (const auto& childData : type->second.RequiredChildNodes)
						{
							const auto childEntry = entry.ChildCount.find(childData.first);

							if (childEntry == entry.ChildCount.end() && !childData.second.Optional)
							{
								if (onlyPrint && !onlyPrintUnknown)
									std::cout << exitingName << " doesn't have supposedly required node " << childData.first << std::endl;
							}
							else if (childEntry != entry.ChildCount.end() && entry.ChildCount[childData.first] != childData.second.Count && !childData.second.Optional)
							{
								if (onlyPrint && !onlyPrintUnknown)
									std::cout << exitingName << " doesn't have supposedly required node " << childData.first << " count " << childData.second.Count << "; found: " << entry.ChildCount[childData.first] << std::endl;
							}
						}
					}
					
					tinyxml2::XMLElement* next = stack.back().Node->NextSiblingElement();

					entry = { next ? next->Name() : "", next };
				}

				continue;
			}

			const char* name = current->Name();

			const auto& type = nodeTypes.find(name);

			if (type == nodeTypes.end())
			{
				std::cout << "found unknown node " << name << ": " << output << std::endl;
			}
			else if (stack.size() > 1)
			{
				stack.back().TypeData = &type->second;

				type->second.Count++;

				for (auto& entry : type->second.DefaultAttributes)
				{
					const tinyxml2::XMLAttribute* attrib = current->FindAttribute(entry.first.c_str());

					if (attrib == nullptr)
					{
						if (!entry.second.Optional)
						{
							if (onlyPrint && !onlyPrintUnknown)
								std::cout << name << " doesn't have supposedly required attribute " << entry.first << std::endl;
						}

						if (entry.second.InvertIfMissing && !onlyPrint)
						{
							current->SetAttribute(entry.first.c_str(), ("=!" + entry.second.Value).c_str());
						}

						entry.second.CountNotFound++;
					}
					else
					{
						const char* value = attrib->Value();

						if (value == entry.second.Value)
						{
							entry.second.CountDefault++;

							if (!onlyPrint)
								current->DeleteAttribute(entry.first.c_str());
						}
						else
						{
							entry.second.CountNotDefault++;
						}
					}
				}

				auto& parentEntry = stack[stack.size() - 2];

				parentEntry.ChildCount[name]++;

				if (!onlyPrint && parentEntry.TypeData != nullptr && current->FirstAttribute() == nullptr && current->FirstChildElement() == nullptr)
				{
					const auto& childEntry = parentEntry.TypeData->RequiredChildNodes.find(name);

					if (childEntry != parentEntry.TypeData->RequiredChildNodes.end())
					{
						parentEntry.Node->DeleteChild(current);
						stack.pop_back();

						continue;
					}
				}
			}

			tinyxml2::XMLElement* next = current->FirstChildElement();

			stack.push_back({ next ? next->Name() : "", next});
		}
	}

	class CustomPrinter : public tinyxml2::XMLPrinter
	{
	public:
		CustomPrinter(FILE* file = 0, bool compact = false, int depth = 0) : XMLPrinter(file, compact, depth) {}

		void PrintSpace(int depth) override
		{
			for (int i = 0; i < depth; ++i)
			{
				Write("\t");
			}
		}

		void CloseElement(bool compactMode = false) override
		{
			if (_elementJustOpened)
			{
				Write(" ");
			}

			XMLPrinter::CloseElement(compactMode);
		}
	};

	if(!onlyPrint)
	{
		FILE* file = nullptr;
		errno_t err = fopen_s(&file, output.string().c_str(), "w");

		if (!file) return;

		CustomPrinter printer(file);

		document.Print(&printer);

		fclose(file);
	}
}

int main(int argc, char** argv)
{
	fs::path ms2Root;
	fs::path outputDir = "B:/Files/ms2export/minified";

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
		}
	}

	if (!fs::exists(outputDir))
	{
		std::cout << "failed to find output dir: " << outputDir << std::endl;

		return -1;
	}

	tinyxml2::XMLDocument document(true, tinyxml2::PRESERVE_WHITESPACE);

	document.LoadFile((outputDir / "additionaleffectMinify.xml").string().c_str());

	for (tinyxml2::XMLElement* root = document.FirstChildElement(); root; root = root->NextSiblingElement())
	{
		for (tinyxml2::XMLElement* element = root->FirstChildElement(); element; element = element->NextSiblingElement())
		{
			const char* name = element->Name();
			NodeType& nodeType = nodeTypes[name];

			for (const tinyxml2::XMLAttribute* attrib = element->FirstAttribute(); attrib; attrib = attrib->Next())
			{
				nodeType.DefaultAttributes[attrib->Name()] = { attrib->Value() };
			}

			for (tinyxml2::XMLElement* config = element->FirstChildElement(); config; config = config->NextSiblingElement())
			{
				const char* type = config->Name();

				if (strcmp(type, "alwaysHas") == 0 || strcmp(type, "oftenHas") == 0) {
					const char* child = config->FindAttribute("name")->Value();
					const char* count = config->FindAttribute("count")->Value();
					bool isOptional = strcmp(type, "oftenHas") == 0;

					nodeType.RequiredChildNodes[child] = { (size_t)atoll(count), isOptional };

					continue;
				}

				if (strcmp(type, "optionalAttribute") == 0) {
					const char* attrib = config->FindAttribute("name")->Value();

					if (!nodeType.DefaultAttributes.contains(attrib))
					{
						std::cout << "trying to set unspecified default attribute '" << attrib << "' as optional" << std::endl;

						continue;
					}

					nodeType.DefaultAttributes[attrib].Optional = true;

					continue;
				}

				if (strcmp(type, "invertIfMissing") == 0) {
					const char* attrib = config->FindAttribute("name")->Value();

					if (!nodeType.DefaultAttributes.contains(attrib))
					{
						std::cout << "trying to set unspecified default attribute '" << attrib << "' as optional" << std::endl;

						continue;
					}

					nodeType.DefaultAttributes[attrib].InvertIfMissing = true;

					continue;
				}
			}
		}
	}

	Archive::ArchiveReader reader(ms2Root / "Data", false);

	struct StackEntry
	{
		Archive::ArchiveReader::Path Path;
		size_t Index = 0;
	};

	Archive::ArchiveReader::Path skillPath = reader.GetPath("Xml/additionaleffect");

	std::cout << skillPath.GetPath() << std::endl;

	std::vector<StackEntry> stack = { { skillPath } };

	std::string contents;

	//parser.Verbose = true;

	std::unordered_set<std::string> xmlFiles;

	while (stack.size())
	{
		StackEntry& entry = stack.back();

		if (entry.Index < entry.Path.ChildDirectories())
		{
			++entry.Index;

			stack.push_back({ entry.Path.ChildDirectory(entry.Index - 1), 0 });

			//std::cout << stack.back().Path.GetPath() << std::endl;

			continue;
		}

		for (size_t i = 0; i < entry.Path.ChildFiles(); ++i)
		{
			Archive::ArchiveReader::Path subPath = entry.Path.ChildFile(i);

			if (subPath.GetPath().extension() != ".xml") continue;

			subPath.Read(contents);

			fs::path filePath = outputDir / "Xml" / subPath.GetArchivePath();

			fs::create_directories(filePath.parent_path());

			Minify(contents, filePath);
		}

		stack.pop_back();
	}

	//for (const auto& type : nodeTypes)
	//{
	//	std::cout << type.first << " [" << type.second.Count << "]:" << std::endl;
	//
	//	for (const auto& attrib : type.second.DefaultAttributes)
	//	{
	//		std::cout << "\t" << attrib.first << ":" << std::endl;
	//		std::cout << "\t\tDefault: " << attrib.second.CountDefault << std::endl;
	//		std::cout << "\t\tNot default: " << attrib.second.CountNotDefault << std::endl;
	//		std::cout << "\t\tNot found: " << attrib.second.CountNotFound << std::endl;
	//	}
	//}

	return 0;
}