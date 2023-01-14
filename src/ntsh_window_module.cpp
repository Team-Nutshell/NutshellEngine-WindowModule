#include "ntsh_window_module.h"
#include "../external/Module/utils/ntsh_module_defines.h"
#include "../external/Module/utils/ntsh_dynamic_library.h"
#include "../external/Common/utils/ntsh_engine_defines.h"
#include "../external/Common/utils/ntsh_engine_enums.h"
#include <thread>

void NutshellWindowModule::init() {
	int argc = 0;
	m_application = std::make_unique<QApplication>(argc, nullptr);
}

void NutshellWindowModule::update(double dt) {
	NTSH_UNUSED(dt);

	for (auto it = m_windows.begin(); it != m_windows.end(); ) {
		if (it->second->shouldClose()) {
			it = m_windows.erase(it);
		}
		else {
			it->second->updateInputs(dt);
			it++;
		}
	}

	m_application->processEvents();
}

void NutshellWindowModule::destroy() {
	for (auto it = m_windows.begin(); it != m_windows.end(); ) {
		it->second->close();
		it = m_windows.erase(it);
	}
}

Ntsh::WindowId NutshellWindowModule::open(int width, int height, const std::string& title) {
	m_windows[m_id] = std::make_unique<QtWindow>();
	m_windows[m_id]->open(width, height, title);

	return m_id++;
}

bool NutshellWindowModule::isOpen(Ntsh::WindowId windowId) {
	return (m_windows.find(windowId) != m_windows.end()) ? !m_windows[windowId]->shouldClose() : false;
}

void NutshellWindowModule::close(Ntsh::WindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->closeWindow();
}

uint64_t NutshellWindowModule::windowCount() {
	uint64_t count = 0;
	for (auto it = m_windows.begin(); it != m_windows.end(); it++) {
		if (!it->second->shouldClose()) {
			count++;
		}
	}

	return count;
}

void NutshellWindowModule::setSize(Ntsh::WindowId windowId, int width, int height) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->resize(width, height);
}

int NutshellWindowModule::getWidth(Ntsh::WindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	if (m_windows[windowId]->isMinimized()) {
		return 0;
	}
	return m_windows[windowId]->width();
}

int NutshellWindowModule::getHeight(Ntsh::WindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	if (m_windows[windowId]->isMinimized()) {
		return 0;
	}
	return m_windows[windowId]->height();
}

void NutshellWindowModule::setPosition(Ntsh::WindowId windowId, int x, int y) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->move(x, y);
}

int NutshellWindowModule::getPositionX(Ntsh::WindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->x();
}

int NutshellWindowModule::getPositionY(Ntsh::WindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->y();
}

void NutshellWindowModule::setFullscreen(Ntsh::WindowId windowId, bool fullscreen) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	if (fullscreen) {
		m_windows[windowId]->showFullScreen();
	}
	else {
		m_windows[windowId]->showNormal();
	}
}

bool NutshellWindowModule::isFullscreen(Ntsh::WindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isFullScreen();
}

void NutshellWindowModule::pollEvents() {
	m_application->processEvents();
}

void NutshellWindowModule::setTitle(Ntsh::WindowId windowId, const std::string& title) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setWindowTitle(QString::fromStdString(title));
}

Ntsh::InputState NutshellWindowModule::getKeyState(Ntsh::WindowId windowId, Ntsh::InputKeyboardKey key) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getKeyState(key);
}

Ntsh::InputState NutshellWindowModule::getMouseButtonState(Ntsh::WindowId windowId, Ntsh::InputMouseButton mouseButton) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getMouseButtonState(mouseButton);
}

void NutshellWindowModule::setCursorPosition(Ntsh::WindowId windowId, int x, int y) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setCursorPosition(x, y);
}

int NutshellWindowModule::getCursorPositionX(Ntsh::WindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getCursorXPosition();
}

int NutshellWindowModule::getCursorPositionY(Ntsh::WindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getCursorYPosition();
}

void NutshellWindowModule::setCursorVisibility(Ntsh::WindowId windowId, bool visible) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setCursorVisibility(visible);
}

bool NutshellWindowModule::isCursorVisible(Ntsh::WindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isCursorVisible();
}

#if defined(NTSH_OS_WINDOWS)
HWND NutshellWindowModule::getNativeHandle(Ntsh::WindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return reinterpret_cast<HWND>(m_windows[windowId]->winId());
}
#elif defined(NTSH_OS_LINUX)
Window NutshellWindowModule::getNativeHandle(Ntsh::WindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return reinterpret_cast<Window>(m_windows[windowId]->winId());
}
#endif

extern "C" NTSH_MODULE_API NutshellWindowModuleInterface* createModule() {
	return new NutshellWindowModule;
}

extern "C" NTSH_MODULE_API void destroyModule(NutshellWindowModuleInterface* m) {
	delete m;
}