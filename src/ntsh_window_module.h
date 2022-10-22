#pragma once
#include "../external/Common/module_interfaces/ntsh_window_module_interface.h"
#include "../external/glfw/include/GLFW/glfw3.h"

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

#ifdef NTSH_OS_WINDOWS
	// Returns the native Win32 window handle
	HWND getNativeHandle();
#elif NTSH_OS_LINUX
	// Returns the native X window handle
	Window getNativeHandle();
#endif

public:
	// Internal function
	void resizeInternal(int newWidth, int newHeight);

private:
	// Resize callback
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
		auto ptr = reinterpret_cast<NutshellWindowModule*>(glfwGetWindowUserPointer(window));
		ptr->resizeInternal(width, height);
	}

private:
	GLFWwindow* m_window = nullptr;
	int m_width = 1280;
	int m_height = 720;
	int m_x = 0;
	int m_y = 0;
};