#include "Shader.h"

#include <nvh/fileoperations.hpp>
#include <nvvk/shaders_vk.hpp>
#include <spirv_cross/spirv.hpp>
#include <spirv_cross/spirv_common.hpp>
#include <iostream>

#include "ShaderPipeline.h"
#include "VulkanAttributes.h"

namespace Graphics
{
	Shader::Shader(const std::shared_ptr<Graphics::VulkanContext>& vulkanContext, const fs::path& shaderPath, VkShaderStageFlagBits shaderStage) : Stage(shaderStage), VulkanContext(vulkanContext)
	{
		SetPath(shaderPath);
	}

	Shader::~Shader()
	{
		ReleaseResources();
	}
	
	void Shader::LoadByteCode(bool forceReload)
	{
		if (ByteCode.size() == 0 || forceReload)
			ByteCode = nvh::loadFile(GetBinaryPath().string(), true);
	}

	void Shader::LoadModule(bool forceReload)
	{
		LoadByteCode(forceReload);

		if (Module != nullptr)
		{
			if (forceReload)
				ReleaseResources();
			else
				return;
		}

		Module = nvvk::createShaderModule(VulkanContext->Device, ByteCode);
	}

	void Shader::LoadReflection(bool forceReload)
	{
		if (Compiler != nullptr)
		{
			if (forceReload)
				Compiler.release();
			else
				return;
		}
		
		Compiler = std::make_unique<spirv_cross::Compiler>(reinterpret_cast<uint32_t*>(ByteCode.data()), ByteCode.size() / sizeof(uint32_t));
	}

