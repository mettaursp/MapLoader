#pragma once

#include <istream>
#include <string_view>
#include <vector>
#include <memory>
#include <optional>

#include <Engine/Math/Matrix4.h>

#include "PackageNodes.h"

struct ModelParser
{
	Engine::Graphics::ModelPackage* Package = nullptr;

	void Parse(std::istream& stream);

	virtual void Parse(std::string_view stream) = 0;
};