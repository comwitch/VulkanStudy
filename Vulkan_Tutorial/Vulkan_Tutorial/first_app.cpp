#include "first_app.h"

#include <stdexcept>

namespace lve {
	First_app::First_app()
	{
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
	}
	First_app::~First_app()
	{
		vkDestroyPipelineLayout(LveDevice.device(), pipelineLayout, nullptr);
	}
	void First_app::run() {
		while (!LveWindow.shouldClose())
		{
			glfwPollEvents();
		}


	}
	void First_app::createPipelineLayout()
	{
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;
		if (vkCreatePipelineLayout(LveDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout)
			!= VK_SUCCESS)
		{
			throw std::runtime_error("tuna tuna failed to create pipeline layout!");
		}
	}
	void First_app::createPipeline()
	{
		auto pipelineConfig =
			LvePipeline::defaultPipelineConfigInfo(lveSwapChain.width(), lveSwapChain.height());
		pipelineConfig.renderPass = lveSwapChain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		lvePipeline = std::make_unique<LvePipeline>(
			LveDevice,
			"Shaders/simple_shader.vert.spv",
			"Shaders/simple_shader.frag.spv",
			pipelineConfig);
	}
	void First_app::createCommandBuffers()
	{

	}
	void First_app::drawFrame()
	{
	}
}
