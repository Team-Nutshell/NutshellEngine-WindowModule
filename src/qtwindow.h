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

	void open(int width, int height, const std::string& title);
	bool shouldClose();
	void closeWindow();

	void updateInputs(double dt);

	Ntsh::InputState getKeyState(Ntsh::InputKeyboardKey key);
	Ntsh::InputState getMouseButtonState(Ntsh::InputMouseButton mouseButton);

	void setCursorPosition(int x, int y);
	int getCursorXPosition();
	int getCursorYPosition();

	void setCursorVisibility(bool visible);
	bool isCursorVisible();

private:
	Ntsh::InputState nextInputState(Ntsh::InputState inputState);

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
	
	std::unordered_map<Ntsh::InputKeyboardKey, Qt::Key> m_keyMap = { { Ntsh::InputKeyboardKey::A, Qt::Key_A },
		{ Ntsh::InputKeyboardKey::B, Qt::Key_B },
		{ Ntsh::InputKeyboardKey::C, Qt::Key_C },
		{ Ntsh::InputKeyboardKey::D, Qt::Key_D },
		{ Ntsh::InputKeyboardKey::E, Qt::Key_E },
		{ Ntsh::InputKeyboardKey::F, Qt::Key_F },
		{ Ntsh::InputKeyboardKey::G, Qt::Key_G },
		{ Ntsh::InputKeyboardKey::H, Qt::Key_H },
		{ Ntsh::InputKeyboardKey::I, Qt::Key_I },
		{ Ntsh::InputKeyboardKey::J, Qt::Key_J },
		{ Ntsh::InputKeyboardKey::K, Qt::Key_K },
		{ Ntsh::InputKeyboardKey::L, Qt::Key_L },
		{ Ntsh::InputKeyboardKey::M, Qt::Key_M },
		{ Ntsh::InputKeyboardKey::N, Qt::Key_N },
		{ Ntsh::InputKeyboardKey::O, Qt::Key_O },
		{ Ntsh::InputKeyboardKey::P, Qt::Key_P },
		{ Ntsh::InputKeyboardKey::Q, Qt::Key_Q },
		{ Ntsh::InputKeyboardKey::R, Qt::Key_R },
		{ Ntsh::InputKeyboardKey::S, Qt::Key_S },
		{ Ntsh::InputKeyboardKey::T, Qt::Key_T },
		{ Ntsh::InputKeyboardKey::U, Qt::Key_U },
		{ Ntsh::InputKeyboardKey::V, Qt::Key_V },
		{ Ntsh::InputKeyboardKey::W, Qt::Key_W },
		{ Ntsh::InputKeyboardKey::X, Qt::Key_X },
		{ Ntsh::InputKeyboardKey::Y, Qt::Key_Y },
		{ Ntsh::InputKeyboardKey::Z, Qt::Key_Z },
		{ Ntsh::InputKeyboardKey::Space, Qt::Key_Space },
		{ Ntsh::InputKeyboardKey::Shift, Qt::Key_Shift },
		{ Ntsh::InputKeyboardKey::LeftCtrl, Qt::Key_Control },
		{ Ntsh::InputKeyboardKey::RightCtrl, Qt::Key_Control },
		{ Ntsh::InputKeyboardKey::Alt, Qt::Key_Alt },
		{ Ntsh::InputKeyboardKey::Escape, Qt::Key_Escape },
		{ Ntsh::InputKeyboardKey::Tab, Qt::Key_Tab },
		{ Ntsh::InputKeyboardKey::Backspace, Qt::Key_Backspace },
		{ Ntsh::InputKeyboardKey::Return, Qt::Key_Return },
		{ Ntsh::InputKeyboardKey::Enter, Qt::Key_Enter },
		{ Ntsh::InputKeyboardKey::Num0, Qt::Key_0 },
		{ Ntsh::InputKeyboardKey::Num1, Qt::Key_1 },
		{ Ntsh::InputKeyboardKey::Num2, Qt::Key_2 },
		{ Ntsh::InputKeyboardKey::Num3, Qt::Key_3 },
		{ Ntsh::InputKeyboardKey::Num4, Qt::Key_4 },
		{ Ntsh::InputKeyboardKey::Num5, Qt::Key_5 },
		{ Ntsh::InputKeyboardKey::Num6, Qt::Key_6 },
		{ Ntsh::InputKeyboardKey::Num7, Qt::Key_7 },
		{ Ntsh::InputKeyboardKey::Num8, Qt::Key_8 },
		{ Ntsh::InputKeyboardKey::Num9, Qt::Key_9 },
		{ Ntsh::InputKeyboardKey::Left, Qt::Key_Left },
		{ Ntsh::InputKeyboardKey::Right, Qt::Key_Right },
		{ Ntsh::InputKeyboardKey::Up, Qt::Key_Up },
		{ Ntsh::InputKeyboardKey::Down, Qt::Key_Down },
		{ Ntsh::InputKeyboardKey::F1, Qt::Key_F1 },
		{ Ntsh::InputKeyboardKey::F2, Qt::Key_F2 },
		{ Ntsh::InputKeyboardKey::F3, Qt::Key_F3 },
		{ Ntsh::InputKeyboardKey::F4, Qt::Key_F4 },
		{ Ntsh::InputKeyboardKey::F5, Qt::Key_F5 },
		{ Ntsh::InputKeyboardKey::F6, Qt::Key_F6 },
		{ Ntsh::InputKeyboardKey::F7, Qt::Key_F7 },
		{ Ntsh::InputKeyboardKey::F8, Qt::Key_F8 },
		{ Ntsh::InputKeyboardKey::F9, Qt::Key_F9 },
		{ Ntsh::InputKeyboardKey::F10, Qt::Key_F10 },
		{ Ntsh::InputKeyboardKey::F11, Qt::Key_F11 },
		{ Ntsh::InputKeyboardKey::F12, Qt::Key_F12 }
	};
	std::unordered_map<Qt::Key, Ntsh::InputState> m_keyStateMap = { { Qt::Key_A, Ntsh::InputState::None },
		{ Qt::Key_B, Ntsh::InputState::None },
		{ Qt::Key_C, Ntsh::InputState::None },
		{ Qt::Key_D, Ntsh::InputState::None },
		{ Qt::Key_E, Ntsh::InputState::None },
		{ Qt::Key_F, Ntsh::InputState::None },
		{ Qt::Key_G, Ntsh::InputState::None },
		{ Qt::Key_H, Ntsh::InputState::None },
		{ Qt::Key_I, Ntsh::InputState::None },
		{ Qt::Key_J, Ntsh::InputState::None },
		{ Qt::Key_K, Ntsh::InputState::None },
		{ Qt::Key_L, Ntsh::InputState::None },
		{ Qt::Key_M, Ntsh::InputState::None },
		{ Qt::Key_N, Ntsh::InputState::None },
		{ Qt::Key_O, Ntsh::InputState::None },
		{ Qt::Key_P, Ntsh::InputState::None },
		{ Qt::Key_Q, Ntsh::InputState::None },
		{ Qt::Key_R, Ntsh::InputState::None },
		{ Qt::Key_S, Ntsh::InputState::None },
		{ Qt::Key_T, Ntsh::InputState::None },
		{ Qt::Key_U, Ntsh::InputState::None },
		{ Qt::Key_V, Ntsh::InputState::None },
		{ Qt::Key_W, Ntsh::InputState::None },
		{ Qt::Key_X, Ntsh::InputState::None },
		{ Qt::Key_Y, Ntsh::InputState::None },
		{ Qt::Key_Z, Ntsh::InputState::None },
		{ Qt::Key_Space, Ntsh::InputState::None },
		{ Qt::Key_Shift, Ntsh::InputState::None },
		{ Qt::Key_Control, Ntsh::InputState::None },
		{ Qt::Key_Alt, Ntsh::InputState::None },
		{ Qt::Key_Escape, Ntsh::InputState::None },
		{ Qt::Key_Tab, Ntsh::InputState::None },
		{ Qt::Key_Backspace, Ntsh::InputState::None },
		{ Qt::Key_Enter, Ntsh::InputState::None },
		{ Qt::Key_Return, Ntsh::InputState::None },
		{ Qt::Key_0, Ntsh::InputState::None },
		{ Qt::Key_1, Ntsh::InputState::None },
		{ Qt::Key_2, Ntsh::InputState::None },
		{ Qt::Key_3, Ntsh::InputState::None },
		{ Qt::Key_4, Ntsh::InputState::None },
		{ Qt::Key_5, Ntsh::InputState::None },
		{ Qt::Key_6, Ntsh::InputState::None },
		{ Qt::Key_7, Ntsh::InputState::None },
		{ Qt::Key_8, Ntsh::InputState::None },
		{ Qt::Key_9, Ntsh::InputState::None },
		{ Qt::Key_Left, Ntsh::InputState::None },
		{ Qt::Key_Right, Ntsh::InputState::None },
		{ Qt::Key_Up, Ntsh::InputState::None },
		{ Qt::Key_Down, Ntsh::InputState::None },
		{ Qt::Key_F1, Ntsh::InputState::None },
		{ Qt::Key_F2, Ntsh::InputState::None },
		{ Qt::Key_F3, Ntsh::InputState::None },
		{ Qt::Key_F4, Ntsh::InputState::None },
		{ Qt::Key_F5, Ntsh::InputState::None },
		{ Qt::Key_F6, Ntsh::InputState::None },
		{ Qt::Key_F7, Ntsh::InputState::None },
		{ Qt::Key_F8, Ntsh::InputState::None },
		{ Qt::Key_F9, Ntsh::InputState::None },
		{ Qt::Key_F10, Ntsh::InputState::None },
		{ Qt::Key_F11, Ntsh::InputState::None },
		{ Qt::Key_F12, Ntsh::InputState::None }
	};

	std::unordered_map<Ntsh::InputMouseButton, Qt::MouseButton> m_mouseButtonMap = { { Ntsh::InputMouseButton::One, Qt::LeftButton },
		{ Ntsh::InputMouseButton::Two, Qt::RightButton },
		{ Ntsh::InputMouseButton::Three, Qt::MiddleButton },
		{ Ntsh::InputMouseButton::Four, Qt::ExtraButton1 },
		{ Ntsh::InputMouseButton::Five, Qt::ExtraButton2 },
		{ Ntsh::InputMouseButton::Six, Qt::ExtraButton3 },
		{ Ntsh::InputMouseButton::Seven, Qt::ExtraButton4 },
		{ Ntsh::InputMouseButton::Eight, Qt::ExtraButton5 },
	};
	std::unordered_map<Qt::MouseButton, Ntsh::InputState> m_mouseButtonStateMap = { { Qt::LeftButton, Ntsh::InputState::None },
		{ Qt::RightButton, Ntsh::InputState::None },
		{ Qt::MiddleButton, Ntsh::InputState::None },
		{ Qt::ExtraButton1, Ntsh::InputState::None },
		{ Qt::ExtraButton2, Ntsh::InputState::None },
		{ Qt::ExtraButton3, Ntsh::InputState::None },
		{ Qt::ExtraButton4, Ntsh::InputState::None },
		{ Qt::ExtraButton5, Ntsh::InputState::None },
	};
};