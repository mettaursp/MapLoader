#include "nvmath.h"

vec2 pow(const vec2& vec, float exp)
{
	return vec2(std::pow(vec.X, exp), std::pow(vec.Y, exp));
}

vec3 pow(const vec3& vec, float exp)
{
	return vec3(std::pow(vec.X, exp), std::pow(vec.Y, exp), std::pow(vec.Z, exp));
}

vec4 pow(const vec4& vec, float exp)
{
	return vec4(std::pow(vec.X, exp), std::pow(vec.Y, exp), std::pow(vec.Z, exp), std::pow(vec.W, exp));
}

vec2 pow(const vec2& vec, vec2 exp)
{
	return vec2(std::pow(vec.X, exp.X), std::pow(vec.Y, exp.Y));
}

vec3 pow(const vec3& vec, vec3 exp)
{
	return vec3(std::pow(vec.X, exp.X), std::pow(vec.Y, exp.Y), std::pow(vec.Z, exp.Z));
}

vec4 pow(const vec4& vec, vec4 exp)
{
	return vec4(std::pow(vec.X, exp.X), std::pow(vec.Y, exp.Y), std::pow(vec.Z, exp.Z), std::pow(vec.W, exp.W));
}

template <>
vec2 sqrt<vec2>(const vec2& value)
{
	return { std::sqrtf(value.X), std::sqrtf(value.Y) };
}

template <>
vec3 sqrt<vec3>(const vec3& value)
{
	return { std::sqrtf(value.X), std::sqrtf(value.Y), std::sqrtf(value.Z) };
}

template <>
vec4 sqrt<vec4>(const vec4& value)
{
	return { std::sqrtf(value.X), std::sqrtf(value.Y), std::sqrtf(value.Z), std::sqrtf(value.W) };
}

template <>
vec2 nvec<vec2>(float value)
{
	return { value, value };
}

template <>
vec3 nvec<vec3>(float value)
{
	return { value, value, value };
}

template <>
vec4 nvec<vec4>(float value)
{
	return { value, value, value, value };
}

template <>
vec2 min<vec2>(vec2 left, vec2 right)
{
	return { min(left.X, right.X), min(left.Y, right.Y) };
}

template <>
vec3 min<vec3>(vec3 left, vec3 right)
{
	return { min(left.X, right.X), min(left.Y, right.Y), min(left.Z, right.Z) };
}

template <>
vec4 min<vec4>(vec4 left, vec4 right)
{
	return { min(left.X, right.X), min(left.Y, right.Y), min(left.Z, right.Z), min(left.W, right.W) };
}

template <>
vec2 max<vec2>(vec2 left, vec2 right)
{
	return { max(left.X, right.X), max(left.Y, right.Y) };
}

template <>
vec3 max<vec3>(vec3 left, vec3 right)
{
	return { max(left.X, right.X), max(left.Y, right.Y), max(left.Z, right.Z) };
}

template <>
vec4 max<vec4>(vec4 left, vec4 right)
{
	return { max(left.X, right.X), max(left.Y, right.Y), max(left.Z, right.Z), max(left.W, right.W) };
}