	void Shader::LoadDescriptors(ShaderPipeline& pipeline)
	{
		//spirv_cross::ShaderResources resources = Compiler->get_shader_resources(Compiler->get_active_interface_variables());
		spirv_cross::ShaderResources resources = Compiler->get_shader_resources();

		std::cout << ShaderPath << "\n";

		LoadDescriptors(pipeline, resources.uniform_buffers, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
		LoadDescriptors(pipeline, resources.storage_buffers, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER);
		LoadInputs(pipeline, resources.stage_inputs);
		LoadDescriptors(pipeline, resources.subpass_inputs, VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT);
		LoadDescriptors(pipeline, resources.storage_images, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE);
		LoadDescriptors(pipeline, resources.sampled_images, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);
		LoadDescriptors(pipeline, resources.acceleration_structures, VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR);
		LoadPushConstants(pipeline, resources.push_constant_buffers);
		LoadShaderRecords(pipeline, resources.shader_record_buffers);
		LoadDescriptors(pipeline, resources.separate_images, VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE);
		LoadDescriptors(pipeline, resources.separate_samplers, VK_DESCRIPTOR_TYPE_SAMPLER);
	}

	void Shader::LoadDescriptor(ShaderPipeline& pipeline, const spirv_cross::Resource& resource, VkDescriptorType type)
	{
		uint32_t setIndex = Compiler->get_decoration(resource.id, spv::DecorationDescriptorSet);
		uint32_t bindingIndex = Compiler->get_decoration(resource.id, spv::DecorationBinding);

		std::cout << "\tdescriptor: " << resource.name;
		std::cout << "; set: " << setIndex;
		std::cout << "; binding: " << bindingIndex << "\n";

		DescriptorSet& set = pipeline.FetchDescriptorSet(setIndex);
		DescriptorSet::DescriptorReference bindingRef = set.FetchBinding(bindingIndex);
		VkDescriptorSetLayoutBinding& binding = bindingRef.Binding;

		const spirv_cross::SPIRType& arrayType = Compiler->get_type(resource.type_id);

		uint32_t descriptorCount = 1;

		if (arrayType.array.size() > 0)
		{
			for (size_t i = 0; i < arrayType.array.size(); ++i)
				descriptorCount *= arrayType.array[i];
		}

		if (binding.stageFlags != 0)
		{
			bool cancel = false;

			if (binding.descriptorType != type)
			{
				std::cout << "mismatching binding type in set " << setIndex << " [" << bindingIndex << "]: " << type << " != " << binding.descriptorType << "\n";

				cancel = true;
			}

			if (bindingRef.Name != resource.name)
			{
				std::cout << "mismatching descriptor name in set " << setIndex << " [" << bindingIndex << "]: \"" << resource.name << "\" != \"" << bindingRef.Name << "\"\n";

				cancel = true;
			}

			if (descriptorCount != 0 && binding.descriptorCount != 0 && descriptorCount != binding.descriptorCount)
			{
				std::cout << "mismatching descriptor count in set " << setIndex << " [" << bindingIndex << "]: " << descriptorCount << " != " << binding.descriptorCount << "\n";

				cancel = true;
			}

			if (cancel)
				return;
		}

		binding.descriptorType = type;
		binding.stageFlags |= Stage;
		bindingRef.Name = resource.name;

		if (descriptorCount != 0)
			binding.descriptorCount = descriptorCount;
	}

	void Shader::LoadDescriptors(ShaderPipeline& pipeline, const spirv_cross::SmallVector<spirv_cross::Resource>& resources, VkDescriptorType type)
	{
		for (const spirv_cross::Resource& resource : resources)
		{
			LoadDescriptor(pipeline, resource, type);
		}
	}

	void Shader::LoadInputs(ShaderPipeline& pipeline, const spirv_cross::SmallVector<spirv_cross::Resource>& resources)
	{
		if (Stage == VK_SHADER_STAGE_VERTEX_BIT)
		{
			for (const spirv_cross::Resource& resource : resources)
			{
				uint32_t locationIndex = Compiler->get_decoration(resource.id, spv::DecorationLocation);

				spirv_cross::SPIRType baseType = Compiler->get_type(resource.base_type_id);

				std::cout << "\tvertex attribute [" << locationIndex << "] " << resource.name << ": " << GetFormatName(baseType.basetype, baseType.vecsize) << "\n";

				auto& attribute = pipeline.FetchVertexInputAttribute(locationIndex, resource.name);

				VkFormat format = GetVulkanFormat(baseType.basetype, baseType.vecsize);

				if (format != attribute.format)
				{
					std::cout << "mismatching vertex attribute type [" << locationIndex << "] " << resource.name << ": " << GetFormatName(baseType.basetype, baseType.vecsize) << "\n";
				}
			}
		}
	}

	void Shader::LoadPushConstants(ShaderPipeline& pipeline, const spirv_cross::SmallVector<spirv_cross::Resource>& resources)
	{
		for (const spirv_cross::Resource& resource : resources)
		{
			spirv_cross::SPIRType baseType = Compiler->get_type(resource.base_type_id);

			uint32_t size = (uint32_t)Compiler->get_declared_struct_size(baseType);

			std::cout << "\tpush constant size: " << size << "\n";

			VkPushConstantRange& pushConstant = pipeline.FetchPushConstant();

			if (pushConstant.size != 0 && pushConstant.size != size)
			{
				std::cout << "mismatching push constant size: " << size << " != " << pushConstant.size << "\n";
			}

			pushConstant.size = size;
			pushConstant.stageFlags |= Stage;
		}
	}

	void Shader::LoadShaderRecords(ShaderPipeline& pipeline, const spirv_cross::SmallVector<spirv_cross::Resource>& resources)
	{
		for (const spirv_cross::Resource& resource : resources)
		{
			spirv_cross::SPIRType baseType = Compiler->get_type(resource.base_type_id);

			uint32_t size = (uint32_t)Compiler->get_declared_struct_size(baseType);

			std::cout << "\tshader record size: " << size << "\n";

			pipeline.SetShaderRecordSize(size);
		}
	}

	void Shader::ReleaseResources()
	{
		if (Module == nullptr) return;

		vkDestroyShaderModule(VulkanContext->Device, Module, nullptr);

		Module = nullptr;
	}

	void Shader::ClearBuffers()
	{
		Source.clear();
		Source.shrink_to_fit();
		ByteCode.clear();
		ByteCode.shrink_to_fit();
	}

	void Shader::SetPath(const fs::path& shaderPath)
	{
		ShaderPath = shaderPath;
	}

	void Shader::SetSourceDirectory(const fs::path& sourcePath)
	{
		SourcePath = sourcePath;
	}

	void Shader::SetBinaryDirectory(const fs::path& binaryPath)
	{
		BinaryPath = binaryPath;
	}
	
	void Shader::SetShaderStage(VkShaderStageFlagBits stage)
	{
		Stage = stage;
	}

	fs::path Shader::GetBinaryPath() const
	{
		fs::path filePath = BinaryPath / ShaderPath;
		filePath += ".spv";

		return filePath;
	}
}