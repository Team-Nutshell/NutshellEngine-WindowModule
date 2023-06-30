#pragma once
#include "../external/Common/module_interfaces/ntshengn_window_module_interface.h"
#include "../external/glfw/include/GLFW/glfw3.h"
#include "glfwwindow.h"
#include <unordered_map>
#include <memory>

namespace NtshEngn {

	class WindowModule : public WindowModuleInterface {
	public:
		WindowModule() : WindowModuleInterface("NutshellEngine GLFW Window Module") {}

		void init();
		void update(double dt);
		void destroy();

		// Opens a new window and returns a unique identifier
		WindowID open(int width, int height, const std::string& title);
		// Returns true if the window with identifier windowId is open, else, returns false
		bool isOpen(WindowID windowId);
		// Flags the window to be closed at the next update
		void close(WindowID windowId);

		// Returns the main window identifier
		WindowID getMainWindowID();
		// Returns the number of opened windows
		uint64_t windowCount();

		// Changes the size of the window with identifier windowId to width and height
		void setSize(WindowID windowId, int width, int height);
		// Returns the width of the window with identifier windowId
		int getWidth(WindowID windowId);
		// Returns the height of the window with identifier windowId
		int getHeight(WindowID windowId);

		// Changes the position of the window with identifier windowId to x and y
		void setPosition(WindowID windowId, int x, int y);
		// Returns the horizontal position of the window with identifier windowId
		int getPositionX(WindowID windowId);
		// Returns the vertical position of the window with identifier windowId
		int getPositionY(WindowID windowId);

		// If the fullscreen parameter is true, puts the window with identifier windowId in fullscreen, else, puts the window with identifier windowId in windowed
		void setFullscreen(WindowID windowId, bool fullscreen);
		// Returns true if the window with identifier windowId is in fullscreen mode, else, returns false
		bool isFullscreen(WindowID windowId);

		// If the borderless parameter is true, puts the window with identifier windowId in borderless, else, adds borders to the window with identifier windowId
		void setBorderless(WindowID windowId, bool borderless);
		// Returns true if the window with identifier windowId is in borderless mode, else, returns false
		bool isBorderless(WindowID windowId);

		// If the resizable parameter is true, makes the window with identifier windowId resizable, else, makes the window with identifier windowId not resizable
		void setResizable(WindowID windowId, bool resizable);
		// Returns true if the window with identifier windowId is resizable, else, returns false
		bool isResizable(WindowID windowId);

		// Polls events of the window with identifier windowId
		void pollEvents();

		// Sets the title of the window with identifier windowId
		void setTitle(WindowID windowId, const std::string& title);

		// Gets the state of the keyboard key. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
		InputState getKeyState(WindowID windowId, InputKeyboardKey key);
		// Gets the state of the mouse button. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
		InputState getMouseButtonState(WindowID windowId, InputMouseButton mouseButton);

		// Sets the mouse cursor position
		void setCursorPosition(WindowID windowId, int x, int y);
		// Gets the mouse cursor horizontal position
		int getCursorPositionX(WindowID windowId);
		// Gets the mouse cursor vertical position
		int getCursorPositionY(WindowID windowId);

		// If the mouse cursor is visible in the window with identifier windowId, hides it, else, shows it
		void setCursorVisibility(WindowID windowId, bool visible);
		// Returns true if the mouse cursor is visible in the window with identifier windowId, else, returns false
		bool isCursorVisible(WindowID windowId);

		// Returns the native window handle of the window with identifier windowId
		NativeWindowHandle getNativeHandle(WindowID windowId);
		// Returns the native window additional information of the window with identifier windowId
		NativeWindowAdditionalInformation getNativeAdditionalInformation(WindowID windowId);

	private:
		std::unordered_map<WindowID, std::unique_ptr<GLFWWindow>> m_windows;

		WindowID m_mainWindow = std::numeric_limits<WindowID>::max();
		WindowID m_id = 0;
	};

}