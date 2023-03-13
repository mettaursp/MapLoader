#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <ArchiveParser/ArchiveReader.h>
#include <MapLoader/Character/Character.h>

namespace MapLoader
{
	struct EmotionTexture
	{
		std::string File;
		std::string Control;
		int Delay = 0;
		bool Loop = false;
	};

	struct Emotion
	{
		std::string Animation;
		std::string IdleAnimation;
		std::string BoreAnimation1;
		std::string BoreAnimation2;
		std::string Target;
		std::string Effect;
		std::vector<EmotionTexture> Faces;
	};

	class EmotionLibrary
	{
	public:
		void LoadEmotions(const std::shared_ptr<Archive::ArchiveReader>& reader);

		const auto& GetEmotions(Gender gender) const { return gender == Gender::Male ? MaleEmotions : FemaleEmotions; }
		const Emotion& GetEmotion(Gender gender, const std::string& emotionName) const;
		EmotionTexture GetFace(Gender gender, const std::string& emotionName, int index, int id);

	private:
		std::unordered_map<std::string, Emotion> MaleEmotions;
		std::unordered_map<std::string, Emotion> FemaleEmotions;
		std::string DocumentBuffer;
		Emotion DefaultMale;
		Emotion DefaultFemale;

		void LoadEmotions(const Archive::ArchivePath& file, std::unordered_map<std::string, Emotion>& container);
	};
}