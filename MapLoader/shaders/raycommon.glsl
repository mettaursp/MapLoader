/*
 * Copyright (c) 2019-2021, NVIDIA CORPORATION.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-FileCopyrightText: Copyright (c) 2019-2021 NVIDIA CORPORATION
 * SPDX-License-Identifier: Apache-2.0
 */

struct hitPayload
{
	vec3 hitValue;
	float rayLength;
	vec3 transmission;
	int hitObject;
	vec3 nextOrigin;
	vec3 nextDirection;
};

struct shadowHitPayload
{
	bool isShadowed;
	vec3 transmission;
	vec3 nextOrigin;
	vec3 nextDirection;
	float rayLength;
};

vec2 flipV(vec2 textureCoords)
{
	return vec2(1, -1) * textureCoords + vec2(0, 1);
}

int getFlags(int flags, int mask, int shift)
{
	return (flags >> shift) & mask;
}

vec3 textureApplyColor(int mode, vec3 texture, vec3 base, float alpha)
{
	switch (mode)
	{
	case 0: // APPLY_REPLACE
		return texture;
	case 1: // APPLY_DECAL
		return mix(base, texture, alpha);
	case 2: // APPLY_MODULATE
		return texture * base;
	}

	return texture;
}

float textureApplyAlpha(int mode, float texture, float base)
{
	switch (mode)
	{
	case 0: // APPLY_REPLACE
		return texture;
	case 1: // APPLY_DECAL
		return base;
	case 2: // APPLY_MODULATE
		return texture * base;
	}

	return texture;
}

vec3 blendValue(int mode, vec3 srcColor, vec3 dstColor, float srcAlpha, float dstAlpha)
{
	vec3 one = vec3(1, 1, 1);
	vec3 zero = vec3(0, 0, 0);

	switch(mode)
	{
	case 0: // GL_ONE
		return one;
	case 1: // GL_ZERO
		return zero;
	case 2: // GL_SRC_COLOR
		return srcColor;
	case 3: // GL_ONE_MINUS_SRC_COLOR
		return one - srcColor;
	case 4: // GL_DST_COLOR
		return dstColor;
	case 5: // GL_ONE_MINUS_DST_COLOR
		return one - dstColor;
	case 6: // GL_SRC_ALPHA
		return srcAlpha * one;
	case 7: // GL_ONE_MINUS_SRC_ALPHA
		return (1 - srcAlpha) * one;
	case 8: // GL_DST_ALPHA
		return dstAlpha * one;
	case 9: // GL_ONE_MINUS_DST_ALPHA
		return (1 - dstAlpha) * one;
	case 10: // GL_SRC_ALPHA_SATURATE
		return min(srcAlpha, 1 - dstAlpha) * one;
	}

	return one;
}

vec3 debugColor(int inputValue)
{
	switch(inputValue)
	{
	case  0: return vec3(  1,   0,   0);
	case  1: return vec3(  0,   1,   0);
	case  2: return vec3(  0,   0,   1);
	case  3: return vec3(  1,   1,   0);
	case  4: return vec3(  1,   0,   1);
	case  5: return vec3(  0,   1,   1);
	case  6: return vec3(  1, 0.5,   0);
	case  7: return vec3(  1,   0, 0.5);
	case  8: return vec3(0.5,   1,   0);
	case  9: return vec3(  0,   1, 0.5);
	case 10: return vec3(0.5,   0,   1);
	case 11: return vec3(  0, 0.5,   1);
	case 12: return vec3(0.5,   0,   0);
	case 13: return vec3(  0, 0.5,   0);
	case 14: return vec3(  0,   0, 0.5);
	case 15: return vec3(0.5, 0.5,   0);
	}

	return vec3(0, 0, 0);
}