#include "ntsh_window_module.h"
#include "../external/Module/ntsh_module_defines.h"
#include "../external/Module/ntsh_dynamic_library.h"
#include "../external/Common/ntsh_engine_enums.h"

void NutshellWindowModule::init() {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	m_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), nullptr, nullptr);
	glfwGetWindowPos(m_window, &m_x, &m_y);
	glfwSetWindowUserPointer(m_window, this);
	
	glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
}

void NutshellWindowModule::update(double dt) {
	NTSH_UNUSED(dt);
	glfwPollEvents();
}

void NutshellWindowModule::destroy() {
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void NutshellWindowModule::closeWindow() {
	glfwSetWindowShouldClose(m_window, true);
}

bool NutshellWindowModule::shouldClose() {
	return glfwWindowShouldClose(m_window);
}

void NutshellWindowModule::setWindowSize(int width, int height) {
	glfwSetWindowSize(m_window, width, height);
	m_width = width;
	m_height = height;
}

int NutshellWindowModule::getWindowWidth() {
	return m_width;
}

int NutshellWindowModule::getWindowHeight() {
	return m_height;
}

bool NutshellWindowModule::isFullscreen() {
	return glfwGetWindowMonitor(m_window) != nullptr;
}

void NutshellWindowModule::setFullscreen(bool fullscreen) {
	if (!isFullscreen() && fullscreen) {
		glfwGetWindowPos(m_window, &m_x, &m_y);
		glfwGetWindowSize(m_window, &m_width, &m_height);

		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
		glfwSetWindowMonitor(m_window, primaryMonitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
	}
	else if (!fullscreen && isFullscreen()) {
		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		glfwSetWindowMonitor(m_window, primaryMonitor, m_x, m_y, m_width, m_height, GLFW_DONT_CARE);
	}
}

void NutshellWindowModule::setTitle(const std::string& title) {
	NTSH_UNUSED(title);
	NTSH_MODULE_WARNING("setTitle() function not implemented.");
}

void NutshellWindowModule::resizeInternal(int newWidth, int newHeight) {
	m_width = newWidth;
	m_height = newHeight;
}

extern "C" NTSH_MODULE_API NutshellWindowModuleInterface* createModule() {
	return new NutshellWindowModule;
}

extern "C" NTSH_MODULE_API void destroyModule(NutshellWindowModuleInterface* m) {
	delete m;
}