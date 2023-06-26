#include "ntshengn_window_module.h"
#if defined(NTSHENGN_OS_WINDOWS)
#include <windows.h>
#elif defined(NTSHENGN_OS_LINUX)
#include <QX11Info>
#endif
#include "../external/Module/utils/ntshengn_module_defines.h"
#include "../external/Module/utils/ntshengn_dynamic_library.h"
#include "../external/Common/utils/ntshengn_defines.h"
#include "../external/Common/utils/ntshengn_enums.h"
#include <thread>

void NtshEngn::WindowModule::init() {
	int argc = 0;
	m_application = std::make_unique<QApplication>(argc, nullptr);
}

void NtshEngn::WindowModule::update(double dt) {
	NTSHENGN_UNUSED(dt);

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

void NtshEngn::WindowModule::destroy() {
	for (auto it = m_windows.begin(); it != m_windows.end(); ) {
		it->second->close();
		it = m_windows.erase(it);
	}
}

NtshEngn::WindowId NtshEngn::WindowModule::open(int width, int height, const std::string& title) {
	m_windows[m_id] = std::make_unique<QtWindow>();
	m_windows[m_id]->open(width, height, title);

	return m_id++;
}

bool NtshEngn::WindowModule::isOpen(WindowId windowId) {
	return (m_windows.find(windowId) != m_windows.end()) ? !m_windows[windowId]->shouldClose() : false;
}

void NtshEngn::WindowModule::close(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->closeWindow();
}

uint64_t NtshEngn::WindowModule::windowCount() {
	uint64_t count = 0;
	for (auto it = m_windows.begin(); it != m_windows.end(); it++) {
		if (!it->second->shouldClose()) {
			count++;
		}
	}

	return count;
}

void NtshEngn::WindowModule::setSize(WindowId windowId, int width, int height) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->resize(width, height);
}

int NtshEngn::WindowModule::getWidth(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	if (m_windows[windowId]->isMinimized()) {
		return 0;
	}
	return m_windows[windowId]->width();
}

int NtshEngn::WindowModule::getHeight(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	if (m_windows[windowId]->isMinimized()) {
		return 0;
	}
	return m_windows[windowId]->height();
}

void NtshEngn::WindowModule::setPosition(WindowId windowId, int x, int y) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->move(x, y);
}

int NtshEngn::WindowModule::getPositionX(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->x();
}

int NtshEngn::WindowModule::getPositionY(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->y();
}

void NtshEngn::WindowModule::setFullscreen(WindowId windowId, bool fullscreen) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	if (fullscreen) {
		m_windows[windowId]->showFullScreen();
	}
	else {
		m_windows[windowId]->showNormal();
	}
}

bool NtshEngn::WindowModule::isFullscreen(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isFullScreen();
}

void NtshEngn::WindowModule::setBorderless(WindowId windowId, bool borderless) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setBorderless(borderless);
}

bool NtshEngn::WindowModule::isBorderless(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isBorderless();
}

void NtshEngn::WindowModule::setResizable(WindowId windowId, bool resizable) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setResizable(resizable);
}

bool NtshEngn::WindowModule::isResizable(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isResizable();
}

void NtshEngn::WindowModule::pollEvents() {
	m_application->processEvents();
}

void NtshEngn::WindowModule::setTitle(WindowId windowId, const std::string& title) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setWindowTitle(QString::fromStdString(title));
}

NtshEngn::InputState NtshEngn::WindowModule::getKeyState(WindowId windowId, InputKeyboardKey key) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getKeyState(key);
}

NtshEngn::InputState NtshEngn::WindowModule::getMouseButtonState(WindowId windowId, InputMouseButton mouseButton) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getMouseButtonState(mouseButton);
}

void NtshEngn::WindowModule::setCursorPosition(WindowId windowId, int x, int y) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setCursorPosition(x, y);
}

int NtshEngn::WindowModule::getCursorPositionX(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getCursorXPosition();
}

int NtshEngn::WindowModule::getCursorPositionY(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getCursorYPosition();
}

void NtshEngn::WindowModule::setCursorVisibility(WindowId windowId, bool visible) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setCursorVisibility(visible);
}

bool NtshEngn::WindowModule::isCursorVisible(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isCursorVisible();
}

NtshEngn::NativeWindowHandle NtshEngn::WindowModule::getNativeHandle(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return reinterpret_cast<NativeWindowHandle>(m_windows[windowId]->winId());
}

NtshEngn::NativeWindowAdditionalInformation NtshEngn::WindowModule::getNativeAdditionalInformation(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
#if defined(NTSHENGN_OS_WINDOWS)
	return reinterpret_cast<NativeWindowAdditionalInformation>(GetWindowLongPtr(reinterpret_cast<HWND>(m_windows[windowId]->winId()), GWLP_HINSTANCE));
#elif defined (NTSHENGN_OS_LINUX)
	return reinterpret_cast<NativeWindowAdditionalInformation>(QX11Info::display());
#endif
}

extern "C" NTSHENGN_MODULE_API NtshEngn::WindowModuleInterface* createModule() {
	return new NtshEngn::WindowModule;
}

extern "C" NTSHENGN_MODULE_API void destroyModule(NtshEngn::WindowModuleInterface* m) {
	delete m;
}