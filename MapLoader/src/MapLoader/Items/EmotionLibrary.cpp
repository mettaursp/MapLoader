#include "EmotionLibrary.h"

#include <tinyxml2/tinyxml2.h>
#include <ArchiveParser/ParserUtils.h>
#include <iostream>

namespace MapLoader
{
	void EmotionLibrary::LoadEmotions(const std::shared_ptr<Archive::ArchiveReader>& reader)
	{
		LoadEmotions(reader->GetPath("Xml/emotion/common/femalecustom.xml"), FemaleEmotions);
		LoadEmotions(reader->GetPath("Xml/emotion/common/malecustom.xml"), MaleEmotions);

		DefaultMale = MaleEmotions["default"];
		DefaultFemale = FemaleEmotions["default"];
	}

	const Emotion& EmotionLibrary::GetEmotion(Gender gender, const std::string& emotionName) const
	{
		const std::unordered_map<std::string, Emotion>& container = GetEmotions(gender);

		const auto emotionIndex = container.find(emotionName);

		if (emotionIndex != container.end())
			return emotionIndex->second;

		if (gender == Gender::Male)
			return DefaultMale;

		return DefaultFemale;
	}

	EmotionTexture EmotionLibrary::GetFace(Gender gender, const std::string& emotionName, int index, int id)
	{
		const Emotion& emotion = GetEmotion(gender, emotionName);

		index = std::min((int)emotion.Faces.size() - 1, std::max(0, index));

		const EmotionTexture& faceData = emotion.Faces[index];
		EmotionTexture face = { faceData.File, faceData.Control };

		id %= 10000000;

		for (int i = 0; i < 8; ++i)
		{
			int digit = id % 10;
			id /= 10;

			face.File[10 + 7 - i] = '0' + digit;
			face.Control[10 + 7 - i] = '0' + digit;
		}

		return face;
	}

	void EmotionLibrary::LoadEmotions(const Archive::ArchivePath& file, std::unordered_map<std::string, Emotion>& container)
	{
		if (!file.Loaded())
		{
			std::cout << "failed to load emotions " << file.GetPath().string() << std::endl;
			return;
		}

		tinyxml2::XMLDocument document;

		file.Read(DocumentBuffer);
		document.Parse(DocumentBuffer.data(), DocumentBuffer.size());

		tinyxml2::XMLElement* rootElement = document.RootElement();

		for (tinyxml2::XMLElement* emotionElement = rootElement->FirstChildElement(); emotionElement; emotionElement = emotionElement->NextSiblingElement())
		{
			std::string emotionName = readAttribute<std::string>(emotionElement, "name", "");

			Emotion& emotion = container[emotionName];

			for (tinyxml2::XMLElement* propertyElement = emotionElement->FirstChildElement(); propertyElement; propertyElement = propertyElement->NextSiblingElement())
			{
				const char* name = propertyElement->Name();

				if (strcmp(name, "anim") == 0)
				{
					emotion.Animation = readAttribute<std::string>(propertyElement, "name", "");

					continue;
				}

				if (strcmp(name, "idleAnim") == 0)
				{
					emotion.IdleAnimation = readAttribute<std::string>(propertyElement, "name", "");

					continue;
				}

				if (strcmp(name, "boreAnim") == 0)
				{
					emotion.BoreAnimation1 = readAttribute<std::string>(propertyElement, "name", "");

					size_t i = 0;

					for (i; i < emotion.BoreAnimation1.size() && emotion.BoreAnimation1[i] != ','; ++i);

					if (i < emotion.BoreAnimation1.size())
					{
						emotion.BoreAnimation2 = emotion.BoreAnimation1.substr(i + 1, emotion.BoreAnimation1.size() - i - 1);
						emotion.BoreAnimation1 = emotion.BoreAnimation1.substr(0, i);
					}

					continue;
				}

				if (strcmp(name, "textureani") == 0)
				{
					emotion.Target = readAttribute<std::string>(propertyElement, "target", "");

					for (tinyxml2::XMLElement* textureElement = propertyElement->FirstChildElement(); textureElement; textureElement = textureElement->NextSiblingElement())
					{
						emotion.Faces.push_back(EmotionTexture{});

						EmotionTexture& face = emotion.Faces.back();

						face.File = readAttribute<std::string>(textureElement, "file", "");
						face.Control = readAttribute<std::string>(textureElement, "control", "");
						face.Delay = readAttribute<int>(textureElement, "delay", 0);

						if (face.File.size() > 0)
							face.File = face.File.substr(0, 10) + "00000000" + face.File.substr(13, face.File.size() - 13);

						if (face.Control.size() > 0)
							face.Control = face.Control.substr(0, 10) + "00000000" + face.Control.substr(13, face.Control.size() - 13);
					}

					continue;
				}

				if (strcmp(name, "effect") == 0)
				{
					emotion.Effect = readAttribute<std::string>(propertyElement, "file", "");

					continue;
				}
			}
		}
	}
}