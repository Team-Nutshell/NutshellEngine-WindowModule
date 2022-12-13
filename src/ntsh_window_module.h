#pragma once
#include "../external/Common/module_interfaces/ntsh_window_module_interface.h"
#include "../external/glfw/include/GLFW/glfw3.h"
#include <unordered_map>

class NutshellWindowModule : public NutshellWindowModuleInterface {
public:
	NutshellWindowModule() : NutshellWindowModuleInterface("Nutshell Window GLFW Module") {}

	void init();
	void update(double dt);
	void destroy();

	// Sends a request to close the window
	void close();
	// Returns true if there has been a request to close the window, else, returns false
	bool shouldClose();

	// Changes the size of the window to width and height
	void setSize(int width, int height);
	// Returns the width of the window
	int getWidth();
	// Returns the height of the window
	int getHeight();

	// Returns true if the window is in fullscreen mode, else, returns false
	bool isFullscreen();
	// If the fullscreen parameter is true, puts the window in fullscreen, else, puts the window in windowed
	void setFullscreen(bool fullscreen);

	// Polls events
	void pollEvents();

	// Sets the title of the window
	void setTitle(const std::string& title);

	// Gets the state of the keyboard key. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
	NtshInputState getKeyState(NtshInputKeyboardKey key);
	// Gets the state of the mouse button. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
	NtshInputState getButtonState(NtshInputMouseButton button) ;

	// Sets the mouse position
	void setMousePosition(int x, int y);
	// Gets the mouse horizontal position
	int getMouseXPosition();
	// Gets the mouse vertical position
	int getMouseYPosition();

#ifdef NTSH_OS_WINDOWS
	// Returns the native Win32 window handle
	HWND getNativeHandle();
#elif NTSH_OS_LINUX
	// Returns the native X window handle
	Window getNativeHandle();
#endif

public:
	// Window resize internal function used by callback
	void resizeInternal(int newWidth, int newHeight);

	// Keyboard key input internal function used by callback
	void keyboardKeyInternal(int key, int action);

	// Mouse button input internal function used by callback
	void mouseButtonInternal(int button, int action);

	// Mouse position internal function used by callback
	void mousePositionInternal(int x, int y);

	// Returns the next input state (Pressed -> Held, Released -> None)
	NtshInputState nextInputState(NtshInputState inputState);

private:
	// Resize callback
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
		auto ptr = reinterpret_cast<NutshellWindowModule*>(glfwGetWindowUserPointer(window));
		ptr->resizeInternal(width, height);
	}

	// Keyboard key callback
	static void keyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		NTSH_UNUSED(scancode);
		NTSH_UNUSED(mods);
		auto ptr = reinterpret_cast<NutshellWindowModule*>(glfwGetWindowUserPointer(window));
		ptr->keyboardKeyInternal(key, action);
	}

	// Mouse button callback
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		NTSH_UNUSED(mods);
		auto ptr = reinterpret_cast<NutshellWindowModule*>(glfwGetWindowUserPointer(window));
		ptr->mouseButtonInternal(button, action);
	}

	// Mouse position callback
	static void mousePositionCallback(GLFWwindow* window, double x, double y) {
		auto ptr = reinterpret_cast<NutshellWindowModule*>(glfwGetWindowUserPointer(window));
		ptr->mousePositionInternal(static_cast<int>(x), static_cast<int>(y));
	}

