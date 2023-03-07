#include "ModelData.h"

namespace MapLoader
{
	bool ModelData::IsLoaded(size_t index) const
	{
		if (index < 0 || index >= MeshIds.size())
			return false;

		return MeshIds[index] != -1;
	}

	uint32_t ModelData::GetId(size_t index) const
	{
		return (uint32_t)MeshIds[index];
	}

}