#include "ModelParser.h"

void ModelParser::Parse(std::istream& stream)
{
	if (Package == nullptr)
	{
		throw "importing model with no target package";
	}

	std::streampos start = stream.tellg();
	stream.seekg(0, std::ios::end);
	std::streampos length = stream.tellg() - start;
	stream.seekg(start);
	std::string buffer;
	buffer.resize(length);
	stream.read(&buffer[0], length);

	Parse(buffer);
}