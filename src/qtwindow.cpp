#include "qtwindow.h"
#include "../external/Common/ntsh_engine_defines.h"
#include <QCursor>

QtWindow::QtWindow(QWidget* parent) : QWidget(parent) {
	setMouseTracking(true);
}

bool QtWindow::shouldClose() {
	return m_shouldClose;
}

void QtWindow::updateInputs(double dt) {
	NTSH_UNUSED(dt);

	for (auto& key : m_keyStateMap) {
		key.second = nextInputState(key.second);
	}

	for (auto& key : m_mouseButtonStateMap) {
		key.second = nextInputState(key.second);
	}
}

NtshInputState QtWindow::getKeyState(NtshInputKeyboardKey key) {
	return m_keyStateMap[m_keyMap[key]];
}

NtshInputState QtWindow::getButtonState(NtshInputMouseButton button) {
	return m_mouseButtonStateMap[m_mouseButtonMap[button]];
}

void QtWindow::setMousePosition(int x, int y) {
	QPoint screenPosition = mapToGlobal(QPoint(x, y));
	QCursor::setPos(screenPosition.x(), screenPosition.y());
}

int QtWindow::getMouseXPosition() {
	return m_mouseX;
}

int QtWindow::getMouseYPosition() {
	return m_mouseY;
}

NtshInputState QtWindow::nextInputState(NtshInputState inputState) {
	if (inputState == NtshInputState::Pressed) {
		return NtshInputState::Held;
	}
	else if (inputState == NtshInputState::Released) {
		return NtshInputState::None;
	}

	return inputState;
}

void QtWindow::closeEvent(QCloseEvent* event) {
	m_shouldClose = true;
	event->ignore();
}

void QtWindow::keyPressEvent(QKeyEvent* event) {
	Qt::Key key = static_cast<Qt::Key>(event->key());
	if (m_keyStateMap.find(key) != m_keyStateMap.end()) {
		NtshInputState currentState = m_keyStateMap[key];
		if (currentState == NtshInputState::None || currentState == NtshInputState::Released) {
			m_keyStateMap[key] = NtshInputState::Pressed;
		}
	}
}

void QtWindow::keyReleaseEvent(QKeyEvent* event) {
	Qt::Key key = static_cast<Qt::Key>(event->key());
	if (m_keyStateMap.find(key) != m_keyStateMap.end()) {
		NtshInputState currentState = m_keyStateMap[key];
		if (currentState == NtshInputState::Pressed || currentState == NtshInputState::Held) {
			m_keyStateMap[key] = NtshInputState::Released;
		}
	}
}

void QtWindow::mousePressEvent(QMouseEvent* event) {
	Qt::MouseButton button = event->button();
	if (m_mouseButtonStateMap.find(button) != m_mouseButtonStateMap.end()) {
		NtshInputState currentState = m_mouseButtonStateMap[button];
		if (currentState == NtshInputState::None || currentState == NtshInputState::Released) {
			m_mouseButtonStateMap[button] = NtshInputState::Pressed;
		}
	}
}

void QtWindow::mouseReleaseEvent(QMouseEvent* event) {
	Qt::MouseButton button = event->button();
	if (m_mouseButtonStateMap.find(button) != m_mouseButtonStateMap.end()) {
		NtshInputState currentState = m_mouseButtonStateMap[button];
		if (currentState == NtshInputState::Pressed || currentState == NtshInputState::Held) {
			m_mouseButtonStateMap[button] = NtshInputState::Released;
		}
	}
}

void QtWindow::mouseMoveEvent(QMouseEvent* event) {
	m_mouseX = event->pos().x();
	m_mouseY = event->pos().y();
}