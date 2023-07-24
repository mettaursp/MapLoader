#include <ArchiveParser/ArchiveParser.h>
#include <ArchiveParser/ArchiveReader.h>
#include <ArchiveParser/MetadataMapper.h>
#include <iostream>
#include <tinyxml2/tinyxml2.h>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <unordered_set>

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

void traverse(const Archive::ArchivePath& path)
{
	std::cout << path.GetPath() << "\n";

	size_t childFiles = path.ChildFiles();
	size_t childDirectories = path.ChildDirectories();

	for (size_t i = 0; i < childFiles; ++i)
		traverse(path.ChildFile(i));

	for (size_t i = 0; i < childDirectories; ++i)
		traverse(path.ChildDirectory(i));
}

struct XmlAttribute
{
	std::string Name;
	std::string Value = "";
	bool Varies = false;
	int Visits = 0;
	std::unordered_set<std::string> Values;
};

struct XmlElement
{
	std::string Name;
	int Depth = 0;
	int Visits = 0;
	bool Optional = false;
	int VisitsThisPass = 0;
	bool CanAppearMultipleTimes = false;

	std::vector<XmlAttribute> Attributes;
	std::vector<XmlElement> Children;
};

void VisitAttribute(const tinyxml2::XMLAttribute* attribute, XmlAttribute& schema)
{
	++schema.Visits;

	if (attribute->Value() != schema.Value)
	{
		schema.Varies = true;
		schema.Values.insert(attribute->Value());
	}
}

void VisitElement(tinyxml2::XMLElement* element, XmlElement& schema)
{
	++schema.Visits;
	++schema.VisitsThisPass;
	schema.CanAppearMultipleTimes |= schema.VisitsThisPass > 1;

	for (const tinyxml2::XMLAttribute* attribute = element->FirstAttribute(); attribute; attribute = attribute->Next())
	{
		size_t index = (size_t)-1;
		const char* name = attribute->Name();

		for (size_t i = 0; i < schema.Attributes.size() && index == (size_t)-1; ++i)
			if (schema.Attributes[i].Name == name)
				index = i;

		if (index == (size_t)-1)
		{
			index = schema.Attributes.size();
			schema.Attributes.push_back({});
			schema.Attributes[index].Name = name;
			schema.Attributes[index].Value = attribute->Value();
		}

		VisitAttribute(attribute, schema.Attributes[index]);
	}

	for (size_t i = 0; i < schema.Children.size(); ++i)
		schema.Children[i].VisitsThisPass = 0;

	for (tinyxml2::XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement())
	{
		size_t index = (size_t)-1;
		const char* name = child->Name();

		for (size_t i = 0; i < schema.Children.size() && index == (size_t)-1; ++i)
			if (schema.Children[i].Name == name)
				index = i;

		if (index == (size_t)-1)
		{
			index = schema.Children.size();
			schema.Children.push_back({});
			schema.Children[index].Name = name;
			schema.Children[index].Optional = schema.Visits > 1;
			schema.Children[index].Depth = schema.Depth + 1;
		}

		VisitElement(child, schema.Children[index]);
	}

	for (size_t i = 0; i < schema.Children.size(); ++i)
		schema.Children[i].Optional |= schema.Children[i].VisitsThisPass == 0;
}

struct TypeFlagsStruct
{
	enum TypeFlags
	{
		Empty,
		Zero,
		Bool,
		Int,
		Float,
		ID,
		UUID,
		Path,
		List,
		Name,
		Unknown,

		Max,

		EmptyBit = 1 << Empty,
		ZeroBit = 1 << Zero,
		BoolBit = 1 << Bool,
		IntBit = 1 << Int,
		FloatBit = 1 << Float,
		IDBit = 1 << ID,
		UUIDBit = 1 << UUID,
		PathBit = 1 << Path,
		ListBit = 1 << List,
		NameBit = 1 << Name,
		UnknownBit = 1 << Unknown,

		AllBits = (1 << Max) - 1
	};
};

typedef TypeFlagsStruct::TypeFlags TypeFlags;

