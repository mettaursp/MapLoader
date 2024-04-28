#include "ObjParser.h"

void ObjParser::Parse(std::string_view stream)
{
	std::vector<Vector3> Points;
	std::vector<Vector2> UVs;
	std::vector<Vector3S> Normals;

	size_t PointComponents = 3;
	size_t UVComponents = 1;
}