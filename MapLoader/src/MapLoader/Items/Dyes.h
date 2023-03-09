#pragma once

#include <Engine/Math/Color4.h>
#include <ArchiveParser/ArchiveReader.h>

namespace MapLoader
{
	struct DyeColor
	{
		Color4 Primary;
		Color4 Secondary;
	};

	struct DyeColorInfo
	{
		std::string Name;
		int Id = 0;
		int Palette = 0;
		int Index = 0;
		Color4 Primary;
		Color4 Unused;
		Color4 Secondary;
		Color4 Display;
		bool DisplayBoth = false;
		bool HasEyeOverride = false;
		Color4 EyePrimary;
		Color4 EyeSecondary;
	};

	class DyeColors
	{
	public:
		DyeColor GetDyeColor(const std::string& name, bool isEye = false);
		DyeColor GetDyeColor(int index, int palette = 11000072);

		void LoadDyes(const std::shared_ptr<Archive::ArchiveReader>& reader);

	private:
		std::vector<DyeColorInfo> DyeColors;
		std::vector<DyeColorInfo> DyeColorsNA;
		std::unordered_map<std::string, DyeColorInfo*> DyeColorMap;
		std::string DocumentBuffer;

		void LoadDyes(const Archive::ArchivePath& file, std::vector<DyeColorInfo>& container);
		void LoadDyeNames(const Archive::ArchivePath& file, std::vector<DyeColorInfo>& container);
	};
}