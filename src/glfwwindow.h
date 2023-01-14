#pragma once
#include "../external/glfw/include/GLFW/glfw3.h"
#include "../external/Common/utils/ntsh_engine_defines.h"
#include "../external/Common/utils/ntsh_engine_input_enums.h"
#if defined(NTSH_OS_WINDOWS)
#include <windows.h>
#elif defined(NTSH_OS_LINUX)
#include <X11/Xlib.h>
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

	Ntsh::InputState getKeyState(Ntsh::InputKeyboardKey key);
	Ntsh::InputState getMouseButtonState(Ntsh::InputMouseButton mouseButton);

	void setCursorPosition(int x, int y);
	int getCursorPositionX();
	int getCursorPositionY();

	void setCursorVisibility(bool visible);
	bool isCursorVisible();

#if defined(NTSH_OS_WINDOWS)
	// Returns the native Win32 window handle
	HWND getNativeHandle();
#elif defined(NTSH_OS_LINUX)
	// Returns the native X window handle
	Window getNativeHandle();
#endif

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
	Ntsh::InputState nextInputState(Ntsh::InputState inputState);

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
		NTSH_UNUSED(scancode);
		NTSH_UNUSED(mods);
		auto ptr = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
		ptr->keyboardKeyInternal(key, action);
	}

	// Mouse button callback
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		NTSH_UNUSED(mods);
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

	std::unordered_map<Ntsh::InputKeyboardKey, int> m_keyMap = { { Ntsh::InputKeyboardKey::A, GLFW_KEY_A },
		{ Ntsh::InputKeyboardKey::B, GLFW_KEY_B },
		{ Ntsh::InputKeyboardKey::C, GLFW_KEY_C },
		{ Ntsh::InputKeyboardKey::D, GLFW_KEY_D },
		{ Ntsh::InputKeyboardKey::E, GLFW_KEY_E },
		{ Ntsh::InputKeyboardKey::F, GLFW_KEY_F },
		{ Ntsh::InputKeyboardKey::G, GLFW_KEY_G },
		{ Ntsh::InputKeyboardKey::H, GLFW_KEY_H },
		{ Ntsh::InputKeyboardKey::I, GLFW_KEY_I },
		{ Ntsh::InputKeyboardKey::J, GLFW_KEY_J },
		{ Ntsh::InputKeyboardKey::K, GLFW_KEY_K },
		{ Ntsh::InputKeyboardKey::L, GLFW_KEY_L },
		{ Ntsh::InputKeyboardKey::M, GLFW_KEY_M },
		{ Ntsh::InputKeyboardKey::N, GLFW_KEY_N },
		{ Ntsh::InputKeyboardKey::O, GLFW_KEY_O },
		{ Ntsh::InputKeyboardKey::P, GLFW_KEY_P },
		{ Ntsh::InputKeyboardKey::Q, GLFW_KEY_Q },
		{ Ntsh::InputKeyboardKey::R, GLFW_KEY_R },
		{ Ntsh::InputKeyboardKey::S, GLFW_KEY_S },
		{ Ntsh::InputKeyboardKey::T, GLFW_KEY_T },
		{ Ntsh::InputKeyboardKey::U, GLFW_KEY_U },
		{ Ntsh::InputKeyboardKey::V, GLFW_KEY_V },
		{ Ntsh::InputKeyboardKey::W, GLFW_KEY_W },
		{ Ntsh::InputKeyboardKey::X, GLFW_KEY_X },
		{ Ntsh::InputKeyboardKey::Y, GLFW_KEY_Y },
		{ Ntsh::InputKeyboardKey::Z, GLFW_KEY_Z },
		{ Ntsh::InputKeyboardKey::Space, GLFW_KEY_SPACE },
		{ Ntsh::InputKeyboardKey::Shift, GLFW_KEY_LEFT_SHIFT },
		{ Ntsh::InputKeyboardKey::LeftCtrl, GLFW_KEY_LEFT_CONTROL },
		{ Ntsh::InputKeyboardKey::RightCtrl, GLFW_KEY_RIGHT_CONTROL },
		{ Ntsh::InputKeyboardKey::Alt, GLFW_KEY_LEFT_ALT },
		{ Ntsh::InputKeyboardKey::Escape, GLFW_KEY_ESCAPE },
		{ Ntsh::InputKeyboardKey::Tab, GLFW_KEY_TAB },
		{ Ntsh::InputKeyboardKey::Backspace, GLFW_KEY_BACKSPACE },
		{ Ntsh::InputKeyboardKey::Return, GLFW_KEY_ENTER },
		{ Ntsh::InputKeyboardKey::Enter, GLFW_KEY_ENTER },
		{ Ntsh::InputKeyboardKey::Num0, GLFW_KEY_KP_0 },
		{ Ntsh::InputKeyboardKey::Num1, GLFW_KEY_KP_1 },
		{ Ntsh::InputKeyboardKey::Num2, GLFW_KEY_KP_2 },
		{ Ntsh::InputKeyboardKey::Num3, GLFW_KEY_KP_3 },
		{ Ntsh::InputKeyboardKey::Num4, GLFW_KEY_KP_4 },
		{ Ntsh::InputKeyboardKey::Num5, GLFW_KEY_KP_5 },
		{ Ntsh::InputKeyboardKey::Num6, GLFW_KEY_KP_6 },
		{ Ntsh::InputKeyboardKey::Num7, GLFW_KEY_KP_7 },
		{ Ntsh::InputKeyboardKey::Num8, GLFW_KEY_KP_8 },
		{ Ntsh::InputKeyboardKey::Num9, GLFW_KEY_KP_9 },
		{ Ntsh::InputKeyboardKey::Left, GLFW_KEY_LEFT },
		{ Ntsh::InputKeyboardKey::Right, GLFW_KEY_RIGHT },
		{ Ntsh::InputKeyboardKey::Up, GLFW_KEY_UP },
		{ Ntsh::InputKeyboardKey::Down, GLFW_KEY_DOWN },
		{ Ntsh::InputKeyboardKey::F1, GLFW_KEY_F1 },
		{ Ntsh::InputKeyboardKey::F2, GLFW_KEY_F2 },
		{ Ntsh::InputKeyboardKey::F3, GLFW_KEY_F3 },
		{ Ntsh::InputKeyboardKey::F4, GLFW_KEY_F4 },
		{ Ntsh::InputKeyboardKey::F5, GLFW_KEY_F5 },
		{ Ntsh::InputKeyboardKey::F6, GLFW_KEY_F6 },
		{ Ntsh::InputKeyboardKey::F7, GLFW_KEY_F7 },
		{ Ntsh::InputKeyboardKey::F8, GLFW_KEY_F8 },
		{ Ntsh::InputKeyboardKey::F9, GLFW_KEY_F9 },
		{ Ntsh::InputKeyboardKey::F10, GLFW_KEY_F10 },
		{ Ntsh::InputKeyboardKey::F11, GLFW_KEY_F11 },
		{ Ntsh::InputKeyboardKey::F12, GLFW_KEY_F12 }
	};
	std::unordered_map<int, Ntsh::InputState> m_keyStateMap = { { GLFW_KEY_A, Ntsh::InputState::None },
		{ GLFW_KEY_B, Ntsh::InputState::None },
		{ GLFW_KEY_C, Ntsh::InputState::None },
		{ GLFW_KEY_D, Ntsh::InputState::None },
		{ GLFW_KEY_E, Ntsh::InputState::None },
		{ GLFW_KEY_F, Ntsh::InputState::None },
		{ GLFW_KEY_G, Ntsh::InputState::None },
		{ GLFW_KEY_H, Ntsh::InputState::None },
		{ GLFW_KEY_I, Ntsh::InputState::None },
		{ GLFW_KEY_J, Ntsh::InputState::None },
		{ GLFW_KEY_K, Ntsh::InputState::None },
		{ GLFW_KEY_L, Ntsh::InputState::None },
		{ GLFW_KEY_M, Ntsh::InputState::None },
		{ GLFW_KEY_N, Ntsh::InputState::None },
		{ GLFW_KEY_O, Ntsh::InputState::None },
		{ GLFW_KEY_P, Ntsh::InputState::None },
		{ GLFW_KEY_Q, Ntsh::InputState::None },
		{ GLFW_KEY_R, Ntsh::InputState::None },
		{ GLFW_KEY_S, Ntsh::InputState::None },
		{ GLFW_KEY_T, Ntsh::InputState::None },
		{ GLFW_KEY_U, Ntsh::InputState::None },
		{ GLFW_KEY_V, Ntsh::InputState::None },
		{ GLFW_KEY_W, Ntsh::InputState::None },
		{ GLFW_KEY_X, Ntsh::InputState::None },
		{ GLFW_KEY_Y, Ntsh::InputState::None },
		{ GLFW_KEY_Z, Ntsh::InputState::None },
		{ GLFW_KEY_SPACE, Ntsh::InputState::None },
		{ GLFW_KEY_LEFT_SHIFT, Ntsh::InputState::None },
		{ GLFW_KEY_LEFT_CONTROL, Ntsh::InputState::None },
		{ GLFW_KEY_RIGHT_CONTROL, Ntsh::InputState::None },
		{ GLFW_KEY_LEFT_ALT, Ntsh::InputState::None },
		{ GLFW_KEY_ESCAPE, Ntsh::InputState::None },
		{ GLFW_KEY_TAB, Ntsh::InputState::None },
		{ GLFW_KEY_BACKSPACE, Ntsh::InputState::None },
		{ GLFW_KEY_ENTER, Ntsh::InputState::None },
		{ GLFW_KEY_KP_0, Ntsh::InputState::None },
		{ GLFW_KEY_KP_1, Ntsh::InputState::None },
		{ GLFW_KEY_KP_2, Ntsh::InputState::None },
		{ GLFW_KEY_KP_3, Ntsh::InputState::None },
		{ GLFW_KEY_KP_4, Ntsh::InputState::None },
		{ GLFW_KEY_KP_5, Ntsh::InputState::None },
		{ GLFW_KEY_KP_6, Ntsh::InputState::None },
		{ GLFW_KEY_KP_7, Ntsh::InputState::None },
		{ GLFW_KEY_KP_8, Ntsh::InputState::None },
		{ GLFW_KEY_KP_9, Ntsh::InputState::None },
		{ GLFW_KEY_LEFT, Ntsh::InputState::None },
		{ GLFW_KEY_RIGHT, Ntsh::InputState::None },
		{ GLFW_KEY_UP, Ntsh::InputState::None },
		{ GLFW_KEY_DOWN, Ntsh::InputState::None },
		{ GLFW_KEY_F1, Ntsh::InputState::None },
		{ GLFW_KEY_F2, Ntsh::InputState::None },
		{ GLFW_KEY_F3, Ntsh::InputState::None },
		{ GLFW_KEY_F4, Ntsh::InputState::None },
		{ GLFW_KEY_F5, Ntsh::InputState::None },
		{ GLFW_KEY_F6, Ntsh::InputState::None },
		{ GLFW_KEY_F7, Ntsh::InputState::None },
		{ GLFW_KEY_F8, Ntsh::InputState::None },
		{ GLFW_KEY_F9, Ntsh::InputState::None },
		{ GLFW_KEY_F10, Ntsh::InputState::None },
		{ GLFW_KEY_F11, Ntsh::InputState::None },
		{ GLFW_KEY_F12, Ntsh::InputState::None }
	};

	std::unordered_map<Ntsh::InputMouseButton, int> m_mouseButtonMap = { { Ntsh::InputMouseButton::One, GLFW_MOUSE_BUTTON_1 },
		{ Ntsh::InputMouseButton::Two, GLFW_MOUSE_BUTTON_2 },
		{ Ntsh::InputMouseButton::Three, GLFW_MOUSE_BUTTON_3 },
		{ Ntsh::InputMouseButton::Four, GLFW_MOUSE_BUTTON_4 },
		{ Ntsh::InputMouseButton::Five, GLFW_MOUSE_BUTTON_5 },
		{ Ntsh::InputMouseButton::Six, GLFW_MOUSE_BUTTON_6 },
		{ Ntsh::InputMouseButton::Seven, GLFW_MOUSE_BUTTON_7 },
		{ Ntsh::InputMouseButton::Eight, GLFW_MOUSE_BUTTON_8 },
	};
	std::unordered_map<int, Ntsh::InputState> m_mouseButtonStateMap = { { GLFW_MOUSE_BUTTON_1, Ntsh::InputState::None },
		{ GLFW_MOUSE_BUTTON_2, Ntsh::InputState::None },
		{ GLFW_MOUSE_BUTTON_3, Ntsh::InputState::None },
		{ GLFW_MOUSE_BUTTON_4, Ntsh::InputState::None },
		{ GLFW_MOUSE_BUTTON_5, Ntsh::InputState::None },
		{ GLFW_MOUSE_BUTTON_6, Ntsh::InputState::None },
		{ GLFW_MOUSE_BUTTON_7, Ntsh::InputState::None },
		{ GLFW_MOUSE_BUTTON_8, Ntsh::InputState::None },
	};
};