#pragma once
#include "qwidget.h"
#include "../external/Common/resources/ntshengn_resources_window.h"
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

	void setBorderless(bool borderless);
	bool isBorderless();

	void setResizable(bool resizable);
	bool isResizable();

	NtshEngn::InputState getKeyState(NtshEngn::InputKeyboardKey key);
	NtshEngn::InputState getMouseButtonState(NtshEngn::InputMouseButton mouseButton);

	void setCursorPosition(int x, int y);
	int getCursorXPosition();
	int getCursorYPosition();

	void setCursorVisibility(bool visible);
	bool isCursorVisible();

private:
	NtshEngn::InputState nextInputState(NtshEngn::InputState inputState);

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
	
	std::unordered_map<NtshEngn::InputKeyboardKey, Qt::Key> m_keyMap = { { NtshEngn::InputKeyboardKey::Any, Qt::Key_unknown },
		{ NtshEngn::InputKeyboardKey::A, Qt::Key_A },
		{ NtshEngn::InputKeyboardKey::B, Qt::Key_B },
		{ NtshEngn::InputKeyboardKey::C, Qt::Key_C },
		{ NtshEngn::InputKeyboardKey::D, Qt::Key_D },
		{ NtshEngn::InputKeyboardKey::E, Qt::Key_E },
		{ NtshEngn::InputKeyboardKey::F, Qt::Key_F },
		{ NtshEngn::InputKeyboardKey::G, Qt::Key_G },
		{ NtshEngn::InputKeyboardKey::H, Qt::Key_H },
		{ NtshEngn::InputKeyboardKey::I, Qt::Key_I },
		{ NtshEngn::InputKeyboardKey::J, Qt::Key_J },
		{ NtshEngn::InputKeyboardKey::K, Qt::Key_K },
		{ NtshEngn::InputKeyboardKey::L, Qt::Key_L },
		{ NtshEngn::InputKeyboardKey::M, Qt::Key_M },
		{ NtshEngn::InputKeyboardKey::N, Qt::Key_N },
		{ NtshEngn::InputKeyboardKey::O, Qt::Key_O },
		{ NtshEngn::InputKeyboardKey::P, Qt::Key_P },
		{ NtshEngn::InputKeyboardKey::Q, Qt::Key_Q },
		{ NtshEngn::InputKeyboardKey::R, Qt::Key_R },
		{ NtshEngn::InputKeyboardKey::S, Qt::Key_S },
		{ NtshEngn::InputKeyboardKey::T, Qt::Key_T },
		{ NtshEngn::InputKeyboardKey::U, Qt::Key_U },
		{ NtshEngn::InputKeyboardKey::V, Qt::Key_V },
		{ NtshEngn::InputKeyboardKey::W, Qt::Key_W },
		{ NtshEngn::InputKeyboardKey::X, Qt::Key_X },
		{ NtshEngn::InputKeyboardKey::Y, Qt::Key_Y },
		{ NtshEngn::InputKeyboardKey::Z, Qt::Key_Z },
		{ NtshEngn::InputKeyboardKey::Space, Qt::Key_Space },
		{ NtshEngn::InputKeyboardKey::Shift, Qt::Key_Shift },
		{ NtshEngn::InputKeyboardKey::LeftCtrl, Qt::Key_Control },
		{ NtshEngn::InputKeyboardKey::RightCtrl, Qt::Key_Control },
		{ NtshEngn::InputKeyboardKey::Alt, Qt::Key_Alt },
		{ NtshEngn::InputKeyboardKey::Escape, Qt::Key_Escape },
		{ NtshEngn::InputKeyboardKey::Tab, Qt::Key_Tab },
		{ NtshEngn::InputKeyboardKey::Backspace, Qt::Key_Backspace },
		{ NtshEngn::InputKeyboardKey::Return, Qt::Key_Return },
		{ NtshEngn::InputKeyboardKey::Enter, Qt::Key_Enter },
		{ NtshEngn::InputKeyboardKey::Num0, Qt::Key_0 },
		{ NtshEngn::InputKeyboardKey::Num1, Qt::Key_1 },
		{ NtshEngn::InputKeyboardKey::Num2, Qt::Key_2 },
		{ NtshEngn::InputKeyboardKey::Num3, Qt::Key_3 },
		{ NtshEngn::InputKeyboardKey::Num4, Qt::Key_4 },
		{ NtshEngn::InputKeyboardKey::Num5, Qt::Key_5 },
		{ NtshEngn::InputKeyboardKey::Num6, Qt::Key_6 },
		{ NtshEngn::InputKeyboardKey::Num7, Qt::Key_7 },
		{ NtshEngn::InputKeyboardKey::Num8, Qt::Key_8 },
		{ NtshEngn::InputKeyboardKey::Num9, Qt::Key_9 },
		{ NtshEngn::InputKeyboardKey::NumPlus, Qt::Key_Plus },
		{ NtshEngn::InputKeyboardKey::NumMinus, Qt::Key_Minus },
		{ NtshEngn::InputKeyboardKey::NumTimes, Qt::Key_Asterisk },
		{ NtshEngn::InputKeyboardKey::NumDivision, Qt::Key_Slash },
		{ NtshEngn::InputKeyboardKey::Left, Qt::Key_Left },
		{ NtshEngn::InputKeyboardKey::Right, Qt::Key_Right },
		{ NtshEngn::InputKeyboardKey::Up, Qt::Key_Up },
		{ NtshEngn::InputKeyboardKey::Down, Qt::Key_Down },
		{ NtshEngn::InputKeyboardKey::F1, Qt::Key_F1 },
		{ NtshEngn::InputKeyboardKey::F2, Qt::Key_F2 },
		{ NtshEngn::InputKeyboardKey::F3, Qt::Key_F3 },
		{ NtshEngn::InputKeyboardKey::F4, Qt::Key_F4 },
		{ NtshEngn::InputKeyboardKey::F5, Qt::Key_F5 },
		{ NtshEngn::InputKeyboardKey::F6, Qt::Key_F6 },
		{ NtshEngn::InputKeyboardKey::F7, Qt::Key_F7 },
		{ NtshEngn::InputKeyboardKey::F8, Qt::Key_F8 },
		{ NtshEngn::InputKeyboardKey::F9, Qt::Key_F9 },
		{ NtshEngn::InputKeyboardKey::F10, Qt::Key_F10 },
		{ NtshEngn::InputKeyboardKey::F11, Qt::Key_F11 },
		{ NtshEngn::InputKeyboardKey::F12, Qt::Key_F12 }
	};
	std::unordered_map<Qt::Key, NtshEngn::InputState> m_keyStateMap = { { Qt::Key_unknown, NtshEngn::InputState::None },
		{ Qt::Key_A, NtshEngn::InputState::None },
		{ Qt::Key_B, NtshEngn::InputState::None },
		{ Qt::Key_C, NtshEngn::InputState::None },
		{ Qt::Key_D, NtshEngn::InputState::None },
		{ Qt::Key_E, NtshEngn::InputState::None },
		{ Qt::Key_F, NtshEngn::InputState::None },
		{ Qt::Key_G, NtshEngn::InputState::None },
		{ Qt::Key_H, NtshEngn::InputState::None },
		{ Qt::Key_I, NtshEngn::InputState::None },
		{ Qt::Key_J, NtshEngn::InputState::None },
		{ Qt::Key_K, NtshEngn::InputState::None },
		{ Qt::Key_L, NtshEngn::InputState::None },
		{ Qt::Key_M, NtshEngn::InputState::None },
		{ Qt::Key_N, NtshEngn::InputState::None },
		{ Qt::Key_O, NtshEngn::InputState::None },
		{ Qt::Key_P, NtshEngn::InputState::None },
		{ Qt::Key_Q, NtshEngn::InputState::None },
		{ Qt::Key_R, NtshEngn::InputState::None },
		{ Qt::Key_S, NtshEngn::InputState::None },
		{ Qt::Key_T, NtshEngn::InputState::None },
		{ Qt::Key_U, NtshEngn::InputState::None },
		{ Qt::Key_V, NtshEngn::InputState::None },
		{ Qt::Key_W, NtshEngn::InputState::None },
		{ Qt::Key_X, NtshEngn::InputState::None },
		{ Qt::Key_Y, NtshEngn::InputState::None },
		{ Qt::Key_Z, NtshEngn::InputState::None },
		{ Qt::Key_Space, NtshEngn::InputState::None },
		{ Qt::Key_Shift, NtshEngn::InputState::None },
		{ Qt::Key_Control, NtshEngn::InputState::None },
		{ Qt::Key_Alt, NtshEngn::InputState::None },
		{ Qt::Key_Escape, NtshEngn::InputState::None },
		{ Qt::Key_Tab, NtshEngn::InputState::None },
		{ Qt::Key_Backspace, NtshEngn::InputState::None },
		{ Qt::Key_Enter, NtshEngn::InputState::None },
		{ Qt::Key_Return, NtshEngn::InputState::None },
		{ Qt::Key_0, NtshEngn::InputState::None },
		{ Qt::Key_1, NtshEngn::InputState::None },
		{ Qt::Key_2, NtshEngn::InputState::None },
		{ Qt::Key_3, NtshEngn::InputState::None },
		{ Qt::Key_4, NtshEngn::InputState::None },
		{ Qt::Key_5, NtshEngn::InputState::None },
		{ Qt::Key_6, NtshEngn::InputState::None },
		{ Qt::Key_7, NtshEngn::InputState::None },
		{ Qt::Key_8, NtshEngn::InputState::None },
		{ Qt::Key_9, NtshEngn::InputState::None },
		{ Qt::Key_Plus, NtshEngn::InputState::None },
		{ Qt::Key_Minus, NtshEngn::InputState::None },
		{ Qt::Key_Asterisk, NtshEngn::InputState::None },
		{ Qt::Key_Slash, NtshEngn::InputState::None },
		{ Qt::Key_Left, NtshEngn::InputState::None },
		{ Qt::Key_Right, NtshEngn::InputState::None },
		{ Qt::Key_Up, NtshEngn::InputState::None },
		{ Qt::Key_Down, NtshEngn::InputState::None },
		{ Qt::Key_F1, NtshEngn::InputState::None },
		{ Qt::Key_F2, NtshEngn::InputState::None },
		{ Qt::Key_F3, NtshEngn::InputState::None },
		{ Qt::Key_F4, NtshEngn::InputState::None },
		{ Qt::Key_F5, NtshEngn::InputState::None },
		{ Qt::Key_F6, NtshEngn::InputState::None },
		{ Qt::Key_F7, NtshEngn::InputState::None },
		{ Qt::Key_F8, NtshEngn::InputState::None },
		{ Qt::Key_F9, NtshEngn::InputState::None },
		{ Qt::Key_F10, NtshEngn::InputState::None },
		{ Qt::Key_F11, NtshEngn::InputState::None },
		{ Qt::Key_F12, NtshEngn::InputState::None }
	};

	std::unordered_map<NtshEngn::InputMouseButton, Qt::MouseButton> m_mouseButtonMap = { { NtshEngn::InputMouseButton::Any, Qt::MouseButtonMask },
		{ NtshEngn::InputMouseButton::One, Qt::LeftButton },
		{ NtshEngn::InputMouseButton::Two, Qt::RightButton },
		{ NtshEngn::InputMouseButton::Three, Qt::MiddleButton },
		{ NtshEngn::InputMouseButton::Four, Qt::ExtraButton1 },
		{ NtshEngn::InputMouseButton::Five, Qt::ExtraButton2 },
		{ NtshEngn::InputMouseButton::Six, Qt::ExtraButton3 },
		{ NtshEngn::InputMouseButton::Seven, Qt::ExtraButton4 },
		{ NtshEngn::InputMouseButton::Eight, Qt::ExtraButton5 },
	};
	std::unordered_map<Qt::MouseButton, NtshEngn::InputState> m_mouseButtonStateMap = { { Qt::MouseButtonMask, NtshEngn::InputState::None },
		{ Qt::LeftButton, NtshEngn::InputState::None },
		{ Qt::RightButton, NtshEngn::InputState::None },
		{ Qt::MiddleButton, NtshEngn::InputState::None },
		{ Qt::ExtraButton1, NtshEngn::InputState::None },
		{ Qt::ExtraButton2, NtshEngn::InputState::None },
		{ Qt::ExtraButton3, NtshEngn::InputState::None },
		{ Qt::ExtraButton4, NtshEngn::InputState::None },
		{ Qt::ExtraButton5, NtshEngn::InputState::None },
	};
};