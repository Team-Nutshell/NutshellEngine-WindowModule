#pragma once
#include "../external/Common/module_interfaces/ntsh_window_module_interface.h"

class NutshellWindowModule : public NutshellWindowModuleInterface {
public:
	NutshellWindowModule() : NutshellWindowModuleInterface("Nutshell Window Test Module") {}

	void init();
	void update(double dt);
	void destroy();

	// Send a request to close the window
	void closeWindow();
	// Returns true if there has been a request to close the window, else if there has been no request to close the window
	bool shouldClose();

	// Changes the size of the window to width and height
	void setWindowSize(int width, int height);
	// Returns the width of the window
	int getWindowWidth();
	// Returns the height of the window
	int getWindowHeight();

	// Returns true if the window is in fullscreen mode, else, return false
	bool isFullscreen();
	// If the fullscreen parameter is true, puts the window in fullscreen, else, puts the window in windowed
	void setFullscreen(bool fullscreen);

	// Sets the title of the window
	void setTitle(const std::string& title);

#ifdef NTSH_OS_WINDOWS
	// Returns the native Win32 window handle
	HWND getWindowHandle();
#elif NTSH_OS_LINUX
	// Returns the native X window handle
	Window getWindowHandle();
#endif
};