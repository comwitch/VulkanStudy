#pragma once

#include "lve_window.h"
#include "lve_pipeline.h"
#include "lve_device.hpp"

namespace lve {
	class First_app
	{
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		void run();

	private:
		LveWindow LveWindow{ WIDTH, HEIGHT, "Hello Vulkan!!" };
		MyEngineDevice LveDevice{ LveWindow };
		LvePipeline LvePipeline{ LveDevice, "Shaders/simple_shader.vert.spv", "Shaders/simple_shader.frag.spv", LvePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
	};


}//namespace lve