std::ostream& operator<<(std::ostream& out, XmlAttribute& attribute)
{
	out << attribute.Name;

	if (attribute.Name == "feature" || attribute.Name == "locale") return out;

	unsigned long long flags = 0;

	for (const std::string& value : attribute.Values)
	{
		if (value.size() == 0)
		{
			flags |= TypeFlags::EmptyBit;
			continue;
		}

		if (value.size() == 1 && value[0] == '0')
		{
			flags |= TypeFlags::ZeroBit;
			continue;
		}

		if (value.size() == 1 && (value[0] == '0' || value[0] == '1'))
		{
			flags |= TypeFlags::BoolBit;
			continue;
		}

		if (strncmp(value.c_str(), "urn:uuid:", 9) == 0 || strncmp(value.c_str(), "urn:llid:", 9) == 0)
		{
			flags |= TypeFlags::UUIDBit;
			continue;
		}

		bool foundNumbers = false;
		bool foundDot = false;
		bool foundNegative = false;
		bool foundE = false;
		bool foundLetters = false;
		bool foundComma = false;
		bool foundSlash = false;
		bool foundSpace = false;
		bool foundOther = false;

		for (size_t i = 0; i < value.size(); ++i)
		{
			if (value[i] >= '0' && value[i] <= '9')
				foundNumbers = true;
			else if (value[i] == '.')
				foundDot = true;
			else if (value[i] == '-')
				foundNegative = true;
			else if (value[i] == ',')
				foundComma = true;
			else if (value[i] == '/')
				foundSlash = true;
			else if ((value[i] >= 'a' && value[i] <= 'z' && value[i] != 'e') || (value[i] >= 'A' && value[i] <= 'Z' && value[i] != 'E'))
				foundLetters = true;
			else if (value[i] == ' ')
				foundSpace = true;
			else
				foundOther = true;

			if (value[i] == 'e' || value[i] == 'E')
				foundE = true;
		}

		bool list = (foundSpace && foundComma) || foundComma;

		if (!foundComma && foundSpace)
			flags |= TypeFlags::UnknownBit;
		else if (list)
			flags |= TypeFlags::ListBit;

		if (!foundOther && !foundLetters && !foundSlash)
		{
			if (foundNumbers)
			{
				if (foundE || foundDot)
				{
					flags |= TypeFlags::FloatBit;
				}
				else
				{
					if (!foundNegative && value.size() >= 7 && value.size() <= 10)
						flags |= TypeFlags::IDBit;
					else
						flags |= TypeFlags::IntBit;
				}
			}
			else
				flags |= TypeFlags::UnknownBit;
		}
		else if (foundLetters || foundE)
		{
			if (!foundOther)
			{
				if (foundDot && !foundSlash)
				{
					flags |= TypeFlags::NameBit;
				}
				else if (foundSlash)
				{
					flags |= TypeFlags::PathBit;
				}
				else
					flags |= TypeFlags::UnknownBit;
			}
			else
				flags |= TypeFlags::UnknownBit;
		}
		else
			flags |= TypeFlags::UnknownBit;
	}

	if (flags & TypeFlags::UnknownBit)
		return out << "=unknown";

	out << "=";

	bool doComma = false;

	if (flags & TypeFlags::EmptyBit && (flags & TypeFlags::ListBit) == 0)
	{
		out << (doComma ? "," : "") << "empty";
		doComma = true;
	}

	if ((flags & TypeFlags::ZeroBit) && (flags & TypeFlags::BoolBit) == 0)
	{
		out << (doComma ? "," : "") << "0";
		doComma = true;
	}

	if (flags & TypeFlags::BoolBit && (flags & TypeFlags::IntBit) == 0 && (flags & TypeFlags::FloatBit) == 0)
	{
		out << (doComma ? "," : "") << "bool";
		doComma = true;
	}

	if (flags & TypeFlags::IntBit && (flags & TypeFlags::FloatBit) == 0 && (flags & TypeFlags::IDBit) == 0)
	{
		out << (doComma ? "," : "") << "int";
		doComma = true;
	}

	if (flags & TypeFlags::FloatBit)
	{
		out << (doComma ? "," : "") << "float";
		doComma = true;
	}

	if (flags & TypeFlags::IDBit)
	{
		out << (doComma ? "," : "") << "id";
		doComma = true;
	}

	if (flags & TypeFlags::UUIDBit)
	{
		out << (doComma ? "," : "") << "uuid";
		doComma = true;
	}

	if (flags & TypeFlags::PathBit)
	{
		out << (doComma ? "," : "") << "path";
		doComma = true;
	}

	if (flags & TypeFlags::NameBit)
	{
		out << (doComma ? "," : "") << "name";
		doComma = true;
	}

	if (flags & TypeFlags::ListBit)
	{
		out << ((flags & TypeFlags::EmptyBit) ? "[?]" : "[]");
	}

	//bool first = true;
	//
	//for (const std::string& value : attribute.Values)
	//{
	//	if (!first)
	//		out << ",";
	//
	//	first = false;
	//
	//	out << "\"" << value << "\"";
	//}

	return out;
}

