#pragma once
#include "../external/Common/module_interfaces/ntsh_window_module_interface.h"

class NutshellWindowModule : public NutshellWindowModuleInterface {
public:
	NutshellWindowModule() : NutshellWindowModuleInterface("Nutshell Window Test Module") {}

	void init();
	void update(double dt);
	void destroy();

	// Opens a new window and returns a unique identifier
	NtshWindowId open();
	// Returns true if the window with identifier windowId is open, else, returns false
	bool isOpen(NtshWindowId windowId);
	// Closes the window with identifier windowId
	void close(NtshWindowId windowId);

	// Returns the number of opened windows
	uint64_t windowCount();

	// Changes the size of the window with identifier windowId to width and height
	void setSize(NtshWindowId windowId, int width, int height);
	// Returns the width of the window with identifier windowId
	int getWidth(NtshWindowId windowId);
	// Returns the height of the window with identifier windowId
	int getHeight(NtshWindowId windowId);

	// Changes the position of the window with identifier windowId to x and y
	void setPosition(NtshWindowId windowId, int x, int y);
	// Returns the horizontal position of the window with identifier windowId
	int getPositionX(NtshWindowId windowId);
	// Returns the vertical position of the window with identifier windowId
	int getPositionY(NtshWindowId windowId);

	// If the fullscreen parameter is true, puts the window with identifier windowId in fullscreen, else, puts the window with identifier windowId in windowed
	void setFullscreen(NtshWindowId windowId, bool fullscreen);
	// Returns true if the window with identifier windowId is in fullscreen mode, else, returns false
	bool isFullscreen(NtshWindowId windowId);

	// Polls events of the windows
	void pollEvents();

	// Sets the title of the window with identifier windowId
	void setTitle(NtshWindowId windowId, const std::string& title);

	// Gets the state of the keyboard key. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
	NtshInputState getKeyState(NtshWindowId windowId, NtshInputKeyboardKey key);
	// Gets the state of the mouse button. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
	NtshInputState getMouseButtonState(NtshWindowId windowId, NtshInputMouseButton mouseButton);

	// Sets the mouse cursor position
	void setCursorPosition(NtshWindowId windowId, int x, int y);
	// Gets the mouse cursor horizontal position
	int getCursorPositionX(NtshWindowId windowId);
	// Gets the mouse cursor vertical position
	int getCursorPositionY(NtshWindowId windowId);

	// If the mouse cursor is visible in the window with identifier windowId, hides it, else, shows it
	void setCursorVisibility(NtshWindowId windowId, bool visible);
	// Returns true if the mouse cursor is visible in the window with identifier windowId, else, returns false
	bool isCursorVisible(NtshWindowId windowId);

#if defined(NTSH_OS_WINDOWS)
	// Returns the native Win32 window handle of the window with identifier windowId
	HWND getNativeHandle(NtshWindowId windowId);
#elif defined(NTSH_OS_LINUX)
	// Returns the native X window handle of the window with identifier windowId
	Window getNativeHandle(NtshWindowId windowId);
#endif
};