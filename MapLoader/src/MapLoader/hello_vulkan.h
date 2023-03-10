/*
 * Copyright (c) 2014-2021, NVIDIA CORPORATION.  All rights reserved.
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
 * SPDX-FileCopyrightText: Copyright (c) 2014-2021 NVIDIA CORPORATION
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <map>

#include "nvvkhl/appbase_vk.hpp"
#include "nvvk/debug_util_vk.hpp"
#include "nvvk/descriptorsets_vk.hpp"
#include "nvvk/memallocator_dma_vk.hpp"
#include "nvvk/resourceallocator_vk.hpp"
#include <host_device.h>
#include <ArchiveParser/ArchiveReader.h>
#include <ArchiveParser/ArchiveParser.h>
#include <ArchiveParser/MetadataMapper.h>
#include <MapLoader/Vulkan/VulkanContext.h>
#include "Assets/GameAssetLibrary.h"
#include "Assets/TextureLibrary.h"

// #VKRay
#include "nvvk/raytraceKHR_vk.hpp"

//--------------------------------------------------------------------------------------------------
// Simple rasterizer of OBJ objects
// - Each OBJ loaded are stored in an `ObjModel` and referenced by a `ObjInstance`
// - It is possible to have many `ObjInstance` referencing the same `ObjModel`
// - Rendering is done in an offscreen framebuffer
// - The image of the framebuffer is displayed in post-process in a full-screen quad
//
class HelloVulkan : public nvvkhl::AppBaseVk
{
public:
	void setup(const VkInstance& instance, const VkDevice& device, const VkPhysicalDevice& physicalDevice, uint32_t queueFamily) override;
	void createDescriptorSetLayout();
	void createGraphicsPipeline();
	void loadModelInstance(uint32_t index, mat4 transform = mat4(1));
	void updateDescriptorSet();
	void createUniformBuffer();
	void createObjDescriptionBuffer();
	void updateUniformBuffer(const VkCommandBuffer& cmdBuf);
	void onResize(int /*w*/, int /*h*/) override;
	void destroyResources();
	void rasterize(const VkCommandBuffer& cmdBuff);
	void screenshot();
	bool startScreenshot();

	VkExtent2D m_offscreenSize{ 0, 0 };
	VkExtent2D m_batch{ 0, 0 };
	VkExtent2D m_batchSize{ 4, 4 };
	bool takingScreenshot = false;
	bool combineScreenshot = true;
	std::vector<char> screenshotBuffer;
	nvvk::Image screenshotImage;

	struct ObjInstance
	{
		mat4 transform;    // Matrix of the instance
		uint32_t      objIndex{ 0 };  // Model index reference
	};

	// Information pushed at each draw call
	PushConstantRaster m_pcRaster{
			{1},                // Identity matrix
			{10.f, 15.f, 8.f},  // light position
			0,                  // instance Id
			100.f,              // light intensity
			0                   // light type
	};

	// Array of objects and instances in the scene
	std::vector<ObjInstance> m_instances;  // Scene model instances
	std::vector<LightDesc>   lights;
	std::vector<InstDesc> instanceDescriptions;
	MouseRayOut mouseIO = { vec3(), -1 };
	MouseRayOut* mouseIOPtr = nullptr;

	// Graphic pipeline
	VkPipelineLayout            m_pipelineLayout;
	VkPipeline                  m_graphicsPipeline;
	nvvk::DescriptorSetBindings m_descSetLayoutBind;
	VkDescriptorPool            m_descPool;
	VkDescriptorSetLayout       m_descSetLayout;
	VkDescriptorSet             m_descSet;

	nvvk::Buffer m_bGlobals;  // Device-Host of the camera matrices
	nvvk::Buffer m_bObjDesc;  // Device buffer of the OBJ descriptions
	nvvk::Buffer m_lightDesc;
	nvvk::Buffer m_textureTransformDesc;
	nvvk::Buffer m_mouseIO;
	nvvk::Buffer m_InstDesc;
	nvvk::Buffer m_textureOverride;
	GlobalUniforms hostUBO;

	std::shared_ptr<MapLoader::GameAssetLibrary> AssetLibrary;

	// #Post - Draw the rendered image on a quad using a tonemapper
	void createOffscreenRender();
	void createPostPipeline();
	void createPostDescriptor();
	void updatePostDescriptorSet();
	void drawPost(VkCommandBuffer cmdBuf);

	nvvk::DescriptorSetBindings m_postDescSetLayoutBind;
	VkDescriptorPool            m_postDescPool{VK_NULL_HANDLE};
	VkDescriptorSetLayout       m_postDescSetLayout{VK_NULL_HANDLE};
	VkDescriptorSet             m_postDescSet{VK_NULL_HANDLE};
	VkPipeline                  m_postPipeline{VK_NULL_HANDLE};
	VkPipelineLayout            m_postPipelineLayout{VK_NULL_HANDLE};
	VkRenderPass                m_offscreenRenderPass{VK_NULL_HANDLE};
	VkFramebuffer               m_offscreenFramebuffer{VK_NULL_HANDLE};
	nvvk::Texture               m_offscreenColor;
	nvvk::Texture               m_offscreenDepth;
	VkFormat                    m_offscreenColorFormat{VK_FORMAT_R32G32B32A32_SFLOAT};
	VkFormat                    m_offscreenDepthFormat{VK_FORMAT_X8_D24_UNORM_PACK32};

	// #VKRay
	void initRayTracing();
	auto objectToVkGeometryKHR(const MapLoader::MeshDescription& model);
	void createBottomLevelAS();
	void createTopLevelAS();
	void createRtDescriptorSet();
	void updateRtDescriptorSet();
	void createRtPipeline();
	void createRtShaderBindingTable();
	void raytrace(const VkCommandBuffer& cmdBuf, const vec4& clearColor);


	VkPhysicalDeviceRayTracingPipelinePropertiesKHR m_rtProperties{VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR};
	nvvk::RaytracingBuilderKHR                      m_rtBuilder;
	nvvk::DescriptorSetBindings                     m_rtDescSetLayoutBind;
	VkDescriptorPool                                m_rtDescPool;
	VkDescriptorSetLayout                           m_rtDescSetLayout;
	VkDescriptorSet                                 m_rtDescSet;
	std::vector<VkRayTracingShaderGroupCreateInfoKHR> m_rtShaderGroups;
	VkPipelineLayout                                  m_rtPipelineLayout;
	VkPipeline                                        m_rtPipeline;

	nvvk::Buffer                    m_rtSBTBuffer;
	VkStridedDeviceAddressRegionKHR m_rgenRegion{};
	VkStridedDeviceAddressRegionKHR m_missRegion{};
	VkStridedDeviceAddressRegionKHR m_hitRegion{};
	VkStridedDeviceAddressRegionKHR m_callRegion{};

	// Push constant for ray tracer
	PushConstantRay m_pcRay{};
};
