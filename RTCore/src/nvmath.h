#pragma once

#include <Engine/Math/Vector2S.h>
#include <Engine/Math/Vector3S.h>
#include <Engine/Math/Vector3.h>
#include <Engine/Math/Matrix3.h>
#include <Engine/Math/Matrix4.h>
#include <Engine/Math/Quaternion.h>

using vec2 = Vector2SF;
using vec2i = Vector2SI;
using vec3 = Vector3SF;
using vec3i = Vector3SI;
using vec4 = Vector3F;
using vec4i = Vector3I;
using mat3 = Matrix3F;
using mat4 = Matrix4F;
using mat4d = Matrix4D;

const float nv_pi = 3.14159265358979323846264338327950288419716939937510582f;
const float nv_two_pi = nv_pi * 2.f;
const float nv_to_rad = nv_pi / 180.f;
const float nv_to_deg = 180.f / nv_pi;

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

template <typename T>
T min(T x, T y)
{
	return x < y ? x : y;
}

template <>
vec2 min<vec2>(vec2 left, vec2 right);
template <>
vec3 min<vec3>(vec3 left, vec3 right);
template <>
vec4 min<vec4>(vec4 left, vec4 right);

template <typename T>
T max(T x, T y)
{
	return x > y ? x : y;
}

template <>
vec2 max<vec2>(vec2 left, vec2 right);
template <>
vec3 max<vec3>(vec3 left, vec3 right);
template <>
vec4 max<vec4>(vec4 left, vec4 right);

template <typename T>
T clamp(T val, T minVal, T maxVal)
{
	return max(minVal, min(maxVal, val));
}

template <typename T>
float dot(const T& left, const T& right)
{
	return left * right;
}

template <typename T>
T mix(const T& first, const T& second, float value)
{
	return (1 - value) * first + value * second;
}

template <typename T>
T nvec(float value);

template <>
vec2 nvec<vec2>(float value);
template <>
vec3 nvec<vec3>(float value);
template <>
vec4 nvec<vec4>(float value);

template <typename T>
T scale(const T& first, const T& second)
{
	return T(first).Scale(second);
}

template <typename T>
T mix(const T& first, const T& second, const T& value)
{
	return scale(first, nvec<T>(1) - value) + scale(value, second);
}

template <typename T>
T sqrt(const T& value);

template <>
vec2 sqrt<vec2>(const vec2& value);
template <>
vec3 sqrt<vec3>(const vec3& value);
template <>
vec4 sqrt<vec4>(const vec4& value);

template <typename T>
T smoothstep(T edge0, T edge1, T x)
{
	T t = clamp((x - edge0) / (edge1 - edge0), (T)0, (T)1);
	return t * t * (3 - 2 * t);
}

template <typename T>
T normalize(const T& vec)
{
	return vec.Unit();
}

template <typename T>
T invert(const T& matrix)
{
	return matrix.Inverted();
}

template <typename T>
mat4 lookat(const T& eye, const T& target, const T& up)
{
	return mat4(eye, target - eye, up);
}

vec2 pow(const vec2& vec, float exp);
vec3 pow(const vec3& vec, float exp);
vec4 pow(const vec4& vec, float exp);
vec2 pow(const vec2& vec, vec2 exp);
vec3 pow(const vec3& vec, vec3 exp);
vec4 pow(const vec4& vec, vec4 exp);