private:
	GLFWwindow* m_window = nullptr;
	int m_width = 1280;
	int m_height = 720;
	int m_x = 0;
	int m_y = 0;
	int m_mouseX = 0;
	int m_mouseY = 0;

	std::unordered_map<NtshInputKeyboardKey, int> m_keyMap = { { NtshInputKeyboardKey::A, GLFW_KEY_A },
		{ NtshInputKeyboardKey::B, GLFW_KEY_B },
		{ NtshInputKeyboardKey::C, GLFW_KEY_C },
		{ NtshInputKeyboardKey::D, GLFW_KEY_D },
		{ NtshInputKeyboardKey::E, GLFW_KEY_E },
		{ NtshInputKeyboardKey::F, GLFW_KEY_F },
		{ NtshInputKeyboardKey::G, GLFW_KEY_G },
		{ NtshInputKeyboardKey::H, GLFW_KEY_H },
		{ NtshInputKeyboardKey::I, GLFW_KEY_I },
		{ NtshInputKeyboardKey::J, GLFW_KEY_J },
		{ NtshInputKeyboardKey::K, GLFW_KEY_K },
		{ NtshInputKeyboardKey::L, GLFW_KEY_L },
		{ NtshInputKeyboardKey::M, GLFW_KEY_M },
		{ NtshInputKeyboardKey::N, GLFW_KEY_N },
		{ NtshInputKeyboardKey::O, GLFW_KEY_O },
		{ NtshInputKeyboardKey::P, GLFW_KEY_P },
		{ NtshInputKeyboardKey::Q, GLFW_KEY_Q },
		{ NtshInputKeyboardKey::R, GLFW_KEY_R },
		{ NtshInputKeyboardKey::S, GLFW_KEY_S },
		{ NtshInputKeyboardKey::T, GLFW_KEY_T },
		{ NtshInputKeyboardKey::U, GLFW_KEY_U },
		{ NtshInputKeyboardKey::V, GLFW_KEY_V },
		{ NtshInputKeyboardKey::W, GLFW_KEY_W },
		{ NtshInputKeyboardKey::X, GLFW_KEY_X },
		{ NtshInputKeyboardKey::Y, GLFW_KEY_Y },
		{ NtshInputKeyboardKey::Z, GLFW_KEY_Z },
		{ NtshInputKeyboardKey::Space, GLFW_KEY_SPACE },
		{ NtshInputKeyboardKey::Shift, GLFW_KEY_LEFT_SHIFT },
		{ NtshInputKeyboardKey::LeftCtrl, GLFW_KEY_LEFT_CONTROL },
		{ NtshInputKeyboardKey::RightCtrl, GLFW_KEY_RIGHT_CONTROL },
		{ NtshInputKeyboardKey::Alt, GLFW_KEY_LEFT_ALT },
		{ NtshInputKeyboardKey::Escape, GLFW_KEY_ESCAPE },
		{ NtshInputKeyboardKey::Tab, GLFW_KEY_TAB },
		{ NtshInputKeyboardKey::Backspace, GLFW_KEY_BACKSPACE },
		{ NtshInputKeyboardKey::Return, GLFW_KEY_ENTER },
		{ NtshInputKeyboardKey::Enter, GLFW_KEY_ENTER },
		{ NtshInputKeyboardKey::Num0, GLFW_KEY_KP_0 },
		{ NtshInputKeyboardKey::Num1, GLFW_KEY_KP_1 },
		{ NtshInputKeyboardKey::Num2, GLFW_KEY_KP_2 },
		{ NtshInputKeyboardKey::Num3, GLFW_KEY_KP_3 },
		{ NtshInputKeyboardKey::Num4, GLFW_KEY_KP_4 },
		{ NtshInputKeyboardKey::Num5, GLFW_KEY_KP_5 },
		{ NtshInputKeyboardKey::Num6, GLFW_KEY_KP_6 },
		{ NtshInputKeyboardKey::Num7, GLFW_KEY_KP_7 },
		{ NtshInputKeyboardKey::Num8, GLFW_KEY_KP_8 },
		{ NtshInputKeyboardKey::Num9, GLFW_KEY_KP_9 },
		{ NtshInputKeyboardKey::Left, GLFW_KEY_LEFT },
		{ NtshInputKeyboardKey::Right, GLFW_KEY_RIGHT },
		{ NtshInputKeyboardKey::Up, GLFW_KEY_UP },
		{ NtshInputKeyboardKey::Down, GLFW_KEY_DOWN },
		{ NtshInputKeyboardKey::F1, GLFW_KEY_F1 },
		{ NtshInputKeyboardKey::F2, GLFW_KEY_F2 },
		{ NtshInputKeyboardKey::F3, GLFW_KEY_F3 },
		{ NtshInputKeyboardKey::F4, GLFW_KEY_F4 },
		{ NtshInputKeyboardKey::F5, GLFW_KEY_F5 },
		{ NtshInputKeyboardKey::F6, GLFW_KEY_F6 },
		{ NtshInputKeyboardKey::F7, GLFW_KEY_F7 },
		{ NtshInputKeyboardKey::F8, GLFW_KEY_F8 },
		{ NtshInputKeyboardKey::F9, GLFW_KEY_F9 },
		{ NtshInputKeyboardKey::F10, GLFW_KEY_F10 },
		{ NtshInputKeyboardKey::F11, GLFW_KEY_F11 },
		{ NtshInputKeyboardKey::F12, GLFW_KEY_F12 }
	};
	std::unordered_map<int, NtshInputState> m_keyStateMap = { { GLFW_KEY_A, NtshInputState::None },
		{ GLFW_KEY_B, NtshInputState::None },
		{ GLFW_KEY_C, NtshInputState::None },
		{ GLFW_KEY_D, NtshInputState::None },
		{ GLFW_KEY_E, NtshInputState::None },
		{ GLFW_KEY_F, NtshInputState::None },
		{ GLFW_KEY_G, NtshInputState::None },
		{ GLFW_KEY_H, NtshInputState::None },
		{ GLFW_KEY_I, NtshInputState::None },
		{ GLFW_KEY_J, NtshInputState::None },
		{ GLFW_KEY_K, NtshInputState::None },
		{ GLFW_KEY_L, NtshInputState::None },
		{ GLFW_KEY_M, NtshInputState::None },
		{ GLFW_KEY_N, NtshInputState::None },
		{ GLFW_KEY_O, NtshInputState::None },
		{ GLFW_KEY_P, NtshInputState::None },
		{ GLFW_KEY_Q, NtshInputState::None },
		{ GLFW_KEY_R, NtshInputState::None },
		{ GLFW_KEY_S, NtshInputState::None },
		{ GLFW_KEY_T, NtshInputState::None },
		{ GLFW_KEY_U, NtshInputState::None },
		{ GLFW_KEY_V, NtshInputState::None },
		{ GLFW_KEY_W, NtshInputState::None },
		{ GLFW_KEY_X, NtshInputState::None },
		{ GLFW_KEY_Y, NtshInputState::None },
		{ GLFW_KEY_Z, NtshInputState::None },
		{ GLFW_KEY_SPACE, NtshInputState::None },
		{ GLFW_KEY_LEFT_SHIFT, NtshInputState::None },
		{ GLFW_KEY_LEFT_CONTROL, NtshInputState::None },
		{ GLFW_KEY_RIGHT_CONTROL, NtshInputState::None },
		{ GLFW_KEY_LEFT_ALT, NtshInputState::None },
		{ GLFW_KEY_ESCAPE, NtshInputState::None },
		{ GLFW_KEY_TAB, NtshInputState::None },
		{ GLFW_KEY_BACKSPACE, NtshInputState::None },
		{ GLFW_KEY_ENTER, NtshInputState::None },
		{ GLFW_KEY_KP_0, NtshInputState::None },
		{ GLFW_KEY_KP_1, NtshInputState::None },
		{ GLFW_KEY_KP_2, NtshInputState::None },
		{ GLFW_KEY_KP_3, NtshInputState::None },
		{ GLFW_KEY_KP_4, NtshInputState::None },
		{ GLFW_KEY_KP_5, NtshInputState::None },
		{ GLFW_KEY_KP_6, NtshInputState::None },
		{ GLFW_KEY_KP_7, NtshInputState::None },
		{ GLFW_KEY_KP_8, NtshInputState::None },
		{ GLFW_KEY_KP_9, NtshInputState::None },
		{ GLFW_KEY_LEFT, NtshInputState::None },
		{ GLFW_KEY_RIGHT, NtshInputState::None },
		{ GLFW_KEY_UP, NtshInputState::None },
		{ GLFW_KEY_DOWN, NtshInputState::None },
		{ GLFW_KEY_F1, NtshInputState::None },
		{ GLFW_KEY_F2, NtshInputState::None },
		{ GLFW_KEY_F3, NtshInputState::None },
		{ GLFW_KEY_F4, NtshInputState::None },
		{ GLFW_KEY_F5, NtshInputState::None },
		{ GLFW_KEY_F6, NtshInputState::None },
		{ GLFW_KEY_F7, NtshInputState::None },
		{ GLFW_KEY_F8, NtshInputState::None },
		{ GLFW_KEY_F9, NtshInputState::None },
		{ GLFW_KEY_F10, NtshInputState::None },
		{ GLFW_KEY_F11, NtshInputState::None },
		{ GLFW_KEY_F12, NtshInputState::None }
	};

	std::unordered_map<NtshInputMouseButton, int> m_mouseButtonMap = { { NtshInputMouseButton::One, GLFW_MOUSE_BUTTON_1 },
		{ NtshInputMouseButton::Two, GLFW_MOUSE_BUTTON_2 },
		{ NtshInputMouseButton::Three, GLFW_MOUSE_BUTTON_3 },
		{ NtshInputMouseButton::Four, GLFW_MOUSE_BUTTON_4 },
		{ NtshInputMouseButton::Five, GLFW_MOUSE_BUTTON_5 },
		{ NtshInputMouseButton::Six, GLFW_MOUSE_BUTTON_6 },
		{ NtshInputMouseButton::Seven, GLFW_MOUSE_BUTTON_7 },
		{ NtshInputMouseButton::Eight, GLFW_MOUSE_BUTTON_8 },
	};
	std::unordered_map<int, NtshInputState> m_mouseButtonStateMap = { { GLFW_MOUSE_BUTTON_1, NtshInputState::None },
		{ GLFW_MOUSE_BUTTON_2, NtshInputState::None },
		{ GLFW_MOUSE_BUTTON_3, NtshInputState::None },
		{ GLFW_MOUSE_BUTTON_4, NtshInputState::None },
		{ GLFW_MOUSE_BUTTON_5, NtshInputState::None },
		{ GLFW_MOUSE_BUTTON_6, NtshInputState::None },
		{ GLFW_MOUSE_BUTTON_7, NtshInputState::None },
		{ GLFW_MOUSE_BUTTON_8, NtshInputState::None },
	};
};