#include "SkillXmlProcessing.h"

#include <string>
#include <filesystem>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <functional>

#include <tinyxml2/tinyxml2.h>

#include "ClientDiff.h"

namespace fs = std::filesystem;

int SkillProcessingMain(int argc, char** argv) {
	fs::path gms2Xmls = "B:/Files/MapleStory2-XML/Xml";
	fs::path kms2Xmls = "B:/Files/Orion2-Repacker-master/xml";

	std::unordered_set<std::string> hitNpcs;
	std::unordered_map<std::string, std::string> aiFiles;
	std::unordered_map<std::string, size_t> aiMaxSkillIdx;
	std::unordered_map<std::string, size_t> skillCount;
	std::unordered_map<int, std::unordered_set<short>> skillLevelEntries;

	for (const auto entry : fs::directory_iterator(kms2Xmls / "NpcData"))
	{
		tinyxml2::XMLDocument document;

		document.LoadFile(entry.path().string().c_str());

		for (tinyxml2::XMLElement* ms2Node = document.FirstChildElement(); ms2Node; ms2Node = ms2Node->NextSiblingElement())
		{
			for (tinyxml2::XMLElement* npcNode = ms2Node->FirstChildElement(); npcNode; npcNode = npcNode->NextSiblingElement())
			{
				const tinyxml2::XMLAttribute* idAttrib = npcNode->FindAttribute("id");

				std::string_view idView = idAttrib->Value();
				std::string id = std::string{ idView } + ".xml";

				hitNpcs.insert(id);

				if (idView.size() == 7)
				{
					id = "0" + id;
				}

				std::string_view dir1 = { id.c_str(), 2 };
				std::string_view dir2 = { id.c_str() + 2, 2 };

				fs::path gms2XmlPath = gms2Xmls / "npc" / dir1 / dir2 / id;

				bool found = fs::exists(gms2XmlPath);

				if (!found)
				{
					//std::cout << "gms2 is missing id " << idView << " file " << gms2XmlPath.string() << std::endl;

					continue;
				}

				std::string idsValue;
				std::string levelsValue;
				std::string probsValue;
				std::string model;
				std::string feature;
				std::string locale;

				for (tinyxml2::XMLElement* envNode = npcNode->FirstChildElement(); envNode; envNode = envNode->NextSiblingElement())
				{
					if (strcmp(envNode->Name(), "environment") != 0)
					{
						continue;
					}

					if (const tinyxml2::XMLAttribute* attr = envNode->FindAttribute("feature"))
					{
						feature = attr->Value();
					}

					if (const tinyxml2::XMLAttribute* attr = envNode->FindAttribute("locale"))
					{
						locale = attr->Value();
						feature += std::string(feature.size() ? ":" : "") + locale;
					}

					for (tinyxml2::XMLElement* skillNode = envNode->FirstChildElement(); skillNode; skillNode = skillNode->NextSiblingElement())
					{
						if (strcmp(skillNode->Name(), "model") == 0)
						{
							const tinyxml2::XMLAttribute* kfmAttrib = skillNode->FindAttribute("kfm");
							if (kfmAttrib)
								model = kfmAttrib->Value();

							continue;
						}

						if (strcmp(skillNode->Name(), "skill") != 0)
						{
							continue;
						}

						const tinyxml2::XMLAttribute* idAttrib = skillNode->FindAttribute("ids");

						idsValue = idAttrib->Value();

						const tinyxml2::XMLAttribute* levelsAttrib = skillNode->FindAttribute("levels");

						if (levelsAttrib) levelsValue = levelsAttrib->Value();

						const tinyxml2::XMLAttribute* probsAttrib = skillNode->FindAttribute("probs");

						if (probsAttrib) probsValue = probsAttrib->Value();
					}
				}

				tinyxml2::XMLDocument gms2Document(true, tinyxml2::PRESERVE_WHITESPACE);

				gms2Document.LoadFile(gms2XmlPath.string().c_str());

				bool bailOut = false;

				for (tinyxml2::XMLElement* gms2Node = gms2Document.FirstChildElement(); gms2Node && !bailOut; gms2Node = gms2Node->NextSiblingElement())
				{
					for (tinyxml2::XMLElement* envNode = gms2Node->FirstChildElement(); envNode && !bailOut; envNode = envNode->NextSiblingElement())
					{
						if (strcmp(envNode->Name(), "environment") != 0)
						{
							continue;
						}

						std::string gms2Model;
						std::string gms2Feature;
						std::string gms2Locale;

						if (const tinyxml2::XMLAttribute* attr = envNode->FindAttribute("feature"))
						{
							gms2Feature = attr->Value();
						}

						if (const tinyxml2::XMLAttribute* attr = envNode->FindAttribute("locale"))
						{
							gms2Locale = attr->Value();
							gms2Feature += std::string(gms2Feature.size() ? ":" : "") + gms2Locale;
						}

						for (tinyxml2::XMLElement* skillNode = envNode->FirstChildElement(); skillNode && !bailOut; skillNode = skillNode->NextSiblingElement())
						{
							if (strcmp(skillNode->Name(), "model") == 0)
							{
								const tinyxml2::XMLAttribute* kfmAttrib = skillNode->FindAttribute("kfm");
								if (kfmAttrib)
									gms2Model = kfmAttrib->Value();

								if (model != gms2Model)
								{

									int countCN = 0;

									if (locale == "CN") ++countCN;
									if (gms2Locale == "CN") ++countCN;

									//bailOut |= countCN == 1;
									bailOut = true;

									//if (countCN != 1)
									std::cout << "mismatching models on " << id << "; kms2 [" << feature << "]: '" << model << "'; gms2 [" << gms2Feature << "]: '" << gms2Model << "'" << std::endl;
								}

								continue;
							}

							if (strcmp(skillNode->Name(), "aiInfo") == 0)
							{
								const tinyxml2::XMLAttribute* attrib = skillNode->FindAttribute("path");

								aiFiles[id] = attrib ? attrib->Value() : "";
								if (aiFiles[id] == "AI_DefaultNew.xml") aiFiles[id] = "AI_Default.xml";

								continue;
							}

							if (strcmp(skillNode->Name(), "skill") != 0)
							{
								continue;
							}

							const auto countStrList = [](std::string_view idList)
								{
									size_t count = 0;

									if (idList.size()) ++count;

									for (char character : idList)
									{
										if (character == ',') ++count;
									}

									return count;
								};

							const auto countProbList = [](std::string_view idList)
								{
									if (idList.size() == 0) return (size_t)0;

									size_t prob = 0;
									size_t start = 0;

									for (size_t i = 0; i <= idList.size(); ++i)
									{
										if (i == idList.size() || idList[i] == ',')
										{
											if (i != start)
											{
												std::string val = std::string{ std::string_view(idList.data() + start, i - start) };
												prob += (size_t)atoi(val.c_str());
											}
											start = i + 1;
										}
									}

									return prob;
								};

							const auto countList = [&countStrList](const tinyxml2::XMLAttribute* attrib)
								{
									size_t count = 0;

									if (attrib)
									{
										count = countStrList(attrib->Value());
									}

									return count;
								};

							const tinyxml2::XMLAttribute* attrib = skillNode->FindAttribute("ids");
							size_t count = countStrList(idsValue.c_str());


							skillCount[id] = countList(attrib);

							skillNode->SetAttribute("ids", idsValue.c_str());

							std::string priosValue;
							size_t probTotal = 0;
							size_t probBase = 100 / (count ? count : 1);
							std::stringstream probValStream;
							probValStream << probBase;
							std::string probBaseVal = probValStream.str();
							std::string levelsValue2 = levelsValue;
							std::string probsValue2 = probsValue;
							size_t levelStart = countStrList(levelsValue.c_str());
							size_t probStart = countStrList(probsValue.c_str());
							bool writeLevels = levelStart != count;
							bool writeProbs = probStart != count;

							//if (!writeLevels && levelStart != count)
							//{
							//	std::cout << id << ": id & level count mismatch: " << count << ", " << levelStart << std::endl;
							//}

							if (!writeProbs && probStart != count)
							{
								size_t remain = count - probStart;
								probTotal = countProbList(probsValue.c_str());
								probBase = 100 / (remain ? remain : 1);

								//std::cout << id << ": id & prob count mismatch: " << count << ", " << probStart << std::endl;
							}

							for (size_t i = 0; i < count; ++i)
							{
								priosValue += i ? ",1" : "1";

								if (writeLevels && i >= levelStart)
								{
									levelsValue2 += i ? ",1" : "1";
								}

								if (writeProbs && i >= probStart)
								{
									if (i == count - 1)
									{
										std::stringstream probValStream2;
										probValStream2.clear();
										probValStream2 << 100 - probTotal;
										probBaseVal = probValStream2.str();
									}

									probTotal += probBase;
									probsValue2 += i ? "," + probBaseVal : probBaseVal;
								}
							}

							if (count > 0 && writeLevels && countList(skillNode->FindAttribute("levels")) == count)
							{
								levelsValue2 = skillNode->FindAttribute("levels")->Value();
							}

							if (count > 0 && countList(skillNode->FindAttribute("priorities")) == count)
							{
								priosValue = skillNode->FindAttribute("priorities")->Value();
							}

							if (count > 0 && writeProbs && countList(skillNode->FindAttribute("probs")) == count)
							{
								probsValue2 = skillNode->FindAttribute("probs")->Value();
							}

							skillNode->SetAttribute("levels", levelsValue2.c_str());
							skillNode->SetAttribute("priorities", priosValue.c_str());
							skillNode->SetAttribute("probs", probsValue2.c_str());
						}
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

				{
					FILE* file = nullptr;
					errno_t err = fopen_s(&file, gms2XmlPath.string().c_str(), "w");

					if (!file) continue;

					CustomPrinter printer(file);

					gms2Document.Print(&printer);

					fclose(file);
				}
				//{
				//	std::ifstream fileIn(gms2XmlPath.string(), std::ios::binary);
				//	std::string contents;
				//	fileIn.seekg(0, std::ios::end);
				//	size_t length = fileIn.tellg();
				//	fileIn.seekg(0, std::ios::beg);
				//	contents.resize(length);
				//	fileIn.read(contents.data(), length);
				//	fileIn.close();
				//	contents.pop_back();
				//	contents.erase(std::remove(contents.begin(), contents.end(), '\r'), contents.end());
				//
				//	//FILE* file = nullptr;
				//	//errno_t err = fopen_s(&file, gms2XmlPath.string().c_str(), "w");
				//	//
				//	//fwrite(contents.data(), 1, contents.size(), file);
				//	//fclose(file);
				//	std::ofstream fileOut(gms2XmlPath.string(), std::ios_base::binary);
				//	fileOut.write(contents.data(), contents.size());
				//	fileOut.close();
				//}

				ms2Node += 0;
			}
		}
	}

	for (const auto entry : fs::recursive_directory_iterator(gms2Xmls / "skill"))
	{
		fs::path path = entry.path();

		if (!fs::is_regular_file(path)) continue;

		tinyxml2::XMLDocument gms2Document(true, tinyxml2::PRESERVE_WHITESPACE);

		gms2Document.LoadFile(path.string().c_str());

		int id = atoi(path.filename().string().c_str());

		auto& skill = skillLevelEntries[id];

		for (tinyxml2::XMLElement* gms2Node = gms2Document.FirstChildElement(); gms2Node; gms2Node = gms2Node->NextSiblingElement())
		{
			for (tinyxml2::XMLElement* levelNode = gms2Node->FirstChildElement(); levelNode; levelNode = levelNode->NextSiblingElement())
			{
				if (strcmp(levelNode->Name(), "level") != 0)
				{
					continue;
				}

				const tinyxml2::XMLAttribute* attrib = levelNode->FindAttribute("value");
				short level = attrib ? (short)atoi(attrib->Value()) : 0;

				if (attrib && !skill.contains(level))
				{
					skill.insert(level);
				}
			}
		}
	}

	for (const auto entry : fs::recursive_directory_iterator(gms2Xmls / "npc"))
	{
		fs::path path = entry.path();

		if (!fs::is_regular_file(path)) continue;

		std::string id = path.filename().string();

		tinyxml2::XMLDocument gms2Document(true, tinyxml2::PRESERVE_WHITESPACE);

		gms2Document.LoadFile(path.string().c_str());

		for (tinyxml2::XMLElement* gms2Node = gms2Document.FirstChildElement(); gms2Node; gms2Node = gms2Node->NextSiblingElement())
		{
			for (tinyxml2::XMLElement* envNode = gms2Node->FirstChildElement(); envNode; envNode = envNode->NextSiblingElement())
			{
				if (strcmp(envNode->Name(), "environment") != 0)
				{
					continue;
				}

				for (tinyxml2::XMLElement* skillNode = envNode->FirstChildElement(); skillNode; skillNode = skillNode->NextSiblingElement())
				{
					if (strcmp(skillNode->Name(), "aiInfo") == 0)
					{
						const tinyxml2::XMLAttribute* attrib = skillNode->FindAttribute("path");

						aiFiles[id] = attrib ? attrib->Value() : "";
						if (aiFiles[id] == "AI_DefaultNew.xml") aiFiles[id] = "AI_Default.xml";

						continue;
					}

					if (strcmp(skillNode->Name(), "skill") != 0)
					{
						continue;
					}

					const tinyxml2::XMLAttribute* attrib = skillNode->FindAttribute("ids");
					const tinyxml2::XMLAttribute* levelAttrib = skillNode->FindAttribute("levels");
					size_t count = 0;
					std::vector<int> skillIds;
					std::vector<short> skillLevels;

					if (attrib)
					{
						std::string_view idList = attrib->Value();

						if (idList.size()) ++count;

						for (char character : idList)
						{
							if (character == ',') ++count;
						}

						if (idList.size())
						{
							size_t start = 0;
							for (size_t i = 0; i <= idList.size(); ++i)
							{
								if (i == idList.size() || idList[i] == ',')
								{
									if (i != start)
									{
										std::string_view idEntry = { idList.data() + start, i - start };
										std::string idEntryVal = std::string{ idEntry };
										int idVal = atoi(idEntryVal.data());
										skillIds.push_back(idVal);
									}
									start = i + 1;
								}
							}
						}
					}

					if (levelAttrib)
					{
						std::string_view levelList = levelAttrib->Value();

						if (levelList.size()) ++count;

						for (char character : levelList)
						{
							if (character == ',') ++count;
						}

						if (levelList.size())
						{
							size_t start = 0;
							for (size_t i = 0; i <= levelList.size(); ++i)
							{
								if (i == levelList.size() || levelList[i] == ',')
								{
									if (i != start)
									{
										std::string_view levelEntry = { levelList.data() + start, i - start };
										std::string levelEntryVal = std::string{ levelEntry };
										short levelVal = (short)atoi(levelEntryVal.data());
										skillLevels.push_back(levelVal);
									}
									start = i + 1;
								}
							}
						}
					}

					if (skillIds.size() != skillLevels.size())
					{
						std::cout << id << ": mismatching id and level size: " << skillIds.size() << ", " << skillLevels.size() << std::endl;
					}
					else
					{
						for (size_t i = 0; i < skillIds.size(); ++i)
						{
							if (!skillLevelEntries.contains(skillIds[i]))
							{
								std::cout << id << ": skill id not found: " << skillIds[i] << std::endl;

								continue;
							}

							const auto& skill = skillLevelEntries[skillIds[i]];

							if (!skill.contains(skillLevels[i]))
							{
								std::cout << id << ": skill id " << skillIds[i] << " level not found: " << skillLevels[i] << std::endl;
							}
						}
					}

					skillCount[id] = count;


				}
			}
		}
	}

	for (const auto entry : aiFiles)
	{
		if (aiMaxSkillIdx.contains(entry.second)) continue;

		size_t& max = aiMaxSkillIdx[entry.second];

		fs::path aiPath = kms2Xmls / "AI" / entry.second;

		if (!fs::exists(aiPath))
		{
			std::cout << "ai file doesnt exist " << entry.second << std::endl;
			continue;
		}

		tinyxml2::XMLDocument aiDocument;

		aiDocument.LoadFile(aiPath.string().c_str());

		std::function<void(tinyxml2::XMLElement*)> traverse;

		const auto traverseFunc = [&max, &traverse](tinyxml2::XMLElement* parent)
			{
				const tinyxml2::XMLAttribute* attrib = parent->FindAttribute("idx");

				if (attrib)
				{
					std::string idx = attrib->Value();

					if (idx.size())
					{
						max = std::max(max, (size_t)atoll(idx.c_str()));
					}
				}

				attrib = parent->FindAttribute("skillIdx");

				if (attrib)
				{
					std::string idx = attrib->Value();

					if (idx.size())
					{
						max = std::max(max, (size_t)atoll(idx.c_str()));
					}
				}

				for (tinyxml2::XMLElement* node = parent->FirstChildElement(); node; node = node->NextSiblingElement())
				{
					traverse(node);
				}
			};

		traverse = traverseFunc;

		for (tinyxml2::XMLElement* node = aiDocument.FirstChildElement(); node; node = node->NextSiblingElement())
		{
			traverse(node);
		}
	}

	for (const auto entry : fs::recursive_directory_iterator(gms2Xmls / "npc"))
	{
		fs::path path = entry.path();

		if (!fs::is_regular_file(path)) continue;

		std::string fileName = path.filename().string();

		if (!hitNpcs.contains(fileName))
		{
			if (!aiFiles.contains(fileName))
			{
				std::cout << "skipped " << fileName << std::endl;
				continue;
			}

			const std::string& aiPath = aiFiles[fileName];

			size_t max = 0;

			if (!aiMaxSkillIdx.contains(aiPath))
			{
				std::cout << "wut" << std::endl;
			}
			else
			{
				max = aiMaxSkillIdx[aiPath];
			}

			size_t count = 0;

			if (!skillCount.contains(fileName))
			{
				std::cout << "wut" << std::endl;
			}
			else
			{
				count = skillCount[fileName];
			}

			if ((int)count < (int)max - 1)
				std::cout << "kms2 missing npc " << fileName << " [" << count << "]; ai: " << aiPath << " [" << std::max(0, (int)max - 1) << "]; " << path << std::endl;

		}
	}

	return 0;
}