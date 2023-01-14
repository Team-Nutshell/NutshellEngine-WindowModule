#pragma once
#include "../external/Common/module_interfaces/ntsh_window_module_interface.h"

class NutshellWindowModule : public NutshellWindowModuleInterface {
public:
	NutshellWindowModule() : NutshellWindowModuleInterface("Nutshell Window Test Module") {}

	void init();
	void update(double dt);
	void destroy();

	// Opens a new window and returns a unique identifier
	Ntsh::WindowId open(int width, int height, const std::string& title);
	// Returns true if the window with identifier windowId is open, else, returns false
	bool isOpen(Ntsh::WindowId windowId);
	// Flags the window to be closed at the next update
	void close(Ntsh::WindowId windowId);

	// Returns the number of opened windows
	uint64_t windowCount();

	// Changes the size of the window with identifier windowId to width and height
	void setSize(Ntsh::WindowId windowId, int width, int height);
	// Returns the width of the window with identifier windowId
	int getWidth(Ntsh::WindowId windowId);
	// Returns the height of the window with identifier windowId
	int getHeight(Ntsh::WindowId windowId);

	// Changes the position of the window with identifier windowId to x and y
	void setPosition(Ntsh::WindowId windowId, int x, int y);
	// Returns the horizontal position of the window with identifier windowId
	int getPositionX(Ntsh::WindowId windowId);
	// Returns the vertical position of the window with identifier windowId
	int getPositionY(Ntsh::WindowId windowId);

	// If the fullscreen parameter is true, puts the window with identifier windowId in fullscreen, else, puts the window with identifier windowId in windowed
	void setFullscreen(Ntsh::WindowId windowId, bool fullscreen);
	// Returns true if the window with identifier windowId is in fullscreen mode, else, returns false
	bool isFullscreen(Ntsh::WindowId windowId);

	// Polls events of the windows
	void pollEvents();

	// Sets the title of the window with identifier windowId
	void setTitle(Ntsh::WindowId windowId, const std::string& title);

	// Gets the state of the keyboard key. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
	Ntsh::InputState getKeyState(Ntsh::WindowId windowId, Ntsh::InputKeyboardKey key);
	// Gets the state of the mouse button. None is the input is neutral, Pressed the first frame it is being pressed, Held from the second frame it is pressed, Released the frame it is being released
	Ntsh::InputState getMouseButtonState(Ntsh::WindowId windowId, Ntsh::InputMouseButton mouseButton);

	// Sets the mouse cursor position
	void setCursorPosition(Ntsh::WindowId windowId, int x, int y);
	// Gets the mouse cursor horizontal position
	int getCursorPositionX(Ntsh::WindowId windowId);
	// Gets the mouse cursor vertical position
	int getCursorPositionY(Ntsh::WindowId windowId);

	// If the mouse cursor is visible in the window with identifier windowId, hides it, else, shows it
	void setCursorVisibility(Ntsh::WindowId windowId, bool visible);
	// Returns true if the mouse cursor is visible in the window with identifier windowId, else, returns false
	bool isCursorVisible(Ntsh::WindowId windowId);

#if defined(NTSH_OS_WINDOWS)
	// Returns the native Win32 window handle of the window with identifier windowId
	HWND getNativeHandle(Ntsh::WindowId windowId);
#elif defined(NTSH_OS_LINUX)
	// Returns the native X window handle of the window with identifier windowId
	Window getNativeHandle(Ntsh::WindowId windowId);
#endif
};