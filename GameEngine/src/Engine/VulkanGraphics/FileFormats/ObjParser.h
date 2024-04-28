#pragma once

#include "ModelParser.h"

#include <Engine/Math/Vector2.h>
#include <Engine/Math/Vector3.h>
#include <Engine/Math/Vector3s.h>


struct ObjParser : public ModelParser
{
public:
	void Parse(std::string_view stream);

private:
};