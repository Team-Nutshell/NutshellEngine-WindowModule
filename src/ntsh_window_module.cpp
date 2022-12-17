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

	for (size_t i = 0; i < m_windows.size(); i++) {
		if (m_windows[i]->shouldClose()) {
			i = m_windows.erase(i);
		}
		else {
			m_windows[i]->updateInputs(dt);
		}
	}

	m_application->processEvents();
}

void NutshellWindowModule::destroy() {
	for (size_t i = 0; i < m_windows.size(); i++) {
		m_windows[i]->close();
		m_windows.erase(i);
	}
}

NtshWindowId NutshellWindowModule::open() {
	m_windows[m_id] = std::make_unique<QtWindow>();
	m_windows[m_id]->open(m_name);

	return m_id++;
}

bool NutshellWindowModule::isOpen(NtshWindowId windowId) {
	return (m_windows.find(windowId) != m_windows.end()) ? !m_windows[windowId]->shouldClose() : false;
}

void NutshellWindowModule::close(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->closeWindow();
}

uint64_t NutshellWindowModule::windowCount() {
	return m_windows.size();
}

void NutshellWindowModule::setSize(NtshWindowId windowId, int width, int height) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->resize(width, height);
}

int NutshellWindowModule::getWidth(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	if (m_windows[windowId]->isMinimized()) {
		return 0;
	}
	return m_windows[windowId]->width();
}

int NutshellWindowModule::getHeight(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	if (m_windows[windowId]->isMinimized()) {
		return 0;
	}
	return m_windows[windowId]->height();
}

void NutshellWindowModule::setPosition(NtshWindowId windowId, int x, int y) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->move(x, y);
}

int NutshellWindowModule::getPositionX(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->x();
}

int NutshellWindowModule::getPositionY(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->y();
}

void NutshellWindowModule::setFullscreen(NtshWindowId windowId, bool fullscreen) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	if (fullscreen) {
		m_windows[windowId]->showFullScreen();
	}
	else {
		m_windows[windowId]->showNormal();
	}
}

bool NutshellWindowModule::isFullscreen(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isFullScreen();
}

void NutshellWindowModule::pollEvents() {
	m_application->processEvents();
}

void NutshellWindowModule::setTitle(NtshWindowId windowId, const std::string& title) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setWindowTitle(QString::fromStdString(title));
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
	return m_windows[windowId]->getCursorXPosition();
}

int NutshellWindowModule::getCursorPositionY(NtshWindowId windowId) {
	NTSH_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getCursorYPosition();
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
	return reinterpret_cast<HWND>(m_windows[windowId]->winId());
}
#elif defined(NTSH_OS_LINUX)
Window NutshellWindowModule::getNativeHandle(NtshWindowId windowId) {
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