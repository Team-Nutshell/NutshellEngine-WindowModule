#include "qtwindow.h"
#include "../Common/utils/ntshengn_defines.h"
#include <QCursor>

QtWindow::QtWindow(QWidget* parent) : QWidget(parent) {
	setMouseTracking(true);
}

void QtWindow::open(int width, int height, const std::string& title) {
	setWindowTitle(QString::fromStdString(title));
	resize(width, height);
	show();
}

bool QtWindow::shouldClose() {
	return m_shouldClose;
}

void QtWindow::closeWindow() {
	m_shouldClose = true;
}

void QtWindow::updateInputs(double dt) {
	NTSHENGN_UNUSED(dt);

	for (auto& key : m_keyStateMap) {
		key.second = nextInputState(key.second);
	}

	for (auto& key : m_mouseButtonStateMap) {
		key.second = nextInputState(key.second);
	}
}

void QtWindow::setBorderless(bool borderless) {
	setWindowFlags(windowFlags().setFlag(Qt::FramelessWindowHint, borderless));
	show();
}

bool QtWindow::isBorderless() {
	return windowFlags().testFlag(Qt::FramelessWindowHint);
}

void QtWindow::setResizable(bool resizable) {
	setWindowFlags(windowFlags().setFlag(Qt::MSWindowsFixedSizeDialogHint, !resizable));
	show();
}

bool QtWindow::isResizable() {
	return !windowFlags().testFlag(Qt::MSWindowsFixedSizeDialogHint);
}

NtshEngn::InputState QtWindow::getKeyState(NtshEngn::InputKeyboardKey key) {
	return m_keyStateMap[m_keyMap[key]];
}

NtshEngn::InputState QtWindow::getMouseButtonState(NtshEngn::InputMouseButton mouseButton) {
	return m_mouseButtonStateMap[m_mouseButtonMap[mouseButton]];
}

void QtWindow::setCursorPosition(int x, int y) {
	QPoint screenPosition = mapToGlobal(QPoint(x, y));
	QCursor::setPos(screenPosition.x(), screenPosition.y());
	m_cursorX = x;
	m_cursorY = y;
}

int QtWindow::getCursorXPosition() {
	return m_cursorX;
}

int QtWindow::getCursorYPosition() {
	return m_cursorY;
}

void QtWindow::setCursorVisibility(bool visible) {
	if (!isCursorVisible() && visible) {
		setCursor(QCursor());
		m_cursorVisible = true;
	}
	else if (isCursorVisible() && !visible) {
		setCursor(QCursor(Qt::BlankCursor));
		m_cursorVisible = false;
	}
}

bool QtWindow::isCursorVisible() {
	return m_cursorVisible;
}

NtshEngn::InputState QtWindow::nextInputState(NtshEngn::InputState inputState) {
	if (inputState == NtshEngn::InputState::Pressed) {
		return NtshEngn::InputState::Held;
	}
	else if (inputState == NtshEngn::InputState::Released) {
		return NtshEngn::InputState::None;
	}

	return inputState;
}

void QtWindow::closeEvent(QCloseEvent* event) {
	closeWindow();
	event->ignore();
}

void QtWindow::keyPressEvent(QKeyEvent* event) {
	Qt::Key key = static_cast<Qt::Key>(event->key());
	if (m_keyStateMap.find(key) != m_keyStateMap.end()) {
		NtshEngn::InputState currentState = m_keyStateMap[key];
		if (currentState == NtshEngn::InputState::None || currentState == NtshEngn::InputState::Released) {
			m_keyStateMap[key] = NtshEngn::InputState::Pressed;
			m_keyStateMap[Qt::Key_unknown] = NtshEngn::InputState::Pressed; // Any
		}
	}
}

void QtWindow::keyReleaseEvent(QKeyEvent* event) {
	Qt::Key key = static_cast<Qt::Key>(event->key());
	if (m_keyStateMap.find(key) != m_keyStateMap.end()) {
		NtshEngn::InputState currentState = m_keyStateMap[key];
		if (currentState == NtshEngn::InputState::Pressed || currentState == NtshEngn::InputState::Held) {
			m_keyStateMap[key] = NtshEngn::InputState::Released;
			m_keyStateMap[Qt::Key_unknown] = NtshEngn::InputState::Released; // Any
		}
	}
}

void QtWindow::mousePressEvent(QMouseEvent* event) {
	Qt::MouseButton button = event->button();
	if (m_mouseButtonStateMap.find(button) != m_mouseButtonStateMap.end()) {
		NtshEngn::InputState currentState = m_mouseButtonStateMap[button];
		if (currentState == NtshEngn::InputState::None || currentState == NtshEngn::InputState::Released) {
			m_mouseButtonStateMap[button] = NtshEngn::InputState::Pressed;
			m_mouseButtonStateMap[Qt::MouseButtonMask] = NtshEngn::InputState::Pressed; // Any
		}
	}
}

void QtWindow::mouseReleaseEvent(QMouseEvent* event) {
	Qt::MouseButton button = event->button();
	if (m_mouseButtonStateMap.find(button) != m_mouseButtonStateMap.end()) {
		NtshEngn::InputState currentState = m_mouseButtonStateMap[button];
		if (currentState == NtshEngn::InputState::Pressed || currentState == NtshEngn::InputState::Held) {
			m_mouseButtonStateMap[button] = NtshEngn::InputState::Released;
			m_mouseButtonStateMap[Qt::MouseButtonMask] = NtshEngn::InputState::Released; // Any
		}
	}
}

void QtWindow::mouseMoveEvent(QMouseEvent* event) {
	m_cursorX = event->pos().x();
	m_cursorY = event->pos().y();
}