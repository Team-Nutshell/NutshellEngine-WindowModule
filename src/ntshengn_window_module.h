#pragma once
#include "../Common/modules/ntshengn_window_module_interface.h"
#include "../external/glfw/include/GLFW/glfw3.h"
#include "glfwwindow.h"
#include "gamepad.h"
#include <unordered_map>
#include <memory>

namespace NtshEngn {

	class WindowModule : public WindowModuleInterface {
	public:
		WindowModule() : WindowModuleInterface("NutshellEngine GLFW Window Module") {}

		void init();
		void update(float dt);
		void destroy();

		// Opens a new window and returns a unique identifier
		WindowID openWindow(int width, int height, const std::string& title);
		// Returns true if the window with identifier windowID is open, else, returns false
		bool isWindowOpen(WindowID windowID);
		// Flags the window to be closed at the next update
		void closeWindow(WindowID windowID);

		// Returns the main window identifier
		WindowID getMainWindowID();
		// Returns the number of opened windows
		uint64_t windowCount();

		// Changes the size of the window with identifier windowID to width and height
		void setWindowSize(WindowID windowID, int width, int height);
		// Returns the width of the window with identifier windowID
		int getWindowWidth(WindowID windowID);
		// Returns the height of the window with identifier windowID
		int getWindowHeight(WindowID windowID);

		// Changes the position of the window with identifier windowID to x and y
		void setWindowPosition(WindowID windowID, int x, int y);
		// Returns the horizontal position of the window with identifier windowID
		int getWindowPositionX(WindowID windowID);
		// Returns the vertical position of the window with identifier windowID
		int getWindowPositionY(WindowID windowID);

		// If the fullscreen parameter is true, puts the window with identifier windowID in fullscreen, else, puts the window with identifier windowID in windowed
		void setWindowFullscreen(WindowID windowID, bool fullscreen);
		// Returns true if the window with identifier windowID is in fullscreen mode, else, returns false
		bool isWindowFullscreen(WindowID windowID);

		// If the borderless parameter is true, puts the window with identifier windowID in borderless, else, adds borders to the window with identifier windowID
		void setWindowBorderless(WindowID windowID, bool borderless);
		// Returns true if the window with identifier windowID is in borderless mode, else, returns false
		bool isWindowBorderless(WindowID windowID);

		// If the resizable parameter is true, makes the window with identifier windowID resizable, else, makes the window with identifier windowID not resizable
		void setWindowResizable(WindowID windowID, bool resizable);
		// Returns true if the window with identifier windowID is resizable, else, returns false
		bool isWindowResizable(WindowID windowID);

		// Sets the opacity of the window with identifier windowID
		void setWindowOpacity(WindowID windowID, float opacity);
		// Returns the opacity of the window with identifier windowID
		float getWindowOpacity(WindowID windowID);

		// Returns the path to the files dropped on the window with identifier windowID
		std::vector<std::string> getWindowDroppedFiles(WindowID windowID);

		// Polls events of the window with identifier windowID
		void pollEvents();

		// Sets the title of the window with identifier windowID
		void setWindowTitle(WindowID windowID, const std::string& title);
		// Returns the title of the window with identifier windowID
		std::string getWindowTitle(WindowID windowID);
		// Sets the icon of the window with identifier windowID
		void setWindowIcon(WindowID windowID, const Image& image);

		// Returns the state of the keyboard key. None if the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
		InputState getKeyState(WindowID windowID, InputKeyboardKey key);
		// Returns the state of the mouse button. None if the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
		InputState getMouseButtonState(WindowID windowID, InputMouseButton mouseButton);

		// Sets the mouse cursor position
		void setCursorPosition(WindowID windowID, int x, int y);
		// Returns the mouse cursor horizontal position
		int getCursorPositionX(WindowID windowID);
		// Returns the mouse cursor vertical position
		int getCursorPositionY(WindowID windowID);

		// Returns the horizontal mouse scroll offset between the last and current frame
		float getMouseScrollOffsetX(WindowID windowID);
		// Returns the vertical mouse scroll offset between the last and current frame
		float getMouseScrollOffsetY(WindowID windowID);

		// Sets the mouse cursor's visibility in the window with identifier windowID
		void setCursorVisibility(WindowID windowID, bool visible);
		// Returns true if the mouse cursor is visible in the window with identifier windowID, else, returns false
		bool isCursorVisible(WindowID windowID);

		// Returns the list of connected gamepads
		std::vector<GamepadID> getConnectedGamepads();

		// Returns the state of the gamepad with identifier gamepadID
		InputState getGamepadButtonState(GamepadID gamepadID, InputGamepadButton button);
		// Returns the value of the stick's horizontal axis, with -1.0 being left, 0.0 neutral and 1.0 right
		float getGamepadStickAxisX(GamepadID gamepadID, InputGamepadStick stick);
		// Returns the value of the stick's vertical axis, with -1.0 being up, 0.0 neutral and 1.0 down
		float getGamepadStickAxisY(GamepadID gamepadID, InputGamepadStick stick);
		// Returns the value of the stick's left trigger, with 0.0 being neutral and 1.0 being fully pressed
		float getGamepadLeftTrigger(GamepadID gamepadID);
		// Returns the value of the stick's right trigger, with 0.0 being neutral and 1.0 being fully pressed
		float getGamepadRightTrigger(GamepadID gamepadID);

		// Returns the name of the gamepad with identifier gamepadID
		std::string getGamepadName(GamepadID gamepadID);

		// Returns the width of the main monitor
		int getMonitorWidth();
		// Returns the height of the main monitor
		int getMonitorHeight();
		// Returns the refresh rate of the main monitor
		int getMonitorRefreshRate();
		// Returns the display scaling ratio of the main monitor
		float getMonitorDisplayScaling();

		// Returns the native window handle of the window with identifier windowID
		NativeWindowHandle getWindowNativeHandle(WindowID windowID);
		// Returns the native window additional information of the window with identifier windowID
		NativeWindowAdditionalInformation getWindowNativeAdditionalInformation(WindowID windowID);

	private:
		std::unordered_map<WindowID, std::unique_ptr<GLFWWindow>> m_windows;

		WindowID m_mainWindow = NTSHENGN_WINDOW_UNKNOWN;
		WindowID m_windowID = 0;

		std::unordered_map<GamepadID, std::unique_ptr<Gamepad>> m_gamepads;
		std::unordered_map<int, GamepadID> m_gamepadIDs;
		GamepadID m_gamepadID;
	};

}