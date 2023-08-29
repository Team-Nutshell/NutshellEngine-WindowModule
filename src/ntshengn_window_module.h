#pragma once
#include "../Common/module_interfaces/ntshengn_window_module_interface.h"
#include "qtwindow.h"
#include <qapplication.h>
#include <memory>
#include <unordered_map>

namespace NtshEngn {

	class WindowModule : public WindowModuleInterface {
	public:
		WindowModule() : WindowModuleInterface("NutshellEngine Qt5 Window Module") {}

		void init();
		void update(double dt);
		void destroy();

		// Opens a new window and returns a unique identifier
		WindowID open(int width, int height, const std::string& title);
		// Returns true if the window with identifier windowID is open, else, returns false
		bool isOpen(WindowID windowID);
		// Flags the window to be closed at the next update
		void close(WindowID windowID);

		// Returns the main window identifier
		WindowID getMainWindowID();
		// Returns the number of opened windows
		uint64_t windowCount();

		// Changes the size of the window with identifier windowID to width and height
		void setSize(WindowID windowID, int width, int height);
		// Returns the width of the window with identifier windowID
		int getWidth(WindowID windowID);
		// Returns the height of the window with identifier windowID
		int getHeight(WindowID windowID);

		// Changes the position of the window with identifier windowID to x and y
		void setPosition(WindowID windowID, int x, int y);
		// Returns the horizontal position of the window with identifier windowID
		int getPositionX(WindowID windowID);
		// Returns the vertical position of the window with identifier windowID
		int getPositionY(WindowID windowID);

		// If the fullscreen parameter is true, puts the window with identifier windowID in fullscreen, else, puts the window with identifier windowID in windowed
		void setFullscreen(WindowID windowID, bool fullscreen);
		// Returns true if the window with identifier windowID is in fullscreen mode, else, returns false
		bool isFullscreen(WindowID windowID);

		// If the borderless parameter is true, puts the window with identifier windowID in borderless, else, adds borders to the window with identifier windowID
		void setBorderless(WindowID windowID, bool borderless);
		// Returns true if the window with identifier windowID is in borderless mode, else, returns false
		bool isBorderless(WindowID windowID);

		// If the resizable parameter is true, makes the window with identifier windowID resizable, else, makes the window with identifier windowID not resizable
		void setResizable(WindowID windowID, bool resizable);
		// Returns true if the window with identifier windowID is resizable, else, returns false
		bool isResizable(WindowID windowID);

		// Polls events of the windows
		void pollEvents();

		// Sets the title of the window with identifier windowID
		void setTitle(WindowID windowID, const std::string& title);
		// Sets the icon of the window with identifier windowID
		void setIcon(WindowID windowID, const Image& image);

		// Gets the state of the keyboard key. None if the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
		InputState getKeyState(WindowID windowID, InputKeyboardKey key);
		// Gets the state of the mouse button. None if the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
		InputState getMouseButtonState(WindowID windowID, InputMouseButton mouseButton);

		// Sets the mouse cursor position
		void setCursorPosition(WindowID windowID, int x, int y);
		// Gets the mouse cursor horizontal position
		int getCursorPositionX(WindowID windowID);
		// Gets the mouse cursor vertical position
		int getCursorPositionY(WindowID windowID);

		// Sets the mouse cursor's visibility in the window with identifier windowID
		void setCursorVisibility(WindowID windowID, bool visible);
		// Returns true if the mouse cursor is visible in the window with identifier windowID, else, returns false
		bool isCursorVisible(WindowID windowID);

		// Returns the horizontal mouse scroll offset between the last and current frame
		float getMouseScrollOffsetX(WindowID windowID);
		// Returns the vertical mouse scroll offset between the last and current frame
		float getMouseScrollOffsetY(WindowID windowID);

		// Returns the width of the main monitor
		int getMonitorWidth();
		// Returns the height of the main monitor
		int getMonitorHeight();
		// Returns the refresh rate of the main monitor
		int getMonitorRefreshRate();
		// Returns the display scaling ratio of the main monitor
		float getMonitorDisplayScaling();

		// Returns the native window handle of the window with identifier windowID
		NativeWindowHandle getNativeHandle(WindowID windowID);
		// Returns the native window additional information of the window with identifier windowID
		NativeWindowAdditionalInformation getNativeAdditionalInformation(WindowID windowID);

	private:
		std::unique_ptr<QApplication> m_application;

		std::unordered_map<WindowID, std::unique_ptr<QtWindow>> m_windows;

		WindowID m_mainWindow = std::numeric_limits<WindowID>::max();
		WindowID m_id = 0;
	};

}