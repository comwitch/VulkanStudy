#include "first_app.h"

namespace lve {

	void First_app::run() {
		while (!LveWindow.shouldClose())
		{
			glfwPollEvents();
		}


	}
}
