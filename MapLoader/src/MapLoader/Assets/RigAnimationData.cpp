#include "RigAnimationData.h"

#include <Engine/VulkanGraphics/FileFormats/PackageNodes.h>

namespace MapLoader
{
	std::vector<std::vector<float>> KnotVectors;

	RigAnimation* RigAnimationData::FetchAnimation(const std::string& name)
	{
		auto animationIndex = AnimationMap.find(name);

		if (animationIndex == AnimationMap.end()) return nullptr;

		return animationIndex->second;
	}

	RigAnimation* RigAnimationData::FetchAnimation(const Archive::Metadata::Entry* entry)
	{
		auto animationIndex = AnimationEntryMap.find(entry);

		if (animationIndex == AnimationEntryMap.end()) return nullptr;

		return animationIndex->second;
	}

	Matrix4F RigAnimation::ComputeAnimationFrame(const Matrix4F& baseTransformation, Engine::Graphics::ModelPackageAnimationNode* node, float time)
	{
		Vector3SF translation = baseTransformation.Translation();
		float scale = baseTransformation.RightVector().Length();

		if (!node->IsSpline && node->Rotation.Type == Enum::AnimationInterpolationType::XyzRotation)
		{
			Vector3SF rotation = baseTransformation.ExtractEulerAngles(Enum::EulerAnglesOrder::PitchYawRoll);

			ComputeKeyframeAnimationFrame(translation, rotation, scale, node, time);

			return ComputeAnimationMatrix(translation, rotation, scale);
		}

		Quaternion rotation = baseTransformation;

		if (node->IsSpline)
		{
			ComputeSplineAnimationFrame(translation, rotation, scale, node, time);
		}
		else
		{
			ComputeKeyframeAnimationFrame(translation, rotation, scale, node, time);
		}

		return ComputeAnimationMatrix(translation, rotation, scale);
	}

	size_t FindKeyFrameIndex(const auto& node, float time)
	{
		if (time <= 0) return 0;

		size_t start = 0;
		size_t end = node.Keyframes.size();

		if (end == 0) return (size_t)-1;
		if (end > 0 && time >= node.Keyframes[end - 1].Time) return end - 1;

		end = end - 1;

		while (start != end && start + 1 != end)
		{
			size_t middle = (start + end) / 2;

			if (node.Keyframes[middle].Time > time)
				end = middle;
			else
				start = middle;
		}

		return start;
	}

	typedef Engine::Graphics::ModelPackageAnimationFloatKeyframe FloatKeyframe;
	typedef Engine::Graphics::ModelPackageAnimationQuaternionKeyframe QuaternionKeyframe;
	typedef Engine::Graphics::ModelPackageAnimationVectorKeyframe VectorKeyframe;

	float LinearInterpolation(const FloatKeyframe& start, const FloatKeyframe& end, float time)
	{
		return (1 - time) * start.Value + time * end.Value;
	}

	float QuadraticInterpolation(const FloatKeyframe& start, const FloatKeyframe& end, float time)
	{
		float time2 = time * time;
		float time3 = time * time2;

		return start.Value * (2 * time3 - 3 * time2 + 1) + end.Value * (-2 * time3 + 3 * time2) + start.Params.Y * (time3 - 2 * time2 + time) + end.Params.X * (time3 - time2);
	}

	float TbcInterpolation(const FloatKeyframe& start, const FloatKeyframe& end, float time)
	{
		return (1 - time) * start.Value + time * end.Value;
	}

	Quaternion LinearInterpolation(const QuaternionKeyframe& start, const QuaternionKeyframe& end, float time)
	{
		return start.Value.Slerp(end.Value, time);
	}

	Quaternion QuadraticInterpolation(const QuaternionKeyframe& start, const QuaternionKeyframe& end, float time)
	{
		return start.Value.Slerp(end.Value, time);
	}

	Quaternion TbcInterpolation(const QuaternionKeyframe& start, const QuaternionKeyframe& end, float time)
	{
		return start.Value.Slerp(end.Value, time);
	}

	Vector3SF LinearInterpolation(const VectorKeyframe& start, const VectorKeyframe& end, float time)
	{
		return (1 - time) * start.Value + time * end.Value;
	}

	Vector3SF QuadraticInterpolation(const VectorKeyframe& start, const VectorKeyframe& end, float time)
	{
		float time2 = time * time;
		float time3 = time * time2;

		return start.Value * (2 * time3 - 3 * time2 + 1) + end.Value * (-2 * time3 + 3 * time2) + start.Backward * (time3 - 2 * time2 + time) + end.Params * (time3 - time2);
	}

	Vector3SF TbcInterpolation(const VectorKeyframe& start, const VectorKeyframe& end, float time)
	{
		return (1 - time) * start.Value + time * end.Value;
	}

