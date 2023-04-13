#pragma once

#include <istream>
#include <string_view>
#include <unordered_map>
#include <vector>

enum class TransitionType : unsigned char
{
	Blend = 0,
	Morph = 1,
	Crossfade = 2,
	Chain = 3,
	DefaultSync = 4,
	DefaultNonsync = 5,
	DefaultInvalid = 6
};

struct BlendPair
{
	std::string StartKey;
	std::string TargetKey;
};

struct ChainInfo
{
	unsigned int SequenceId = 0;
	float Duration = 0;
};

struct KfmMapTransition
{
	unsigned int TargetSequenceId = 0;
	TransitionType Type = TransitionType::DefaultInvalid;
	float Duration = 0;
	std::vector<BlendPair> BlendPairs;
	std::vector<ChainInfo> ChainInfos;
};

struct KfmAnimation
{
	unsigned int Id = 0;
	std::string Path;
	std::string Name;
	std::vector<KfmMapTransition> MapTransitions;
};

struct KfmDocument
{
	std::string NifPath;
	std::string RootName;
	unsigned int Unknown1 = 0;
	unsigned int Unknown2 = 0;
	float Unknown3 = 0;
	float Unknown4 = 0;
	std::vector<KfmAnimation> Animations;
};

class KfmParser
{
public:
	KfmDocument* Document = nullptr;

	void Parse(std::istream& stream);
	void Parse(std::string_view stream);

private:

};