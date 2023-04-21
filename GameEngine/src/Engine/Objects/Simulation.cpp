#include "Simulation.h"

#include "Transform.h"

namespace Engine
{
	Simulation::~Simulation()
	{
		ClearTransforms();
	}

	void Simulation::ClearTransforms()
	{
		for (size_t i = 0; i < Transforms.size(); ++i)
		{
			if (Transforms[i] != nullptr)
			{
				Transforms[i]->RemoveFromSimulation(this);
				Transforms[i] = nullptr;
				TransformIds.Release(i);
			}
		}
	}

	void Simulation::AddTransform(Transform* transform)
	{
		size_t index = TransformIds.Allocate(Transforms, transform);

		transform->AddToSimulation(this, index);
	}

	void Simulation::RemoveTransform(Transform* transform)
	{
		size_t index = transform->RemoveFromSimulation(this);

		if (index == (size_t)-1) return;

		TransformIds.Release(index);
		Transforms[index] = nullptr;
	}
}