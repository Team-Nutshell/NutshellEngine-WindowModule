#include "ntsh_window_module.h"
#include "../external/Module/utils/ntsh_module_defines.h"
#include "../external/Module/utils/ntsh_dynamic_library.h"
#include "../external/Common/utils/ntsh_engine_defines.h"
#include "../external/Common/utils/ntsh_engine_enums.h"
#include <thread>

void NutshellWindowModule::init() {
	int argc = 0;
	m_application = std::make_unique<QApplication>(argc, nullptr);

	m_window = std::make_unique<QtWindow>();
	m_window->resize(1280, 720);
	m_window->show();
}

void NutshellWindowModule::update(double dt) {
	NTSH_UNUSED(dt);

	m_window->updateInputs(dt);

	m_application->processEvents();
}

void NutshellWindowModule::destroy() {
	m_window->close();
}

void NutshellWindowModule::close() {
	m_window->close();
}

bool NutshellWindowModule::shouldClose() {
	return m_window->shouldClose();
}

void NutshellWindowModule::setSize(int width, int height) {
	m_window->resize(width, height);
}

int NutshellWindowModule::getWidth() {
	if (m_window->isMinimized()) {
		return 0;
	}
	return m_window->width();
}

int NutshellWindowModule::getHeight() {
	if (m_window->isMinimized()) {
		return 0;
	}
	return m_window->height();
}

bool NutshellWindowModule::isFullscreen() {
	return m_window->isFullScreen();
}

void NutshellWindowModule::setFullscreen(bool fullscreen) {
	if (fullscreen) {
		m_window->showFullScreen();
	}
	else {
		m_window->showNormal();
	}
}

void NutshellWindowModule::pollEvents() {
	m_application->processEvents();
}

void NutshellWindowModule::setTitle(const std::string& title) {
	m_window->setWindowTitle(QString::fromStdString(title));
}

NtshInputState NutshellWindowModule::getKeyState(NtshInputKeyboardKey key) {
	return m_window->getKeyState(key);
}

NtshInputState NutshellWindowModule::getButtonState(NtshInputMouseButton button) {
	return m_window->getButtonState(button);
}

void NutshellWindowModule::setCursorPosition(int x, int y) {
	m_window->setCursorPosition(x, y);
}

int NutshellWindowModule::getCursorXPosition() {
	return m_window->getCursorXPosition();
}

int NutshellWindowModule::getCursorYPosition() {
	return m_window->getCursorYPosition();
}

bool NutshellWindowModule::isCursorVisible() {
	return m_cursorVisible;
}

void NutshellWindowModule::setCursorVisibility(bool visible) {
	if (!isCursorVisible() && visible) {
		QApplication::setOverrideCursor(QCursor());
		m_cursorVisible = true;
	}
	else if (isCursorVisible() && !visible) {
		QApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
		m_cursorVisible = false;
	}
}

#ifdef NTSH_OS_WINDOWS
HWND NutshellWindowModule::getNativeHandle() {
	return reinterpret_cast<HWND>(m_window->winId());
}
#elif NTSH_OS_LINUX
Window NutshellWindowModule::getNativeHandle() {
	return reinterpret_cast<Window>(m_window->winId());
}
#endif

extern "C" NTSH_MODULE_API NutshellWindowModuleInterface* createModule() {
	return new NutshellWindowModule;
}

extern "C" NTSH_MODULE_API void destroyModule(NutshellWindowModuleInterface* m) {
	delete m;
}