#pragma once
#include "qwidget.h"
#include "../external/Common/utils/ntsh_engine_input_enums.h"
#include <QCloseEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <unordered_map>

class QtWindow : public QWidget {
public:
	QtWindow(QWidget* parent = nullptr);

	bool shouldClose();

	void updateInputs(double dt);

	NtshInputState getKeyState(NtshInputKeyboardKey key);
	NtshInputState getButtonState(NtshInputMouseButton button);

	void setCursorPosition(int x, int y);
	int getCursorXPosition();
	int getCursorYPosition();

	bool isCursorVisible();
	void setCursorVisibility(bool visible);

private:
	NtshInputState nextInputState(NtshInputState inputState);

protected:
	void closeEvent(QCloseEvent* event);
	void keyPressEvent(QKeyEvent* event);
	void keyReleaseEvent(QKeyEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);

private:
	bool m_shouldClose = false;

	int m_cursorX = 0;
	int m_cursorY = 0;

	bool m_cursorVisible = true;
	
	std::unordered_map<NtshInputKeyboardKey, Qt::Key> m_keyMap = { { NtshInputKeyboardKey::A, Qt::Key_A },
		{ NtshInputKeyboardKey::B, Qt::Key_B },
		{ NtshInputKeyboardKey::C, Qt::Key_C },
		{ NtshInputKeyboardKey::D, Qt::Key_D },
		{ NtshInputKeyboardKey::E, Qt::Key_E },
		{ NtshInputKeyboardKey::F, Qt::Key_F },
		{ NtshInputKeyboardKey::G, Qt::Key_G },
		{ NtshInputKeyboardKey::H, Qt::Key_H },
		{ NtshInputKeyboardKey::I, Qt::Key_I },
		{ NtshInputKeyboardKey::J, Qt::Key_J },
		{ NtshInputKeyboardKey::K, Qt::Key_K },
		{ NtshInputKeyboardKey::L, Qt::Key_L },
		{ NtshInputKeyboardKey::M, Qt::Key_M },
		{ NtshInputKeyboardKey::N, Qt::Key_N },
		{ NtshInputKeyboardKey::O, Qt::Key_O },
		{ NtshInputKeyboardKey::P, Qt::Key_P },
		{ NtshInputKeyboardKey::Q, Qt::Key_Q },
		{ NtshInputKeyboardKey::R, Qt::Key_R },
		{ NtshInputKeyboardKey::S, Qt::Key_S },
		{ NtshInputKeyboardKey::T, Qt::Key_T },
		{ NtshInputKeyboardKey::U, Qt::Key_U },
		{ NtshInputKeyboardKey::V, Qt::Key_V },
		{ NtshInputKeyboardKey::W, Qt::Key_W },
		{ NtshInputKeyboardKey::X, Qt::Key_X },
		{ NtshInputKeyboardKey::Y, Qt::Key_Y },
		{ NtshInputKeyboardKey::Z, Qt::Key_Z },
		{ NtshInputKeyboardKey::Space, Qt::Key_Space },
		{ NtshInputKeyboardKey::Shift, Qt::Key_Shift },
		{ NtshInputKeyboardKey::LeftCtrl, Qt::Key_Control },
		{ NtshInputKeyboardKey::RightCtrl, Qt::Key_Control },
		{ NtshInputKeyboardKey::Alt, Qt::Key_Alt },
		{ NtshInputKeyboardKey::Escape, Qt::Key_Escape },
		{ NtshInputKeyboardKey::Tab, Qt::Key_Tab },
		{ NtshInputKeyboardKey::Backspace, Qt::Key_Backspace },
		{ NtshInputKeyboardKey::Return, Qt::Key_Return },
		{ NtshInputKeyboardKey::Enter, Qt::Key_Enter },
		{ NtshInputKeyboardKey::Num0, Qt::Key_0 },
		{ NtshInputKeyboardKey::Num1, Qt::Key_1 },
		{ NtshInputKeyboardKey::Num2, Qt::Key_2 },
		{ NtshInputKeyboardKey::Num3, Qt::Key_3 },
		{ NtshInputKeyboardKey::Num4, Qt::Key_4 },
		{ NtshInputKeyboardKey::Num5, Qt::Key_5 },
		{ NtshInputKeyboardKey::Num6, Qt::Key_6 },
		{ NtshInputKeyboardKey::Num7, Qt::Key_7 },
		{ NtshInputKeyboardKey::Num8, Qt::Key_8 },
		{ NtshInputKeyboardKey::Num9, Qt::Key_9 },
		{ NtshInputKeyboardKey::Left, Qt::Key_Left },
		{ NtshInputKeyboardKey::Right, Qt::Key_Right },
		{ NtshInputKeyboardKey::Up, Qt::Key_Up },
		{ NtshInputKeyboardKey::Down, Qt::Key_Down },
		{ NtshInputKeyboardKey::F1, Qt::Key_F1 },
		{ NtshInputKeyboardKey::F2, Qt::Key_F2 },
		{ NtshInputKeyboardKey::F3, Qt::Key_F3 },
		{ NtshInputKeyboardKey::F4, Qt::Key_F4 },
		{ NtshInputKeyboardKey::F5, Qt::Key_F5 },
		{ NtshInputKeyboardKey::F6, Qt::Key_F6 },
		{ NtshInputKeyboardKey::F7, Qt::Key_F7 },
		{ NtshInputKeyboardKey::F8, Qt::Key_F8 },
		{ NtshInputKeyboardKey::F9, Qt::Key_F9 },
		{ NtshInputKeyboardKey::F10, Qt::Key_F10 },
		{ NtshInputKeyboardKey::F11, Qt::Key_F11 },
		{ NtshInputKeyboardKey::F12, Qt::Key_F12 }
	};
	std::unordered_map<Qt::Key, NtshInputState> m_keyStateMap = { { Qt::Key_A, NtshInputState::None },
		{ Qt::Key_B, NtshInputState::None },
		{ Qt::Key_C, NtshInputState::None },
		{ Qt::Key_D, NtshInputState::None },
		{ Qt::Key_E, NtshInputState::None },
		{ Qt::Key_F, NtshInputState::None },
		{ Qt::Key_G, NtshInputState::None },
		{ Qt::Key_H, NtshInputState::None },
		{ Qt::Key_I, NtshInputState::None },
		{ Qt::Key_J, NtshInputState::None },
		{ Qt::Key_K, NtshInputState::None },
		{ Qt::Key_L, NtshInputState::None },
		{ Qt::Key_M, NtshInputState::None },
		{ Qt::Key_N, NtshInputState::None },
		{ Qt::Key_O, NtshInputState::None },
		{ Qt::Key_P, NtshInputState::None },
		{ Qt::Key_Q, NtshInputState::None },
		{ Qt::Key_R, NtshInputState::None },
		{ Qt::Key_S, NtshInputState::None },
		{ Qt::Key_T, NtshInputState::None },
		{ Qt::Key_U, NtshInputState::None },
		{ Qt::Key_V, NtshInputState::None },
		{ Qt::Key_W, NtshInputState::None },
		{ Qt::Key_X, NtshInputState::None },
		{ Qt::Key_Y, NtshInputState::None },
		{ Qt::Key_Z, NtshInputState::None },
		{ Qt::Key_Space, NtshInputState::None },
		{ Qt::Key_Shift, NtshInputState::None },
		{ Qt::Key_Control, NtshInputState::None },
		{ Qt::Key_Alt, NtshInputState::None },
		{ Qt::Key_Escape, NtshInputState::None },
		{ Qt::Key_Tab, NtshInputState::None },
		{ Qt::Key_Backspace, NtshInputState::None },
		{ Qt::Key_Enter, NtshInputState::None },
		{ Qt::Key_Return, NtshInputState::None },
		{ Qt::Key_0, NtshInputState::None },
		{ Qt::Key_1, NtshInputState::None },
		{ Qt::Key_2, NtshInputState::None },
		{ Qt::Key_3, NtshInputState::None },
		{ Qt::Key_4, NtshInputState::None },
		{ Qt::Key_5, NtshInputState::None },
		{ Qt::Key_6, NtshInputState::None },
		{ Qt::Key_7, NtshInputState::None },
		{ Qt::Key_8, NtshInputState::None },
		{ Qt::Key_9, NtshInputState::None },
		{ Qt::Key_Left, NtshInputState::None },
		{ Qt::Key_Right, NtshInputState::None },
		{ Qt::Key_Up, NtshInputState::None },
		{ Qt::Key_Down, NtshInputState::None },
		{ Qt::Key_F1, NtshInputState::None },
		{ Qt::Key_F2, NtshInputState::None },
		{ Qt::Key_F3, NtshInputState::None },
		{ Qt::Key_F4, NtshInputState::None },
		{ Qt::Key_F5, NtshInputState::None },
		{ Qt::Key_F6, NtshInputState::None },
		{ Qt::Key_F7, NtshInputState::None },
		{ Qt::Key_F8, NtshInputState::None },
		{ Qt::Key_F9, NtshInputState::None },
		{ Qt::Key_F10, NtshInputState::None },
		{ Qt::Key_F11, NtshInputState::None },
		{ Qt::Key_F12, NtshInputState::None }
	};

