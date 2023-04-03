#include "ModelData.h"

namespace MapLoader
{
	bool ModelData::IsLoaded(size_t index) const
	{
		if (index < 0 || index >= Nodes.size())
			return false;

		return Nodes[index].MeshId != -1;
	}

	uint32_t ModelData::GetId(size_t index) const
	{
		return (uint32_t)Nodes[index].MeshId;
	}

}