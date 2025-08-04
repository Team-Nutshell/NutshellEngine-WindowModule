#include "glfwwindow.h"
#include "../Common/utils/ntshengn_defines.h"

GLFWWindow::GLFWWindow(int width, int height, const std::string& title) {
	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	m_width = width;
	m_height = height;
	m_title = title;
	glfwGetWindowPos(m_window, &m_x, &m_y);
	glfwSetWindowUserPointer(m_window, this);

	glfwSetWindowPosCallback(m_window, windowPosCallback);
	glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
	glfwSetDropCallback(m_window, dropFilesCallback);
	glfwSetKeyCallback(m_window, keyboardKeyCallback);
	glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
	glfwSetCursorPosCallback(m_window, cursorPositionCallback);
	glfwSetScrollCallback(m_window, scrollCallback);
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

void GLFWWindow::update() {
	m_droppedFiles.clear();

	for (auto& key : m_keyStateMap) {
		key.second = nextInputState(key.second);
	}

	for (auto& button : m_mouseButtonStateMap) {
		button.second = nextInputState(button.second);
	}

	m_scrollX = 0.0f;
	m_scrollY = 0.0f;
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
		glfwGetWindowPos(m_window, &m_savedX, &m_savedY);
		glfwGetWindowSize(m_window, &m_savedWidth, &m_savedHeight);

		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
		glfwSetWindowMonitor(m_window, primaryMonitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
	}
	else if (!fullscreen && isFullscreen()) {
		glfwSetWindowMonitor(m_window, NULL, m_savedX, m_savedY, m_savedWidth, m_savedHeight, GLFW_DONT_CARE);
	}
}

bool GLFWWindow::isFullscreen() {
	return glfwGetWindowMonitor(m_window) != nullptr;
}

void GLFWWindow::setBorderless(bool borderless) {
	glfwSetWindowAttrib(m_window, GLFW_DECORATED, borderless ? GLFW_FALSE : GLFW_TRUE);
}

bool GLFWWindow::isBorderless() {
	return glfwGetWindowAttrib(m_window, GLFW_DECORATED) == GLFW_FALSE;
}

void GLFWWindow::setResizable(bool resizable) {
	glfwSetWindowAttrib(m_window, GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
}

bool GLFWWindow::isResizable() {
	return glfwGetWindowAttrib(m_window, GLFW_RESIZABLE) == GLFW_TRUE;
}

void GLFWWindow::setOpacity(float opacity) {
	glfwSetWindowOpacity(m_window, opacity);
}

float GLFWWindow::getOpacity() {
	return glfwGetWindowOpacity(m_window);
}

std::vector<std::string> GLFWWindow::getDroppedFiles() {
	return m_droppedFiles;
}

void GLFWWindow::setWindowFocus() {
	glfwFocusWindow(m_window);
}

bool GLFWWindow::isWindowFocused() {
	return glfwGetWindowAttrib(m_window, GLFW_FOCUSED) == GLFW_TRUE;
}

void GLFWWindow::setTitle(const std::string& title) {
	m_title = title;
	glfwSetWindowTitle(m_window, title.c_str());
}

std::string GLFWWindow::getTitle() {
	return m_title;
}

void GLFWWindow::setIcon(const NtshEngn::Image& image) {
	GLFWimage glfwImage;
	glfwImage.width = image.width;
	glfwImage.height = image.height;
	glfwImage.pixels = const_cast<uint8_t*>(image.data.data());
	glfwSetWindowIcon(m_window, 1, &glfwImage);
}

NtshEngn::InputState GLFWWindow::getKeyState(NtshEngn::InputKeyboardKey key) {
	return m_keyStateMap[m_keyMap[key]];
}

NtshEngn::InputState GLFWWindow::getMouseButtonState(NtshEngn::InputMouseButton mouseButton) {
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

float GLFWWindow::getMouseScrollOffsetX() {
	return m_scrollX;
}

float GLFWWindow::getMouseScrollOffsetY() {
	return m_scrollY;
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

void GLFWWindow::dropFilesInternal(std::vector<std::string>& droppedFiles) {
	m_droppedFiles = droppedFiles;
}

void GLFWWindow::keyboardKeyInternal(int key, int action) {
	if (m_keyStateMap.find(key) != m_keyStateMap.end()) {
		NtshEngn::InputState currentState = m_keyStateMap[key];
		if (((currentState == NtshEngn::InputState::None) || (currentState == NtshEngn::InputState::Released)) && (action == GLFW_PRESS)) {
			m_keyStateMap[key] = NtshEngn::InputState::Pressed;
			m_keyStateMap[GLFW_KEY_LAST + 1] = NtshEngn::InputState::Pressed; // Any
		}
		else if (((currentState == NtshEngn::InputState::Pressed) || (currentState == NtshEngn::InputState::Held)) && (action == GLFW_RELEASE)) {
			m_keyStateMap[key] = NtshEngn::InputState::Released;
			m_keyStateMap[GLFW_KEY_LAST + 1] = NtshEngn::InputState::Released; // Any
		}
	}
}

void GLFWWindow::mouseButtonInternal(int button, int action) {
	if (m_mouseButtonStateMap.find(button) != m_mouseButtonStateMap.end()) {
		NtshEngn::InputState currentState = m_mouseButtonStateMap[button];
		if (((currentState == NtshEngn::InputState::None) || (currentState == NtshEngn::InputState::Released)) && (action == GLFW_PRESS)) {
			m_mouseButtonStateMap[button] = NtshEngn::InputState::Pressed;
			m_mouseButtonStateMap[GLFW_MOUSE_BUTTON_LAST + 1] = NtshEngn::InputState::Pressed; // Any
		}
		else if (((currentState == NtshEngn::InputState::Pressed) || (currentState == NtshEngn::InputState::Held)) && (action == GLFW_RELEASE)) {
			m_mouseButtonStateMap[button] = NtshEngn::InputState::Released;
			m_mouseButtonStateMap[GLFW_MOUSE_BUTTON_LAST + 1] = NtshEngn::InputState::Released; // Any
		}
	}
}

void GLFWWindow::cursorPositionInternal(int x, int y) {
	m_cursorX = x;
	m_cursorY = y;
}

void GLFWWindow::scrollInternal(float x, float y) {
	m_scrollX = x;
	m_scrollY = y;
}

void GLFWWindow::windowCloseInternal() {
	close();
}

NtshEngn::InputState GLFWWindow::nextInputState(NtshEngn::InputState inputState) {
	if (inputState == NtshEngn::InputState::Pressed) {
		return NtshEngn::InputState::Held;
	}
	else if (inputState == NtshEngn::InputState::Released) {
		return NtshEngn::InputState::None;
	}

	return inputState;
}

NtshEngn::NativeWindowHandle GLFWWindow::getNativeHandle() {
#if defined(NTSHENGN_OS_WINDOWS)
	return glfwGetWin32Window(m_window);
#elif defined(NTSHENGN_OS_LINUX) || defined(NTSHENGN_OS_FREEBSD)
	return reinterpret_cast<NtshEngn::NativeWindowHandle>(glfwGetX11Window(m_window));
#endif
}

NtshEngn::NativeWindowAdditionalInformation GLFWWindow::getNativeAdditionalInformation() {
#if defined(NTSHENGN_OS_WINDOWS)
	return reinterpret_cast<NtshEngn::NativeWindowAdditionalInformation>(GetWindowLongPtr(glfwGetWin32Window(m_window), GWLP_HINSTANCE));
#elif defined(NTSHENGN_OS_LINUX) || defined(NTSHENGN_OS_FREEBSD)
	return glfwGetX11Display();
#endif
}