std::ostream& operator<<(std::ostream& out, XmlElement& element)
{
	for (int i = 0; i < element.Depth; ++i)
		out << "\t";

	out << "<" << element.Name << (element.CanAppearMultipleTimes ? "[]" : "") << (element.Optional ? "? " : " ");

	for (size_t i = 0; i < element.Attributes.size(); ++i)
	{
		if (element.Attributes[i].Varies)
			out << element.Attributes[i] << (element.Attributes[i].Visits != element.Visits ? "? " : " ");
		else if (element.Attributes[i].Visits != element.Visits)
			out << element.Attributes[i].Name << "=\"" << element.Attributes[i].Value << "\"? ";
	}

	if (element.Children.size() == 0)
	{
		out << "/>\n";

		return out;
	}

	out << ">\n";

	for (size_t i = 0; i < element.Children.size(); ++i)
		out << element.Children[i];

	for (int i = 0; i < element.Depth; ++i)
		out << "\t";

	return out << "</" << element.Name << ">\n";
}

int main()
{
	
	fs::path ms2Root = "B:/Files/Maplstory 2 Client/appdata/";

	if (!fs::exists(ms2Root)) return -1;

	Archive::ArchiveReader reader(ms2Root / "Data", false);

	std::string paths[] = {
		"Xml/achieve",
		"Xml/additionaleffect",
		"Xml/effect",
		"Xml/emotion",
		"Xml/groundeffect",
		"Xml/item",
		"Xml/itemoption",
		"Xml/itempreset",
		"Xml/map",
		"Xml/mapxblock",
		"Xml/masteryhomemade",
		"Xml/musicscore",
		"Xml/npc",
		"Xml/object",
		"Xml/pet",
		"Xml/quest",
		"Xml/riding",
		"Xml/script",
		"Xml/skill",
		"Xml/string/en",
		"Xml/trigger",
		"Xml/ui",
		"Xml/anikeytext",
		"Resource/Exported/flat",
		"Resource/Exported/xblock"
	};

	for (const std::string& xmlPath : paths)
	{
		Archive::ArchivePath path = reader.GetPath(xmlPath, true);

		std::string output;
		XmlElement schema;

		const auto visit = [&output, &schema](const Archive::ArchivePath& path)
		{
			output.clear();

			path.Read(output);

			if (output.size() == 0)
				return;

			tinyxml2::XMLDocument document;

			document.Parse(output.data(), output.size());

			tinyxml2::XMLElement* rootElement = document.RootElement();

			if (rootElement == nullptr)
			{
				std::cout << "no root: " << path.GetPath() << std::endl;

				path.Read(output);
				return;
			}

			schema.Name = rootElement->Name();

			VisitElement(rootElement, schema);
		};

		Archive::ForEachFile(path, true, visit);
		//
		//size_t childFiles = path.ChildFiles();
		//size_t childDirectories = path.ChildDirectories();
		//
		//std::string output;
		//path.Read(output);

		//fs::path webMetaCache = "./cache/asset-web-metadata-cache";
		//
		//if (!Archive::Metadata::Entry::LoadCached(webMetaCache))
		//{
		//	Archive::Metadata::Entry::LoadEntries(reader, "Resource/asset-web-metadata");
		//	Archive::Metadata::Entry::Cache(webMetaCache);
		//}
		fs::path outPath = "./schemas/" + xmlPath + ".xml";
		fs::path parentPath = outPath.parent_path();

		if (!fs::is_directory(parentPath))
			fs::create_directories(parentPath);

		std::ofstream out(outPath);

		out << schema;
	}

	int i = 0;
	i += 0;
}