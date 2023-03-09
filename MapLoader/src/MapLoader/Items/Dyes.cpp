#include "Dyes.h"

#include <tinyxml2/tinyxml2.h>
#include <ArchiveParser/ParserUtils.h>

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

		tinyxml2::XMLDocument document;

		file.Read(DocumentBuffer);

		document.Parse(DocumentBuffer.data(), DocumentBuffer.size());

		tinyxml2::XMLElement* rootElement = document.RootElement();

		for (tinyxml2::XMLElement* paletteElement = rootElement->FirstChildElement(); paletteElement; paletteElement = paletteElement->NextSiblingElement())
		{
			int paletteId = readAttribute<int>(paletteElement, "id", 0);

			for (tinyxml2::XMLElement* colorElement = paletteElement->FirstChildElement(); colorElement; colorElement = colorElement->NextSiblingElement())
			{
				DyeColorInfo dyeColor;

				dyeColor.Palette = paletteId;
				dyeColor.Index = readAttribute<int>(colorElement, "colorSN", 0);
				dyeColor.Id = readAttribute<int>(colorElement, "stringKey", 0);
				char* pointer;

				unsigned long ch0 = strtoul(readAttribute<const char*>(colorElement, "ch0", "0xFFFFFFFF") + 2, &pointer, 16);
				unsigned long ch1 = strtoul(readAttribute<const char*>(colorElement, "ch1", "0xFFFFFFFF") + 2, &pointer, 16);
				unsigned long ch2 = strtoul(readAttribute<const char*>(colorElement, "ch2", "0xFFFFFFFF") + 2, &pointer, 16);
				unsigned long display = strtoul(readAttribute<const char*>(colorElement, "palette", "0xFFFFFFFF") + 2, &pointer, 16);

				dyeColor.DisplayBoth = readAttribute<int>(colorElement, "show2color", 0) == 1;

				unsigned long ch0_eye = 0xFFFFFFFF;
				unsigned long ch2_eye = 0xFFFFFFFF;

				const char* ch0_eyeStr = readAttribute<const char*>(colorElement, "ch0_eye", nullptr);
				const char* ch2_eyeStr = readAttribute<const char*>(colorElement, "ch2_eye", nullptr);

				dyeColor.HasEyeOverride = ch0_eyeStr != nullptr && ch2_eyeStr != nullptr;

				if (dyeColor.HasEyeOverride)
				{
					ch0_eye = strtoul(ch0_eyeStr + 2, &pointer, 16);
					ch2_eye = strtoul(ch2_eyeStr + 2, &pointer, 16);
				}

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

	void DyeColors::LoadDyeNames(const Archive::ArchivePath& file, std::vector<DyeColorInfo>& container)
	{
		if (!file.Loaded())
		{
			std::cout << "failed to load dye names " << file.GetPath().string() << std::endl;
			return;
		}

		tinyxml2::XMLDocument document;

		file.Read(DocumentBuffer);
		document.Parse(DocumentBuffer.data(), DocumentBuffer.size());

		tinyxml2::XMLElement* rootElement = document.RootElement();

		for (tinyxml2::XMLElement* keyElement = rootElement->FirstChildElement(); keyElement; keyElement = keyElement->NextSiblingElement())
		{
			int id = readAttribute<int>(keyElement, "id", 0);

			for (DyeColorInfo& dyeColor : container)
			{
				if (dyeColor.Id == id)
				{
					dyeColor.Name = readAttribute<std::string>(keyElement, "name", "");

					if (dyeColor.Name != "")
						DyeColorMap[lower(dyeColor.Name)] = &dyeColor;
				}
			}
		}
	}

}