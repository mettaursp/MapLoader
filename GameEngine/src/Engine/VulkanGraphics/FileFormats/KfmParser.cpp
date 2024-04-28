#include "KfmParser.h"

#include <iostream>

#include <Engine/Assets/ParserUtils.h>

void KfmParser::Parse(std::istream& stream)
{
	std::streampos start = stream.tellg();
	stream.seekg(0, std::ios::end);
	std::streampos length = stream.tellg() - start;
	stream.seekg(start);
	std::string buffer;
	buffer.resize(length);
	stream.read(&buffer[0], length);

	Parse(buffer);
}

void readString(std::string& output, Endian& endian, std::string_view& stream)
{
	unsigned int stringLength = endian.read<unsigned int>(stream);

	if (stringLength > 0)
	{
		output.append(stream.data(), stringLength);
		advanceStream(stream, stringLength);
	}
}

void KfmParser::Parse(std::string_view stream)
{
	std::string_view streamStart = stream;

	std::string headerString;

	size_t index = 0;

	for (index; stream[index] != 0x0A; ++index);

	headerString.append(stream.data(), index + 2);

	advanceStream(stream, index + 2);

	if (!(headerString[index - 1] == 0x62 && headerString[index + 1] == 0x01))
	{
		std::cout << "unknown kfm header format encountered" << std::endl;
	}

	Endian endian(std::endian::little);

	readString(Document->NifPath, endian, stream);
	readString(Document->RootName, endian, stream);

	Document->Unknown1 = endian.read<unsigned int>(stream);

	if (Document->Unknown1 != 1)
	{
		std::cout << "unknown kfm data encountered, possible larger list of data" << std::endl;
	}

	Document->Unknown2 = endian.read<unsigned int>(stream);
	Document->Unknown3 = endian.read<float>(stream);
	Document->Unknown4 = endian.read<float>(stream);

	unsigned int animationCount = endian.read<unsigned int>(stream);
	Document->Animations.resize(animationCount);

	for (unsigned int i = 0; i < animationCount; ++i)
	{
		KfmAnimation& animation = Document->Animations[i];

		animation.Id = endian.read<unsigned int>(stream);
		
		readString(animation.Path, endian, stream);
		readString(animation.Name, endian, stream);

		unsigned int transitionCount = endian.read<unsigned int>(stream);

		animation.MapTransitions.resize(transitionCount);

		for (unsigned int j = 0; j < transitionCount; ++j)
		{
			KfmMapTransition& transition = animation.MapTransitions[j];

			transition.TargetSequenceId = endian.read<unsigned int>(stream);
			transition.Type = (TransitionType)endian.read<unsigned int>(stream);

			if (transition.Type == TransitionType::DefaultNonsync) continue;

			if (transition.Type == TransitionType::Blend || transition.Type == TransitionType::Crossfade)
			{
				transition.Duration = endian.read<float>(stream);

				unsigned int blendPairCount = endian.read<unsigned int>(stream);

				transition.BlendPairs.resize(blendPairCount);

				for (unsigned int k = 0; k < blendPairCount; ++k)
				{
					BlendPair& pair = transition.BlendPairs[k];

					readString(pair.StartKey, endian, stream);
					readString(pair.TargetKey, endian, stream);
				}

				unsigned int transitionCount = endian.read<unsigned int>(stream);

				transition.ChainInfos.resize(transitionCount);

				for (unsigned int k = 0; k < transitionCount; ++k)
				{
					ChainInfo& chain = transition.ChainInfos[k];

					chain.SequenceId = endian.read<unsigned int>(stream);
					chain.Duration = endian.read<float>(stream);
				}

				continue;
			}

			std::cout << "found kfm with unsupported transition type" << std::endl;
		}
	}

	unsigned int nullTerminator = endian.read<unsigned int>(stream);

	if (nullTerminator != 0)
	{
		std::cout << "ended kfm parse before null terminator" << std::endl;
	}

	if (stream.size() != 0)
	{
		std::cout << "ended kfm parse before end of file" << std::endl;
	}
}