#include "lve_pipeline.h"

//std
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace lve {
	
	// init


	LvePipeline::LvePipeline(LveDevice& device,const std::string& vertFilepath,const std::string& fragFilepath,const PipelineConfigInfo& configInfo) : lveDevice{device}
	{
		createGraphicsPipeline(vertFilepath, fragFilepath, configInfo);
	}



	PipelineConfigInfo LvePipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height)
	{
		PipelineConfigInfo configInfo{};

		return configInfo;
	}
	/*
	* readFile
	*/
	std::vector<char> LvePipeline::readFile(const std::string& filepath) 
	{
		std::ifstream file{ filepath, std::ios::ate | std::ios::binary };

		if (!file.is_open()) 
		{
			throw std::runtime_error("failed to open file: " + filepath);
		}

		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();
		return buffer;
	}

	void LvePipeline::createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo)
	{
		auto vertCode = readFile(vertFilepath);
		auto fragCode = readFile(fragFilepath);

		std::cout << "Vertex Shader Code Size: " << vertCode.size() << std::endl;
		std::cout << "fragCode  Shader Code Size: " << fragCode.size() << std::endl;
	}

	void LvePipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule)
	{
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO; // create structure type ��
		createInfo.codeSize = code.size(); //vector array�� code size
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data()); //�츮�� �� �ڵ��� ������ �ּ� uint32_t int32�� �ٸ���. c stayle character array ��������

		if (vkCreateShaderModule(lveDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create shader module");
		}
	}


}


