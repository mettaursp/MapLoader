#include "Dyes.h"

#include <ArchiveParser/ParserUtils.h>
#include <ArchiveParser/XmlReader.h>

namespace MapLoader
{
	void DyeColors::LoadDyes(const std::shared_ptr<Archive::ArchiveReader>& reader)
	{
		LoadDyes(reader->GetPath("Xml/table/colorpalette.xml"), DyeColors);
		LoadDyes(reader->GetPath("Xml/table/na/colorpalette_achieve.xml"), DyeColorsNA);
		LoadDyeNames(reader->GetPath("Xml/string/en/stringcolorpalette.xml"), DyeColorsNA);
	}

	DyeColor DyeColors::GetDyeColor(const std::string& name, bool isEye)
	{
		const auto& dyeIndex = DyeColorMap.find(lower(name));

		if (dyeIndex == DyeColorMap.end()) return DyeColor{};
		if (dyeIndex->second == nullptr) return DyeColor{};

		if (isEye && dyeIndex->second->HasEyeOverride)
			return DyeColor{ dyeIndex->second->EyePrimary, dyeIndex->second->EyeSecondary };

		return DyeColor{ dyeIndex->second->Primary, dyeIndex->second->Secondary };
	}

	DyeColor DyeColors::GetDyeColor(int index, int palette)
	{
		for (const DyeColorInfo& color : DyeColors)
		{
			if (color.Palette == palette && color.Index == index)
				return DyeColor{ color.Primary, color.Secondary };
		}

		return DyeColor{};
	}

	void DyeColors::LoadDyes(const Archive::ArchivePath& file, std::vector<DyeColorInfo>& container)
	{
		if (!file.Loaded())
		{
			std::cout << "failed to load dyes " << file.GetPath().string() << std::endl;
			return;
		}

		file.Read(DocumentBuffer);

		XmlLite::XmlReader document;

		document.OpenDocument(DocumentBuffer);

		document.GetFirstChild();

		XmlLite::XmlReader::StackMarker paletteMarker = document.GetStackMarker();

		for (const XmlLite::XmlNode* paletteElement = document.GetFirstChild(); paletteElement; paletteElement = document.GetNextSibling(paletteMarker))
		{
			XmlLite::XmlReader::StackMarker colorMarker = document.GetStackMarker();

			int paletteId = document.ReadAttributeValue<int>("id", 0);

			for (const XmlLite::XmlNode* colorElement = document.GetFirstChild(); colorElement; colorElement = document.GetNextSibling(colorMarker))
			{
				DyeColorInfo dyeColor;

				unsigned long ch0 = 0xFFFFFFFF;
				unsigned long ch1 = 0xFFFFFFFF;
				unsigned long ch2 = 0xFFFFFFFF;
				unsigned long ch0_eye = 0xFFFFFFFF;
				unsigned long ch2_eye = 0xFFFFFFFF;
				unsigned long display = 0xFFFFFFFF;

				const auto results = document.ReadAttributes(
					XmlLite::Attribute<int>("colorSN", dyeColor.Index, 0),
					XmlLite::AttributeHex<unsigned long>("ch0", ch0, 0xFFFFFFFFul, 2),
					XmlLite::AttributeHex<unsigned long>("ch1", ch1, 0xFFFFFFFFul, 2),
					XmlLite::AttributeHex<unsigned long>("ch2", ch2, 0xFFFFFFFFul, 2),
					XmlLite::AttributeHex<unsigned long>("ch0_eye", ch0_eye, 0xFFFFFFFFul, 2),
					XmlLite::AttributeHex<unsigned long>("ch2_eye", ch2_eye, 0xFFFFFFFFul, 2),
					XmlLite::AttributeHex<unsigned long>("palette", display, 0xFFFFFFFFul, 2),
					XmlLite::Attribute<bool>("show2color", dyeColor.DisplayBoth, false),
					XmlLite::Attribute<int>("stringKey", dyeColor.Id, 0)
				);

				dyeColor.Palette = paletteId;

				bool has_ch0_eye = results.FoundAttribute[4];
				bool has_ch2_eye = results.FoundAttribute[5];

				dyeColor.HasEyeOverride = has_ch0_eye && has_ch2_eye;

				const auto loadColor = [](unsigned int color) -> Color4
				{
					unsigned int alpha = (color & 0xFF000000) >> 24;
					color <<= 8;
					return Color4(color | alpha);
				};

				dyeColor.Primary = loadColor((unsigned int)ch0);
				dyeColor.Secondary = loadColor((unsigned int)ch2);
				dyeColor.Unused = loadColor((unsigned int)ch1);
				dyeColor.Display = loadColor((unsigned int)display);
				dyeColor.EyePrimary = loadColor((unsigned int)ch0_eye);
				dyeColor.EyeSecondary = loadColor((unsigned int)ch2_eye);

				container.push_back(dyeColor);
			}
		}
	}

	int str2int(const char* string, size_t length)
	{
		if (length == 0) return 0;

		int number = 0;
		bool isNegative = string[0] == '-';

		if (length == 1) return 0;

		for (size_t i = isNegative ? 1 : 0; i < length && string[i] >= '0' && string[i] <= '9'; ++i)
			number = number * 10 + string[i] - '0';

		if (isNegative)
			number *= -1;

		return number;
	}

	int str2int(const std::string_view& string)
	{
		return str2int(string.data(), string.size());
	}

	void DyeColors::LoadDyeNames(const Archive::ArchivePath& file, std::vector<DyeColorInfo>& container)
	{
		if (!file.Loaded())
		{
			std::cout << "failed to load dye names " << file.GetPath().string() << std::endl;
			return;
		}

		file.Read(DocumentBuffer);

		XmlLite::XmlReader document;
		document.OpenDocument(DocumentBuffer);

		const XmlLite::XmlNode* node2 = document.GetFirstChild();

		XmlLite::XmlReader::StackMarker nodeMarker = document.GetStackMarker();

		for (const XmlLite::XmlNode* node = document.GetFirstChild(); node != nullptr; node = document.GetNextSibling(nodeMarker))
		{
			int id = document.ReadAttributeValue<int>("id", 0);

			for (DyeColorInfo& dyeColor : container)
			{
				if (dyeColor.Id == id)
				{
					document.ReadAttribute<std::string>("name", dyeColor.Name, "");

					if (dyeColor.Name != "")
						DyeColorMap[lower(dyeColor.Name)] = &dyeColor;
				}
			}
		}
	}
}