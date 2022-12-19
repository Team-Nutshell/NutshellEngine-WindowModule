#include "ntsh_window_module.h"
#include "../external/Module/utils/ntsh_module_defines.h"
#include "../external/Module/utils/ntsh_dynamic_library.h"
#include "../external/Common/utils/ntsh_engine_defines.h"
#include "../external/Common/utils/ntsh_engine_enums.h"
#if defined(NTSH_OS_WINDOWS)
#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(NTSH_OS_LINUX)
#define GLFW_EXPOSE_NATIVE_X11
#endif
#include "../external/glfw/include/GLFW/glfw3native.h"

GLFWWindow::GLFWWindow(int width, int height, const std::string& title) {
	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	m_width = width;
	m_height = height;
	glfwGetWindowPos(m_window, &m_x, &m_y);
	glfwSetWindowUserPointer(m_window, this);

	glfwSetWindowPosCallback(m_window, windowPosCallback);
	glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
	glfwSetKeyCallback(m_window, keyboardKeyCallback);
	glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
	glfwSetCursorPosCallback(m_window, cursorPositionCallback);
	glfwSetWindowCloseCallback(m_window, windowCloseCallback);
}

GLFWWindow::~GLFWWindow() {
	glfwDestroyWindow(m_window);
}

void GLFWWindow::close() {
	glfwSetWindowShouldClose(m_window, true);
}

bool GLFWWindow::shouldClose() {
	return glfwWindowShouldClose(m_window);
}

void GLFWWindow::updateInputs(double dt) {
	NTSH_UNUSED(dt);

	for (auto& key : m_keyStateMap) {
		key.second = nextInputState(key.second);
	}

	for (auto& key : m_mouseButtonStateMap) {
		key.second = nextInputState(key.second);
	}
}

void GLFWWindow::setSize(int width, int height) {
	glfwSetWindowSize(m_window, width, height);
	m_width = width;
	m_height = height;
}

int GLFWWindow::getWidth() {
	return m_width;
}

int GLFWWindow::getHeight() {
	return m_height;
}

void GLFWWindow::setPosition(int x, int y) {
	glfwSetWindowPos(m_window, x, y);
	m_x = x;
	m_y = y;
}

int GLFWWindow::getPositionX() {
	return m_x;
}

int GLFWWindow::getPositionY() {
	return m_y;
}

void GLFWWindow::setFullscreen(bool fullscreen) {
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

bool GLFWWindow::isFullscreen() {
	return glfwGetWindowMonitor(m_window) != nullptr;
}

void GLFWWindow::setTitle(const std::string& title) {
	glfwSetWindowTitle(m_window, title.c_str());
}

NtshInputState GLFWWindow::getKeyState(NtshInputKeyboardKey key) {
	return m_keyStateMap[m_keyMap[key]];
}

NtshInputState GLFWWindow::getMouseButtonState(NtshInputMouseButton mouseButton) {
	return m_mouseButtonStateMap[m_mouseButtonMap[mouseButton]];
}

void GLFWWindow::setCursorPosition(int x, int y) {
	glfwSetCursorPos(m_window, static_cast<double>(x), static_cast<double>(y));
	m_cursorX = x;
	m_cursorY = y;
}

int GLFWWindow::getCursorPositionX() {
	return m_cursorX;
}

int GLFWWindow::getCursorPositionY() {
	return m_cursorY;
}

void GLFWWindow::setCursorVisibility(bool visible) {
	if (!isCursorVisible() && visible) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_cursorVisible = true;
	}
	else if (isCursorVisible() && !visible) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		m_cursorVisible = false;
	}
}

bool GLFWWindow::isCursorVisible() {
	return m_cursorVisible;
}

void GLFWWindow::windowPosInternal(int newXPos, int newYPos) {
	m_x = newXPos;
	m_y = newYPos;
}

void GLFWWindow::resizeInternal(int newWidth, int newHeight) {
	m_width = newWidth;
	m_height = newHeight;
}

void GLFWWindow::keyboardKeyInternal(int key, int action) {
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

void GLFWWindow::mouseButtonInternal(int button, int action) {
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

void GLFWWindow::cursorPositionInternal(int x, int y) {
	m_cursorX = x;
	m_cursorY = y;
}

void GLFWWindow::windowCloseInternal() {
	close();
}

NtshInputState GLFWWindow::nextInputState(NtshInputState inputState) {
	if (inputState == NtshInputState::Pressed) {
		return NtshInputState::Held;
	}
	else if (inputState == NtshInputState::Released) {
		return NtshInputState::None;
	}

	return inputState;
}

#if defined(NTSH_OS_WINDOWS)
HWND GLFWWindow::getNativeHandle() {
	return glfwGetWin32Window(m_window);
}
#elif defined(NTSH_OS_LINUX)
Window GLFWWindow::getNativeHandle() {
	return glfwGetX11Window(m_window);
}
#endif