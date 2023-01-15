#pragma once
#include "../external/Common/module_interfaces/ntshengn_window_module_interface.h"

namespace NtshEngn {

	class WindowModule : public WindowModuleInterface {
	public:
		WindowModule() : WindowModuleInterface("NutshellEngine Window Test Module") {}

		void init();
		void update(double dt);
		void destroy();

		// Opens a new window and returns a unique identifier
		NtshEngn::WindowId open(int width, int height, const std::string& title);
		// Returns true if the window with identifier windowId is open, else, returns false
		bool isOpen(NtshEngn::WindowId windowId);
		// Flags the window to be closed at the next update
		void close(NtshEngn::WindowId windowId);

		// Returns the number of opened windows
		uint64_t windowCount();

		// Changes the size of the window with identifier windowId to width and height
		void setSize(NtshEngn::WindowId windowId, int width, int height);
		// Returns the width of the window with identifier windowId
		int getWidth(NtshEngn::WindowId windowId);
		// Returns the height of the window with identifier windowId
		int getHeight(NtshEngn::WindowId windowId);

		// Changes the position of the window with identifier windowId to x and y
		void setPosition(NtshEngn::WindowId windowId, int x, int y);
		// Returns the horizontal position of the window with identifier windowId
		int getPositionX(NtshEngn::WindowId windowId);
		// Returns the vertical position of the window with identifier windowId
		int getPositionY(NtshEngn::WindowId windowId);

		// If the fullscreen parameter is true, puts the window with identifier windowId in fullscreen, else, puts the window with identifier windowId in windowed
		void setFullscreen(NtshEngn::WindowId windowId, bool fullscreen);
		// Returns true if the window with identifier windowId is in fullscreen mode, else, returns false
		bool isFullscreen(NtshEngn::WindowId windowId);

		// Polls events of the windows
		void pollEvents();

		// Sets the title of the window with identifier windowId
		void setTitle(NtshEngn::WindowId windowId, const std::string& title);

		// Gets the state of the keyboard key. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
		NtshEngn::InputState getKeyState(NtshEngn::WindowId windowId, NtshEngn::InputKeyboardKey key);
		// Gets the state of the mouse button. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
		NtshEngn::InputState getMouseButtonState(NtshEngn::WindowId windowId, NtshEngn::InputMouseButton mouseButton);

		// Sets the mouse cursor position
		void setCursorPosition(NtshEngn::WindowId windowId, int x, int y);
		// Gets the mouse cursor horizontal position
		int getCursorPositionX(NtshEngn::WindowId windowId);
		// Gets the mouse cursor vertical position
		int getCursorPositionY(NtshEngn::WindowId windowId);

		// If the mouse cursor is visible in the window with identifier windowId, hides it, else, shows it
		void setCursorVisibility(NtshEngn::WindowId windowId, bool visible);
		// Returns true if the mouse cursor is visible in the window with identifier windowId, else, returns false
		bool isCursorVisible(NtshEngn::WindowId windowId);

#if defined(NTSHENGN_OS_WINDOWS)
		// Returns the native Win32 window handle of the window with identifier windowId
		HWND getNativeHandle(NtshEngn::WindowId windowId);
#elif defined(NTSHENGN_OS_LINUX)
		// Returns the native X window handle of the window with identifier windowId
		Window getNativeHandle(NtshEngn::WindowId windowId);
#endif
	};

}