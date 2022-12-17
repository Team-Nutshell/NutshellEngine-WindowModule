#include "ntsh_window_module.h"
#include "../external/Module/utils/ntsh_module_defines.h"
#include "../external/Module/utils/ntsh_dynamic_library.h"
#include "../external/Common/utils/ntsh_engine_defines.h"
#include "../external/Common/utils/ntsh_engine_enums.h"

void NutshellWindowModule::init() {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void NutshellWindowModule::update(double dt) {
	NTSH_UNUSED(dt);

	for (size_t i = 0; i < m_windows.size(); i++) {
		if (m_windows[i]->shouldClose()) {
			i = m_windows.erase(i);
		}
		else {
			m_windows[i]->updateInputs(dt);
		}
	}

	pollEvents();
}

void NutshellWindowModule::destroy() {
	for (size_t i = 0; i < m_windows.size(); i++) {
		m_windows[i]->close();
	}
	glfwTerminate();
}

NtshWindowId NutshellWindowModule::open(int width, int height, const std::string& title) {
	m_windows[m_id] = std::make_unique<GLFWWindow>(width, height, title);

	return m_id++;
}

bool NutshellWindowModule::isOpen(NtshWindowId windowId) {
	return (m_windows.find(windowId) != m_windows.end()) ? !m_windows[windowId]->shouldClose() : false;
}

void NutshellWindowModule::close(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->close();
}

uint64_t NutshellWindowModule::windowCount() {
	uint64_t count = 0;
	for (size_t i = 0; i < m_windows.size(); i++) {
		if (!m_windows[i]->shouldClose()) {
			count++;
		}
	}

	return count;
}

void NutshellWindowModule::setSize(NtshWindowId windowId, int width, int height) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setSize(width, height);
}

int NutshellWindowModule::getWidth(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getWidth();
}

int NutshellWindowModule::getHeight(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getHeight();
}

void NutshellWindowModule::setPosition(NtshWindowId windowId, int x, int y) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setPosition(x, y);
}

int NutshellWindowModule::getPositionX(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getPositionX();
}

int NutshellWindowModule::getPositionY(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getPositionY();
}

void NutshellWindowModule::setFullscreen(NtshWindowId windowId, bool fullscreen) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setFullscreen(fullscreen);
}

bool NutshellWindowModule::isFullscreen(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isFullscreen();
}

void NutshellWindowModule::pollEvents() {
	glfwPollEvents();
}

void NutshellWindowModule::setTitle(NtshWindowId windowId, const std::string& title) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setTitle(title);
}

NtshInputState NutshellWindowModule::getKeyState(NtshWindowId windowId, NtshInputKeyboardKey key) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getKeyState(key);
}

NtshInputState NutshellWindowModule::getMouseButtonState(NtshWindowId windowId, NtshInputMouseButton mouseButton) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getMouseButtonState(mouseButton);
}

void NutshellWindowModule::setCursorPosition(NtshWindowId windowId, int x, int y) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setCursorPosition(x, y);
}

int NutshellWindowModule::getCursorPositionX(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getCursorPositionX();
}

int NutshellWindowModule::getCursorPositionY(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getCursorPositionY();
}

void NutshellWindowModule::setCursorVisibility(NtshWindowId windowId, bool visible) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setCursorVisibility(visible);
}

bool NutshellWindowModule::isCursorVisible(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isCursorVisible();
}

#if defined(NTSH_OS_WINDOWS)
HWND NutshellWindowModule::getNativeHandle(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getNativeHandle();
}
#elif defined(NTSH_OS_LINUX)
Window NutshellWindowModule::getNativeHandle(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getNativeHandle();
}
#endif

extern "C" NTSH_MODULE_API NutshellWindowModuleInterface* createModule() {
	return new NutshellWindowModule;
}

extern "C" NTSH_MODULE_API void destroyModule(NutshellWindowModuleInterface* m) {
	delete m;
}