	std::unordered_map<NtshInputMouseButton, Qt::MouseButton> m_mouseButtonMap = { { NtshInputMouseButton::One, Qt::LeftButton },
		{ NtshInputMouseButton::Two, Qt::RightButton },
		{ NtshInputMouseButton::Three, Qt::MiddleButton },
		{ NtshInputMouseButton::Four, Qt::ExtraButton1 },
		{ NtshInputMouseButton::Five, Qt::ExtraButton2 },
		{ NtshInputMouseButton::Six, Qt::ExtraButton3 },
		{ NtshInputMouseButton::Seven, Qt::ExtraButton4 },
		{ NtshInputMouseButton::Eight, Qt::ExtraButton5 },
	};
	std::unordered_map<Qt::MouseButton, NtshInputState> m_mouseButtonStateMap = { { Qt::LeftButton, NtshInputState::None },
		{ Qt::RightButton, NtshInputState::None },
		{ Qt::MiddleButton, NtshInputState::None },
		{ Qt::ExtraButton1, NtshInputState::None },
		{ Qt::ExtraButton2, NtshInputState::None },
		{ Qt::ExtraButton3, NtshInputState::None },
		{ Qt::ExtraButton4, NtshInputState::None },
		{ Qt::ExtraButton5, NtshInputState::None },
	};
};