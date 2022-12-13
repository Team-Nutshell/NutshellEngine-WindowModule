#pragma once
#include "../external/Common/module_interfaces/ntsh_window_module_interface.h"

class NutshellWindowModule : public NutshellWindowModuleInterface {
public:
	NutshellWindowModule() : NutshellWindowModuleInterface("Nutshell Window Test Module") {}

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
	NtshInputState getButtonState(NtshInputMouseButton button);

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
};