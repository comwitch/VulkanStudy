#pragma once

#include "lve_device.cpp"

//std
#include <string>
#include <vector>

namespace lve {

	struct PipelineConfigInfo {};

	class LvePipeline {


	public:
		LvePipeline(
			MyEngineDevice& device,
			const std::string& vertFilepath,
			const std::string& fragFilepath,
			const PipelineConfigInfo& configInfo);
		~LvePipeline() {}

		LvePipeline(const LvePipeline&) = delete;
		void operator=(const LvePipeline&) = delete;

		static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);
	
	private:
		static std::vector<char> readFile(const std::string& filepath);

		void createGraphicsPipeline(
			const std::string& vertFilepath,
			const std::string& fragFilepath,
			const PipelineConfigInfo& configInfo);

		void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

		MyEngineDevice& LveDevice;
		VkPipeline graphicPipeline;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;

	};
}