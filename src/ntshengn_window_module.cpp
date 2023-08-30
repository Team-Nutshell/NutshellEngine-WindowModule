#include "ntshengn_window_module.h"
#if defined(NTSHENGN_OS_WINDOWS)
#include <windows.h>
#elif defined(NTSHENGN_OS_LINUX)
#include <QX11Info>
#endif
#include "../Module/utils/ntshengn_module_defines.h"
#include "../Module/utils/ntshengn_dynamic_library.h"
#include "../Common/utils/ntshengn_defines.h"
#include "../Common/utils/ntshengn_enums.h"
#include <QScreen>
#include <QIcon>
#include <limits>

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

NtshEngn::WindowID NtshEngn::WindowModule::openWindow(int width, int height, const std::string& title) {
	m_windows[m_id] = std::make_unique<QtWindow>();
	m_windows[m_id]->open(width, height, title);

	if (m_mainWindow == std::numeric_limits<WindowID>::max()) {
		m_mainWindow = m_id;
	}

	return m_id++;
}

bool NtshEngn::WindowModule::isWindowOpen(WindowID windowID) {
	return (m_windows.find(windowID) != m_windows.end()) ? !m_windows[windowID]->shouldClose() : false;
}

void NtshEngn::WindowModule::closeWindow(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	
	m_windows[windowID]->closeWindow();
}

NtshEngn::WindowID NtshEngn::WindowModule::getMainWindowID() {
	return m_mainWindow;
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

void NtshEngn::WindowModule::setWindowSize(WindowID windowID, int width, int height) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	m_windows[windowID]->resize(width, height);
}

int NtshEngn::WindowModule::getWindowWidth(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	if (m_windows[windowID]->isMinimized()) {
		return 0;
	}
	return m_windows[windowID]->width();
}

int NtshEngn::WindowModule::getWindowHeight(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	if (m_windows[windowID]->isMinimized()) {
		return 0;
	}
	return m_windows[windowID]->height();
}

void NtshEngn::WindowModule::setWindowPosition(WindowID windowID, int x, int y) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	m_windows[windowID]->move(x, y);
}

int NtshEngn::WindowModule::getWindowPositionX(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->x();
}

int NtshEngn::WindowModule::getWindowPositionY(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->y();
}

void NtshEngn::WindowModule::setWindowFullscreen(WindowID windowID, bool fullscreen) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	if (fullscreen) {
		m_windows[windowID]->showFullScreen();
	}
	else {
		m_windows[windowID]->showNormal();
	}
}

bool NtshEngn::WindowModule::isWindowFullscreen(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->isFullScreen();
}

void NtshEngn::WindowModule::setWindowBorderless(WindowID windowID, bool borderless) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	m_windows[windowID]->setBorderless(borderless);
}

bool NtshEngn::WindowModule::isWindowBorderless(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->isBorderless();
}

void NtshEngn::WindowModule::setWindowResizable(WindowID windowID, bool resizable) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	m_windows[windowID]->setResizable(resizable);
}

bool NtshEngn::WindowModule::isWindowResizable(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->isResizable();
}

void NtshEngn::WindowModule::pollEvents() {
	m_application->processEvents();
}

void NtshEngn::WindowModule::setWindowTitle(WindowID windowID, const std::string& title) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	m_windows[windowID]->setWindowTitle(QString::fromStdString(title));
}

void NtshEngn::WindowModule::setWindowIcon(WindowID windowID, const Image& image) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	QImage im(image.data.data(), image.width, image.height, QImage::Format_RGBA8888);
	QPixmap pixmap = QPixmap::fromImage(im);
	QIcon icon(pixmap);
	m_windows[windowID]->setWindowIcon(icon);
}

NtshEngn::InputState NtshEngn::WindowModule::getKeyState(WindowID windowID, InputKeyboardKey key) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->getKeyState(key);
}

NtshEngn::InputState NtshEngn::WindowModule::getMouseButtonState(WindowID windowID, InputMouseButton mouseButton) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->getMouseButtonState(mouseButton);
}

void NtshEngn::WindowModule::setCursorPosition(WindowID windowID, int x, int y) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	m_windows[windowID]->setCursorPosition(x, y);
}

int NtshEngn::WindowModule::getCursorPositionX(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->getCursorXPosition();
}

int NtshEngn::WindowModule::getCursorPositionY(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->getCursorYPosition();
}

float NtshEngn::WindowModule::getMouseScrollOffsetX(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->getMouseScrollOffsetX();
}

float NtshEngn::WindowModule::getMouseScrollOffsetY(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->getMouseScrollOffsetY();
}

void NtshEngn::WindowModule::setCursorVisibility(WindowID windowID, bool visible) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	m_windows[windowID]->setCursorVisibility(visible);
}

bool NtshEngn::WindowModule::isCursorVisible(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->isCursorVisible();
}

std::vector<NtshEngn::GamepadID> NtshEngn::WindowModule::getConnectedGamepads() {
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return std::vector<GamepadID>();
}

NtshEngn::InputState NtshEngn::WindowModule::getGamepadButtonState(GamepadID gamepadID, InputGamepadButton button) {
	NTSHENGN_UNUSED(gamepadID);
	NTSHENGN_UNUSED(button);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return InputState::None;
}

float NtshEngn::WindowModule::getGamepadStickAxisX(GamepadID gamepadID, InputGamepadStick stick) {
	NTSHENGN_UNUSED(gamepadID);
	NTSHENGN_UNUSED(stick);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return 0.0f;
}

float NtshEngn::WindowModule::getGamepadStickAxisY(GamepadID gamepadID, InputGamepadStick stick) {
	NTSHENGN_UNUSED(gamepadID);
	NTSHENGN_UNUSED(stick);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return 0.0f;
}

float NtshEngn::WindowModule::getGamepadLeftTrigger(GamepadID gamepadID) {
	NTSHENGN_UNUSED(gamepadID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return 0.0f;
}

float NtshEngn::WindowModule::getGamepadRightTrigger(GamepadID gamepadID) {
	NTSHENGN_UNUSED(gamepadID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return 0.0f;
}

int NtshEngn::WindowModule::getMonitorWidth() {
	return m_application->primaryScreen()->geometry().width();
}

int NtshEngn::WindowModule::getMonitorHeight() {
	return m_application->primaryScreen()->geometry().height();
}

int NtshEngn::WindowModule::getMonitorRefreshRate() {
	return static_cast<int>(m_application->primaryScreen()->refreshRate());
}

float NtshEngn::WindowModule::getMonitorDisplayScaling() {
	return static_cast<float>(m_application->primaryScreen()->devicePixelRatio());
}

NtshEngn::NativeWindowHandle NtshEngn::WindowModule::getWindowNativeHandle(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return reinterpret_cast<NativeWindowHandle>(m_windows[windowID]->winId());
}

NtshEngn::NativeWindowAdditionalInformation NtshEngn::WindowModule::getWindowNativeAdditionalInformation(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

#if defined(NTSHENGN_OS_WINDOWS)
	return reinterpret_cast<NativeWindowAdditionalInformation>(GetWindowLongPtr(reinterpret_cast<HWND>(m_windows[windowID]->winId()), GWLP_HINSTANCE));
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