#pragma once
#include "../external/glfw/include/GLFW/glfw3.h"
#include "../external/Common/utils/ntshengn_defines.h"
#include "../external/Common/resources/ntshengn_resources_window.h"
#if defined(NTSHENGN_OS_WINDOWS)
#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(NTSHENGN_OS_LINUX)
#define GLFW_EXPOSE_NATIVE_X11
#endif
#include "../external/glfw/include/GLFW/glfw3native.h"
#if defined(NTSHENGN_OS_LINUX)
#undef None
#undef Success
#endif
#include <string>
#include <unordered_map>


class GLFWWindow {
public:
	GLFWWindow(int width, int height, const std::string& title);
	~GLFWWindow();

	void close();
	bool shouldClose();

	void updateInputs(double dt);

	void setSize(int width, int height);
	int getWidth();
	int getHeight();

	void setPosition(int x, int y);
	int getPositionX();
	int getPositionY();

	void setFullscreen(bool fullscreen);
	bool isFullscreen();

	void setTitle(const std::string& title);

	NtshEngn::InputState getKeyState(NtshEngn::InputKeyboardKey key);
	NtshEngn::InputState getMouseButtonState(NtshEngn::InputMouseButton mouseButton);

	void setCursorPosition(int x, int y);
	int getCursorPositionX();
	int getCursorPositionY();

	void setCursorVisibility(bool visible);
	bool isCursorVisible();

	NtshEngn::NativeWindowHandle getNativeHandle();
	NtshEngn::NativeWindowAdditionalInformation getNativeAdditionalInformation();

private:
	// Window position internal function used by callback
	void windowPosInternal(int newXPos, int newYPos);

	// Window resize internal function used by callback
	void resizeInternal(int newWidth, int newHeight);

	// Keyboard key input internal function used by callback
	void keyboardKeyInternal(int key, int action);

	// Mouse button input internal function used by callback
	void mouseButtonInternal(int button, int action);

	// Mouse position internal function used by callback
	void cursorPositionInternal(int x, int y);

	// Window close internal function used by callback
	void windowCloseInternal();

	// Returns the next input state (Pressed -> Held, Released -> None)
	NtshEngn::InputState nextInputState(NtshEngn::InputState inputState);

private:
	// Position callback
	static void windowPosCallback(GLFWwindow* window, int xpos, int ypos) {
		auto ptr = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
		ptr->windowPosInternal(xpos, ypos);
	}

	// Resize callback
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
		auto ptr = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
		ptr->resizeInternal(width, height);
	}

	// Keyboard key callback
	static void keyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		NTSHENGN_UNUSED(scancode);
		NTSHENGN_UNUSED(mods);
		auto ptr = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
		ptr->keyboardKeyInternal(key, action);
	}

	// Mouse button callback
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		NTSHENGN_UNUSED(mods);
		auto ptr = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
		ptr->mouseButtonInternal(button, action);
	}

	// Mouse cursor position callback
	static void cursorPositionCallback(GLFWwindow* window, double x, double y) {
		auto ptr = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
		ptr->cursorPositionInternal(static_cast<int>(x), static_cast<int>(y));
	}

	// Window close callback
	static void windowCloseCallback(GLFWwindow* window) {
		auto ptr = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
		ptr->windowCloseInternal();
	}

