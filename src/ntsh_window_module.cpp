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
	glfwSetKeyCallback(m_window, keyboardKeyCallback);
	glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
	glfwSetCursorPosCallback(m_window, cursorPositionCallback);
}

void NutshellWindowModule::update(double dt) {
	NTSH_UNUSED(dt);

	for (auto& key : m_keyStateMap) {
		key.second = nextInputState(key.second);
	}

	for (auto& key : m_mouseButtonStateMap) {
		key.second = nextInputState(key.second);
	}

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

NtshInputState NutshellWindowModule::getKeyState(NtshInputKeyboardKey key) {
	return m_keyStateMap[m_keyMap[key]];
}

NtshInputState NutshellWindowModule::getButtonState(NtshInputMouseButton button) {
	return m_mouseButtonStateMap[m_mouseButtonMap[button]];
}

void NutshellWindowModule::setCursorPosition(int x, int y) {
	glfwSetCursorPos(m_window, static_cast<double>(x), static_cast<double>(y));
	m_cursorX = x;
	m_cursorY = y;
}

int NutshellWindowModule::getCursorXPosition() {
	return m_cursorX;
}

int NutshellWindowModule::getCursorYPosition() {
	return m_cursorY;
}

bool NutshellWindowModule::isCursorVisible() {
	return m_cursorVisible;
}

void NutshellWindowModule::setCursorVisibility(bool visible) {
	if (!isCursorVisible() && visible) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_cursorVisible = true;
	}
	else if (isCursorVisible() && !visible) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		m_cursorVisible = false;
	}
}

void NutshellWindowModule::resizeInternal(int newWidth, int newHeight) {
	m_width = newWidth;
	m_height = newHeight;
}

void NutshellWindowModule::keyboardKeyInternal(int key, int action) {
	if (m_keyStateMap.find(key) != m_keyStateMap.end()) {
		NtshInputState currentState = m_keyStateMap[key];
		if ((currentState == NtshInputState::None || currentState == NtshInputState::Released) && action == GLFW_PRESS) {
			m_keyStateMap[key] = NtshInputState::Pressed;
		}
		else if ((currentState == NtshInputState::Pressed || currentState == NtshInputState::Held) && action == GLFW_RELEASE) {
			m_keyStateMap[key] = NtshInputState::Released;
		}
	}
}

void NutshellWindowModule::mouseButtonInternal(int button, int action) {
	if (m_mouseButtonStateMap.find(button) != m_mouseButtonStateMap.end()) {
		NtshInputState currentState = m_mouseButtonStateMap[button];
		if ((currentState == NtshInputState::None || currentState == NtshInputState::Released) && action == GLFW_PRESS) {
			m_mouseButtonStateMap[button] = NtshInputState::Pressed;
		}
		else if ((currentState == NtshInputState::Pressed || currentState == NtshInputState::Held) && action == GLFW_RELEASE) {
			m_mouseButtonStateMap[button] = NtshInputState::Released;
		}
	}
}

void NutshellWindowModule::cursorPositionInternal(int x, int y) {
	m_cursorX = x;
	m_cursorY = y;
}

NtshInputState NutshellWindowModule::nextInputState(NtshInputState inputState) {
	if (inputState == NtshInputState::Pressed) {
		return NtshInputState::Held;
	}
	else if (inputState == NtshInputState::Released) {
		return NtshInputState::None;
	}

	return inputState;
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