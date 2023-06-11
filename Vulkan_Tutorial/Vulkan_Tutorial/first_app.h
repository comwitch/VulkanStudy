#pragma once

#include "lve_window.h"
#include "lve_pipeline.h"
#include "lve_device.hpp"
#include "lve_swap_chain.h"

#include <memory>
#include <vector>

namespace lve {
	class First_app
	{
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		First_app();
		~First_app();

		First_app(const First_app&) = delete;
		First_app& operator=(const First_app&) = delete;

		void run();

	private:
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();

		LveWindow LveWindow{ WIDTH, HEIGHT, "Hello Vulkan!!" };
		LveDevice LveDevice{ LveWindow };
		lveSwapChain lveSwapChain{ LveDevice, LveWindow.getExtent() };
		std::unique_ptr<LvePipeline> lvePipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
		
	};


}//namespace lve

