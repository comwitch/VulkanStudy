#pragma once

#include "lve_window.h"
#include "lve_pipeline.h"

namespace lve {
	class First_app
	{
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		void run();

	private:
		LveWindow LveWindow{ WIDTH, HEIGHT, "Hello Vulkan!!" };
		LvePipeline LvePipeline{ "Shaders/simple_shader.vert.spv", "Shaders/simple_shader.frag.spv" };
	};


}//namespace lve

