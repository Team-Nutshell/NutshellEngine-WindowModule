#pragma once
#include "../external/glfw/include/GLFW/glfw3.h"
#include "../Common/utils/ntshengn_defines.h"
#include "../Common/resources/ntshengn_resources_window.h"
#include <unordered_map>
#include <string>

class Gamepad {
public:
	Gamepad(int id);

	void update();

	NtshEngn::InputState getGamepadButtonState(NtshEngn::InputGamepadButton button);
	float getGamepadStickAxisX(NtshEngn::InputGamepadStick stick);
	float getGamepadStickAxisY(NtshEngn::InputGamepadStick stick);
	float getGamepadLeftTrigger();
	float getGamepadRightTrigger();

	std::string getGamepadName();

private:
	int m_id;

	GLFWgamepadstate m_currentState;

	std::unordered_map<NtshEngn::InputGamepadButton, int> m_gamepadButtonMap = { { NtshEngn::InputGamepadButton::Any, GLFW_GAMEPAD_BUTTON_LAST + 1 },
		{ NtshEngn::InputGamepadButton::Face1, GLFW_GAMEPAD_BUTTON_A },
		{ NtshEngn::InputGamepadButton::Face2, GLFW_GAMEPAD_BUTTON_B },
		{ NtshEngn::InputGamepadButton::Face3, GLFW_GAMEPAD_BUTTON_X },
		{ NtshEngn::InputGamepadButton::Face4, GLFW_GAMEPAD_BUTTON_Y },
		{ NtshEngn::InputGamepadButton::Start, GLFW_GAMEPAD_BUTTON_START },
		{ NtshEngn::InputGamepadButton::Select, GLFW_GAMEPAD_BUTTON_BACK },
		{ NtshEngn::InputGamepadButton::Guide, GLFW_GAMEPAD_BUTTON_GUIDE },
		{ NtshEngn::InputGamepadButton::LeftStick, GLFW_GAMEPAD_BUTTON_LEFT_THUMB },
		{ NtshEngn::InputGamepadButton::RightStick, GLFW_GAMEPAD_BUTTON_RIGHT_THUMB },
		{ NtshEngn::InputGamepadButton::LeftBumper, GLFW_GAMEPAD_BUTTON_LEFT_BUMPER },
		{ NtshEngn::InputGamepadButton::RightBumper, GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER },
		{ NtshEngn::InputGamepadButton::DPadLeft, GLFW_GAMEPAD_BUTTON_DPAD_LEFT },
		{ NtshEngn::InputGamepadButton::DPadRight, GLFW_GAMEPAD_BUTTON_DPAD_RIGHT },
		{ NtshEngn::InputGamepadButton::DPadUp, GLFW_GAMEPAD_BUTTON_DPAD_UP },
		{ NtshEngn::InputGamepadButton::DPadDown, GLFW_GAMEPAD_BUTTON_DPAD_DOWN }
	};
	std::unordered_map<int, NtshEngn::InputState> m_gamepadButtonStateMap = { { GLFW_GAMEPAD_BUTTON_LAST + 1, NtshEngn::InputState::None },
		{ GLFW_GAMEPAD_BUTTON_A, NtshEngn::InputState::None },
		{ GLFW_GAMEPAD_BUTTON_B, NtshEngn::InputState::None },
		{ GLFW_GAMEPAD_BUTTON_X, NtshEngn::InputState::None },
		{ GLFW_GAMEPAD_BUTTON_Y, NtshEngn::InputState::None },
		{ GLFW_GAMEPAD_BUTTON_START, NtshEngn::InputState::None },
		{ GLFW_GAMEPAD_BUTTON_BACK, NtshEngn::InputState::None },
		{ GLFW_GAMEPAD_BUTTON_GUIDE, NtshEngn::InputState::None },
		{ GLFW_GAMEPAD_BUTTON_LEFT_THUMB, NtshEngn::InputState::None },
		{ GLFW_GAMEPAD_BUTTON_RIGHT_THUMB, NtshEngn::InputState::None },
		{ GLFW_GAMEPAD_BUTTON_LEFT_BUMPER, NtshEngn::InputState::None },
		{ GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER, NtshEngn::InputState::None },
		{ GLFW_GAMEPAD_BUTTON_DPAD_LEFT, NtshEngn::InputState::None },
		{ GLFW_GAMEPAD_BUTTON_DPAD_RIGHT, NtshEngn::InputState::None },
		{ GLFW_GAMEPAD_BUTTON_DPAD_UP, NtshEngn::InputState::None },
		{ GLFW_GAMEPAD_BUTTON_DPAD_DOWN, NtshEngn::InputState::None }
	};

	std::string m_name;
};