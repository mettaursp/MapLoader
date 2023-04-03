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

#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_EXT_scalar_block_layout : enable
#extension GL_GOOGLE_include_directive : enable

#extension GL_EXT_shader_explicit_arithmetic_types_int64 : require
#extension GL_EXT_shader_explicit_arithmetic_types_int8 : require

#include "wavefront.glsl"

layout(set = 0, binding = 0) uniform _GlobalUniforms { GlobalUniforms uni; };

layout(push_constant) uniform _PushConstantRaster
{
	PushConstantRaster pcRaster;
};

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in u8vec4 color;
layout(location = 3) in vec2 texcoord;


layout(location = 1) out vec3 o_worldPos;
layout(location = 2) out vec4 o_color;

out gl_PerVertex
{
	vec4 gl_Position;
};


void main()
{
	vec3 origin = vec3(uni.viewInverse * vec4(0, 0, 0, 1));

	o_worldPos = vec3(pcRaster.modelMatrix * vec4(position, 1.0));
	o_color  = color;

	gl_Position = uni.viewProj * vec4(o_worldPos, 1.0);
}