	void Interpolate(auto& value, Engine::Graphics::ModelPackageAnimationNode* node, float time, const auto& axis)
	{
		if (axis.Type == Enum::AnimationInterpolationType::None) return;

		size_t index = FindKeyFrameIndex(axis, time);

		if (index == axis.Keyframes.size() - 1 || axis.Keyframes[index + 1].NoChange)
		{
			value = axis.Keyframes[index].Value;

			return;
		}

		if (time <= 0)
		{
			value = axis.Keyframes[0].Value;

			return;
		}

		const auto& start = axis.Keyframes[index];
		const auto& end = axis.Keyframes[index + 1];
		float t = (time - start.Time) / (end.Time - start.Time);

		switch (axis.Type)
		{
		case Enum::AnimationInterpolationType::Linear:
			value = LinearInterpolation(start, end, t);

			break;
		case Enum::AnimationInterpolationType::Quadratic:
			value = QuadraticInterpolation(start, end, t);

			break;
		case Enum::AnimationInterpolationType::TensionBiasContinuity:
			value = TbcInterpolation(start, end, t);

			break;
		default:
			break;
		}
	};

	void GetControlPointRange(size_t& start, size_t& end, float(&weights)[SplineDegree + 1], const auto& spline, float time)
	{
		size_t count = spline.ControlPoints.size();

		time = std::max(0.f, std::min(1.f, time));
		float t = time * (float)(count - SplineDegree);

		if (time == 0)
		{
			start = 0;
			end = SplineDegree;
		}
		else if (time == 1)
		{
			start = count - 1 - SplineDegree;
			end = count - 1;
		}
		else
		{
			start = (size_t)t;
			end = start + SplineDegree;
		}

		const auto& knotVector = KnotVectors[count];

		weights[3] = 1;

		for (size_t row = SplineDegree - 1; row <= SplineDegree; --row)
		{
			size_t knotIndex0 = start + SplineDegree;
			size_t knotIndex1 = start + row;
			float knot0 = knotVector[knotIndex0];
			float knot1 = knotVector[knotIndex1];
			float knotRange = 1.f / (knot0 - knot1);
			float weight1 = (knot0 - t) * knotRange;
			float weight0 = 0;

			weights[row] = weight1 * weights[row + 1];

			for (size_t column = row + 1; column < SplineDegree; ++column)
			{
				weight0 = (t - knot1) * knotRange;
				weights[column] *= weight0;

				++knotIndex0;
				++knotIndex1;

				knot0 = knotVector[knotIndex0];
				knot1 = knotVector[knotIndex1];
				knotRange = 1.f / (knot0 - knot1);
				weight1 = (knot0 - t) * knotRange;
				weights[column] += weight1 * weights[column + 1];
			}

			weights[SplineDegree] *= (t - knot1) * knotRange;
		}
	}

	void InterpolateSpline(auto& value, const auto& spline, float time)
	{
		if (spline.ControlPoints.size() == 0) return;

		time = (time - spline.Start) / (spline.End - spline.Start);

		size_t start = 0;
		size_t end = 0;
		float weights[SplineDegree + 1] = { 0 };

		GetControlPointRange(start, end, weights, spline, time);

		value = weights[0] * spline.ControlPoints[start];

		for (size_t i = 1; i < SplineDegree + 1; ++i)
			value += weights[i] * spline.ControlPoints[start + i];

		typedef std::remove_cvref_t<decltype(spline)> SplineType;

		if constexpr (std::is_same_v<Quaternion, typename SplineType::PointType>)
		{
			value.Normalize();
		}
	}

	void RigAnimation::ComputeSplineAnimationFrame(Vector3SF& translation, Quaternion& rotation, float& scale, Engine::Graphics::ModelPackageAnimationNode* node, float time)
	{
		InterpolateSpline(translation, node->TranslationSpline, time);
		InterpolateSpline(rotation, node->RotationSpline, time);
		InterpolateSpline(scale, node->ScaleSpline, time);
	}

	void RigAnimation::ComputeKeyframeAnimationFrame(Vector3SF& translation, Quaternion& rotation, float& scale, Engine::Graphics::ModelPackageAnimationNode* node, float time)
	{
		Interpolate(translation, node, time, node->Translation);
		Interpolate(rotation, node, time, node->Rotation);
		Interpolate(scale, node, time, node->Scale);
	}

	void RigAnimation::ComputeKeyframeAnimationFrame(Vector3SF& translation, Vector3SF& rotation, float& scale, Engine::Graphics::ModelPackageAnimationNode* node, float time)
	{
		Interpolate(translation, node, time, node->Translation);
		Interpolate(rotation.X, node, time, node->EulerRotation.X);
		Interpolate(rotation.Y, node, time, node->EulerRotation.Y);
		Interpolate(rotation.Z, node, time, node->EulerRotation.Z);
		Interpolate(scale, node, time, node->Scale);
	}

	Matrix4F RigAnimation::ComputeAnimationMatrix(const Vector3SF& translation, const Quaternion& rotation, float scale)
	{
		Matrix4F transformation = rotation.MatrixF();

		transformation.SetTranslation(translation);
		
		for (int i = 0; i < 9; ++i)
			transformation.Data[i % 3][i / 3] *= scale;

		return transformation;
	}

	Matrix4F RigAnimation::ComputeAnimationMatrix(const Vector3SF& translation, const Vector3SF& rotation, float scale)
	{
		Matrix4F roll = Matrix4F::RollRotation(rotation.Z);
		Matrix4F yaw = Matrix4F::YawRotation(rotation.Y);
		Matrix4F pitch = Matrix4F::PitchRotation(rotation.X);
		Matrix4F transformation = pitch * yaw * roll;

		transformation.SetTranslation(translation);

		for (int i = 0; i < 9; ++i)
			transformation.Data[i % 3][i / 3] *= scale;

		return transformation;
	}
}