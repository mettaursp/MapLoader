#include "Object.h"

#include <Engine/IdentifierHeap.h>

namespace Engine
{
	class Transform;

	class Simulation : public Object
	{
	public:
		~Simulation();

		void AddTransform(Transform* transform);
		void RemoveTransform(Transform* transform);
		void ClearTransforms();

		virtual void TransformChanged(Transform* transform, bool firstChange) {}
		virtual void TransformStaticChanged(Transform* transform, bool isNowStatic) {}
		virtual void TransformRemoved(Transform* transform) {}

	private:
		std::vector<Transform*> Transforms;
		IDHeap TransformIds;
	};
}