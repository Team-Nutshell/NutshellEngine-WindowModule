#include "ntsh_window_module.h"
#include "../external/Module/utils/ntsh_module_defines.h"
#include "../external/Module/utils/ntsh_dynamic_library.h"
#include "../external/Common/utils/ntsh_engine_defines.h"
#include "../external/Common/utils/ntsh_engine_enums.h"
#ifdef NTSH_OS_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif NTSH_OS_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#endif
#include "../external/glfw/include/GLFW/glfw3native.h"

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

void NutshellWindowModule::close() {
	glfwSetWindowShouldClose(m_window, true);
}

bool NutshellWindowModule::shouldClose() {
	return glfwWindowShouldClose(m_window);
}

void NutshellWindowModule::setSize(int width, int height) {
	glfwSetWindowSize(m_window, width, height);
	m_width = width;
	m_height = height;
}

int NutshellWindowModule::getWidth() {
	return m_width;
}

int NutshellWindowModule::getHeight() {
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

void NutshellWindowModule::pollEvents() {
	glfwPollEvents();
}

void NutshellWindowModule::setTitle(const std::string& title) {
	glfwSetWindowTitle(m_window, title.c_str());
}

void NutshellWindowModule::resizeInternal(int newWidth, int newHeight) {
	m_width = newWidth;
	m_height = newHeight;
}

#ifdef NTSH_OS_WINDOWS
HWND NutshellWindowModule::getNativeHandle() {
	return glfwGetWin32Window(m_window);
}
#elif NTSH_OS_LINUX
Window NutshellWindowModule::getNativeHandle() {
	return glfwGetX11Window(m_window);
}
#endif

extern "C" NTSH_MODULE_API NutshellWindowModuleInterface* createModule() {
	return new NutshellWindowModule;
}

extern "C" NTSH_MODULE_API void destroyModule(NutshellWindowModuleInterface* m) {
	delete m;
}