private:
	GLFWwindow* m_window = nullptr;
	int m_width;
	int m_height;
	int m_x = 0;
	int m_y = 0;
	int m_cursorX = 0;
	int m_cursorY = 0;
	bool m_cursorVisible = true;

	std::unordered_map<NtshEngn::InputKeyboardKey, int> m_keyMap = { { NtshEngn::InputKeyboardKey::A, GLFW_KEY_A },
		{ NtshEngn::InputKeyboardKey::B, GLFW_KEY_B },
		{ NtshEngn::InputKeyboardKey::C, GLFW_KEY_C },
		{ NtshEngn::InputKeyboardKey::D, GLFW_KEY_D },
		{ NtshEngn::InputKeyboardKey::E, GLFW_KEY_E },
		{ NtshEngn::InputKeyboardKey::F, GLFW_KEY_F },
		{ NtshEngn::InputKeyboardKey::G, GLFW_KEY_G },
		{ NtshEngn::InputKeyboardKey::H, GLFW_KEY_H },
		{ NtshEngn::InputKeyboardKey::I, GLFW_KEY_I },
		{ NtshEngn::InputKeyboardKey::J, GLFW_KEY_J },
		{ NtshEngn::InputKeyboardKey::K, GLFW_KEY_K },
		{ NtshEngn::InputKeyboardKey::L, GLFW_KEY_L },
		{ NtshEngn::InputKeyboardKey::M, GLFW_KEY_M },
		{ NtshEngn::InputKeyboardKey::N, GLFW_KEY_N },
		{ NtshEngn::InputKeyboardKey::O, GLFW_KEY_O },
		{ NtshEngn::InputKeyboardKey::P, GLFW_KEY_P },
		{ NtshEngn::InputKeyboardKey::Q, GLFW_KEY_Q },
		{ NtshEngn::InputKeyboardKey::R, GLFW_KEY_R },
		{ NtshEngn::InputKeyboardKey::S, GLFW_KEY_S },
		{ NtshEngn::InputKeyboardKey::T, GLFW_KEY_T },
		{ NtshEngn::InputKeyboardKey::U, GLFW_KEY_U },
		{ NtshEngn::InputKeyboardKey::V, GLFW_KEY_V },
		{ NtshEngn::InputKeyboardKey::W, GLFW_KEY_W },
		{ NtshEngn::InputKeyboardKey::X, GLFW_KEY_X },
		{ NtshEngn::InputKeyboardKey::Y, GLFW_KEY_Y },
		{ NtshEngn::InputKeyboardKey::Z, GLFW_KEY_Z },
		{ NtshEngn::InputKeyboardKey::Space, GLFW_KEY_SPACE },
		{ NtshEngn::InputKeyboardKey::Shift, GLFW_KEY_LEFT_SHIFT },
		{ NtshEngn::InputKeyboardKey::LeftCtrl, GLFW_KEY_LEFT_CONTROL },
		{ NtshEngn::InputKeyboardKey::RightCtrl, GLFW_KEY_RIGHT_CONTROL },
		{ NtshEngn::InputKeyboardKey::Alt, GLFW_KEY_LEFT_ALT },
		{ NtshEngn::InputKeyboardKey::Escape, GLFW_KEY_ESCAPE },
		{ NtshEngn::InputKeyboardKey::Tab, GLFW_KEY_TAB },
		{ NtshEngn::InputKeyboardKey::Backspace, GLFW_KEY_BACKSPACE },
		{ NtshEngn::InputKeyboardKey::Return, GLFW_KEY_ENTER },
		{ NtshEngn::InputKeyboardKey::Enter, GLFW_KEY_ENTER },
		{ NtshEngn::InputKeyboardKey::Num0, GLFW_KEY_KP_0 },
		{ NtshEngn::InputKeyboardKey::Num1, GLFW_KEY_KP_1 },
		{ NtshEngn::InputKeyboardKey::Num2, GLFW_KEY_KP_2 },
		{ NtshEngn::InputKeyboardKey::Num3, GLFW_KEY_KP_3 },
		{ NtshEngn::InputKeyboardKey::Num4, GLFW_KEY_KP_4 },
		{ NtshEngn::InputKeyboardKey::Num5, GLFW_KEY_KP_5 },
		{ NtshEngn::InputKeyboardKey::Num6, GLFW_KEY_KP_6 },
		{ NtshEngn::InputKeyboardKey::Num7, GLFW_KEY_KP_7 },
		{ NtshEngn::InputKeyboardKey::Num8, GLFW_KEY_KP_8 },
		{ NtshEngn::InputKeyboardKey::Num9, GLFW_KEY_KP_9 },
		{ NtshEngn::InputKeyboardKey::Left, GLFW_KEY_LEFT },
		{ NtshEngn::InputKeyboardKey::Right, GLFW_KEY_RIGHT },
		{ NtshEngn::InputKeyboardKey::Up, GLFW_KEY_UP },
		{ NtshEngn::InputKeyboardKey::Down, GLFW_KEY_DOWN },
		{ NtshEngn::InputKeyboardKey::F1, GLFW_KEY_F1 },
		{ NtshEngn::InputKeyboardKey::F2, GLFW_KEY_F2 },
		{ NtshEngn::InputKeyboardKey::F3, GLFW_KEY_F3 },
		{ NtshEngn::InputKeyboardKey::F4, GLFW_KEY_F4 },
		{ NtshEngn::InputKeyboardKey::F5, GLFW_KEY_F5 },
		{ NtshEngn::InputKeyboardKey::F6, GLFW_KEY_F6 },
		{ NtshEngn::InputKeyboardKey::F7, GLFW_KEY_F7 },
		{ NtshEngn::InputKeyboardKey::F8, GLFW_KEY_F8 },
		{ NtshEngn::InputKeyboardKey::F9, GLFW_KEY_F9 },
		{ NtshEngn::InputKeyboardKey::F10, GLFW_KEY_F10 },
		{ NtshEngn::InputKeyboardKey::F11, GLFW_KEY_F11 },
		{ NtshEngn::InputKeyboardKey::F12, GLFW_KEY_F12 }
	};
	std::unordered_map<int, NtshEngn::InputState> m_keyStateMap = { { GLFW_KEY_A, NtshEngn::InputState::None },
		{ GLFW_KEY_B, NtshEngn::InputState::None },
		{ GLFW_KEY_C, NtshEngn::InputState::None },
		{ GLFW_KEY_D, NtshEngn::InputState::None },
		{ GLFW_KEY_E, NtshEngn::InputState::None },
		{ GLFW_KEY_F, NtshEngn::InputState::None },
		{ GLFW_KEY_G, NtshEngn::InputState::None },
		{ GLFW_KEY_H, NtshEngn::InputState::None },
		{ GLFW_KEY_I, NtshEngn::InputState::None },
		{ GLFW_KEY_J, NtshEngn::InputState::None },
		{ GLFW_KEY_K, NtshEngn::InputState::None },
		{ GLFW_KEY_L, NtshEngn::InputState::None },
		{ GLFW_KEY_M, NtshEngn::InputState::None },
		{ GLFW_KEY_N, NtshEngn::InputState::None },
		{ GLFW_KEY_O, NtshEngn::InputState::None },
		{ GLFW_KEY_P, NtshEngn::InputState::None },
		{ GLFW_KEY_Q, NtshEngn::InputState::None },
		{ GLFW_KEY_R, NtshEngn::InputState::None },
		{ GLFW_KEY_S, NtshEngn::InputState::None },
		{ GLFW_KEY_T, NtshEngn::InputState::None },
		{ GLFW_KEY_U, NtshEngn::InputState::None },
		{ GLFW_KEY_V, NtshEngn::InputState::None },
		{ GLFW_KEY_W, NtshEngn::InputState::None },
		{ GLFW_KEY_X, NtshEngn::InputState::None },
		{ GLFW_KEY_Y, NtshEngn::InputState::None },
		{ GLFW_KEY_Z, NtshEngn::InputState::None },
		{ GLFW_KEY_SPACE, NtshEngn::InputState::None },
		{ GLFW_KEY_LEFT_SHIFT, NtshEngn::InputState::None },
		{ GLFW_KEY_LEFT_CONTROL, NtshEngn::InputState::None },
		{ GLFW_KEY_RIGHT_CONTROL, NtshEngn::InputState::None },
		{ GLFW_KEY_LEFT_ALT, NtshEngn::InputState::None },
		{ GLFW_KEY_ESCAPE, NtshEngn::InputState::None },
		{ GLFW_KEY_TAB, NtshEngn::InputState::None },
		{ GLFW_KEY_BACKSPACE, NtshEngn::InputState::None },
		{ GLFW_KEY_ENTER, NtshEngn::InputState::None },
		{ GLFW_KEY_KP_0, NtshEngn::InputState::None },
		{ GLFW_KEY_KP_1, NtshEngn::InputState::None },
		{ GLFW_KEY_KP_2, NtshEngn::InputState::None },
		{ GLFW_KEY_KP_3, NtshEngn::InputState::None },
		{ GLFW_KEY_KP_4, NtshEngn::InputState::None },
		{ GLFW_KEY_KP_5, NtshEngn::InputState::None },
		{ GLFW_KEY_KP_6, NtshEngn::InputState::None },
		{ GLFW_KEY_KP_7, NtshEngn::InputState::None },
		{ GLFW_KEY_KP_8, NtshEngn::InputState::None },
		{ GLFW_KEY_KP_9, NtshEngn::InputState::None },
		{ GLFW_KEY_LEFT, NtshEngn::InputState::None },
		{ GLFW_KEY_RIGHT, NtshEngn::InputState::None },
		{ GLFW_KEY_UP, NtshEngn::InputState::None },
		{ GLFW_KEY_DOWN, NtshEngn::InputState::None },
		{ GLFW_KEY_F1, NtshEngn::InputState::None },
		{ GLFW_KEY_F2, NtshEngn::InputState::None },
		{ GLFW_KEY_F3, NtshEngn::InputState::None },
		{ GLFW_KEY_F4, NtshEngn::InputState::None },
		{ GLFW_KEY_F5, NtshEngn::InputState::None },
		{ GLFW_KEY_F6, NtshEngn::InputState::None },
		{ GLFW_KEY_F7, NtshEngn::InputState::None },
		{ GLFW_KEY_F8, NtshEngn::InputState::None },
		{ GLFW_KEY_F9, NtshEngn::InputState::None },
		{ GLFW_KEY_F10, NtshEngn::InputState::None },
		{ GLFW_KEY_F11, NtshEngn::InputState::None },
		{ GLFW_KEY_F12, NtshEngn::InputState::None }
	};

	std::unordered_map<NtshEngn::InputMouseButton, int> m_mouseButtonMap = { { NtshEngn::InputMouseButton::One, GLFW_MOUSE_BUTTON_1 },
		{ NtshEngn::InputMouseButton::Two, GLFW_MOUSE_BUTTON_2 },
		{ NtshEngn::InputMouseButton::Three, GLFW_MOUSE_BUTTON_3 },
		{ NtshEngn::InputMouseButton::Four, GLFW_MOUSE_BUTTON_4 },
		{ NtshEngn::InputMouseButton::Five, GLFW_MOUSE_BUTTON_5 },
		{ NtshEngn::InputMouseButton::Six, GLFW_MOUSE_BUTTON_6 },
		{ NtshEngn::InputMouseButton::Seven, GLFW_MOUSE_BUTTON_7 },
		{ NtshEngn::InputMouseButton::Eight, GLFW_MOUSE_BUTTON_8 }
	};
	std::unordered_map<int, NtshEngn::InputState> m_mouseButtonStateMap = { { GLFW_MOUSE_BUTTON_1, NtshEngn::InputState::None },
		{ GLFW_MOUSE_BUTTON_2, NtshEngn::InputState::None },
		{ GLFW_MOUSE_BUTTON_3, NtshEngn::InputState::None },
		{ GLFW_MOUSE_BUTTON_4, NtshEngn::InputState::None },
		{ GLFW_MOUSE_BUTTON_5, NtshEngn::InputState::None },
		{ GLFW_MOUSE_BUTTON_6, NtshEngn::InputState::None },
		{ GLFW_MOUSE_BUTTON_7, NtshEngn::InputState::None },
		{ GLFW_MOUSE_BUTTON_8, NtshEngn::InputState::None }
	};
};