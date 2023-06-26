#pragma once
#include "../external/Common/module_interfaces/ntshengn_window_module_interface.h"
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
		WindowId open(int width, int height, const std::string& title);
		// Returns true if the window with identifier windowId is open, else, returns false
		bool isOpen(WindowId windowId);
		// Flags the window to be closed at the next update
		void close(WindowId windowId);

		// Returns the number of opened windows
		uint64_t windowCount();

		// Changes the size of the window with identifier windowId to width and height
		void setSize(WindowId windowId, int width, int height);
		// Returns the width of the window with identifier windowId
		int getWidth(WindowId windowId);
		// Returns the height of the window with identifier windowId
		int getHeight(WindowId windowId);

		// Changes the position of the window with identifier windowId to x and y
		void setPosition(WindowId windowId, int x, int y);
		// Returns the horizontal position of the window with identifier windowId
		int getPositionX(WindowId windowId);
		// Returns the vertical position of the window with identifier windowId
		int getPositionY(WindowId windowId);

		// If the fullscreen parameter is true, puts the window with identifier windowId in fullscreen, else, puts the window with identifier windowId in windowed
		void setFullscreen(WindowId windowId, bool fullscreen);
		// Returns true if the window with identifier windowId is in fullscreen mode, else, returns false
		bool isFullscreen(WindowId windowId);

		// If the borderless parameter is true, puts the window with identifier windowId in borderless, else, adds borders to the window with identifier windowId
		void setBorderless(WindowId windowId, bool borderless);
		// Returns true if the window with identifier windowId is in borderless mode, else, returns false
		bool isBorderless(WindowId windowId);

		// If the resizable parameter is true, makes the window with identifier windowId resizable, else, makes the window with identifier windowId not resizable
		void setResizable(WindowId windowId, bool resizable);
		// Returns true if the window with identifier windowId is resizable, else, returns false
		bool isResizable(WindowId windowId);

		// Polls events of the windows
		void pollEvents();

		// Sets the title of the window with identifier windowId
		void setTitle(WindowId windowId, const std::string& title);

		// Gets the state of the keyboard key. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
		InputState getKeyState(WindowId windowId, InputKeyboardKey key);
		// Gets the state of the mouse button. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
		InputState getMouseButtonState(WindowId windowId, InputMouseButton mouseButton);

		// Sets the mouse cursor position
		void setCursorPosition(WindowId windowId, int x, int y);
		// Gets the mouse cursor horizontal position
		int getCursorPositionX(WindowId windowId);
		// Gets the mouse cursor vertical position
		int getCursorPositionY(WindowId windowId);

		// If the mouse cursor is visible in the window with identifier windowId, hides it, else, shows it
		void setCursorVisibility(WindowId windowId, bool visible);
		// Returns true if the mouse cursor is visible in the window with identifier windowId, else, returns false
		bool isCursorVisible(WindowId windowId);

		// Returns the native window handle of the window with identifier windowId
		NativeWindowHandle getNativeHandle(WindowId windowId);
		// Returns the native window additional information of the window with identifier windowId
		NativeWindowAdditionalInformation getNativeAdditionalInformation(WindowId windowId);

	private:
		std::unique_ptr<QApplication> m_application;

		std::unordered_map<WindowId, std::unique_ptr<QtWindow>> m_windows;

		NtshEngn::WindowId m_id = 0;
	};

}