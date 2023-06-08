#pragma once

#include "lve_device.cpp"

//std
#include <string>
#include <vector>

namespace lve {

	struct PiplineConfigInfo {};

	class LvePipeline {


	public:
		LvePipeline(const std::string& vertFilepath, const std::string& fragFilepath);
	
	private:
		static std::vector<char> readFile(const std::string& filepath);

		void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath);

	
	};
}