#include "gamepad.h"
#include "../Common/utils/ntshengn_defines.h"

Gamepad::Gamepad(int id) : m_id(id) {
	const char* gamepadName = glfwGetGamepadName(id);
	if (gamepadName) {
		m_name = std::string(gamepadName);
	}
	else {
		m_name = "Unknown Gamepad";
	}
}

void Gamepad::updateInputs(double dt) {
	NTSHENGN_UNUSED(dt);

	glfwGetGamepadState(m_id, &m_currentState);

	for (auto& button : m_gamepadButtonStateMap) {
		if (button.first == GLFW_GAMEPAD_BUTTON_LAST + 1) {
			continue;
		}

		if (m_currentState.buttons[button.first] == GLFW_PRESS) {
			if ((button.second == NtshEngn::InputState::None) || (button.second == NtshEngn::InputState::Released)) {
				button.second = NtshEngn::InputState::Pressed;
				m_gamepadButtonStateMap[GLFW_GAMEPAD_BUTTON_LAST + 1] = NtshEngn::InputState::Pressed; // Any
			}
			else if (button.second == NtshEngn::InputState::Pressed) {
				button.second = NtshEngn::InputState::Held;
			}
		}
		else if (m_currentState.buttons[button.first] == GLFW_RELEASE) {
			if ((button.second == NtshEngn::InputState::Pressed) || (button.second == NtshEngn::InputState::Held)) {
				button.second = NtshEngn::InputState::Released;
				m_gamepadButtonStateMap[GLFW_GAMEPAD_BUTTON_LAST + 1] = NtshEngn::InputState::Released; // Any
			}
			else if (button.second == NtshEngn::InputState::Released) {
				button.second = NtshEngn::InputState::None;
			}
		}
	}
}

NtshEngn::InputState Gamepad::getGamepadButtonState(NtshEngn::InputGamepadButton button) {
	return m_gamepadButtonStateMap[m_gamepadButtonMap[button]];
}

float Gamepad::getGamepadStickAxisX(NtshEngn::InputGamepadStick stick) {
	if (stick == NtshEngn::InputGamepadStick::Left) {
		return m_currentState.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
	}
	else if (stick == NtshEngn::InputGamepadStick::Right) {
		return m_currentState.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
	}

	return 0.0f;
}

float Gamepad::getGamepadStickAxisY(NtshEngn::InputGamepadStick stick) {
	if (stick == NtshEngn::InputGamepadStick::Left) {
		return m_currentState.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
	}
	else if (stick == NtshEngn::InputGamepadStick::Right) {
		return m_currentState.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];
	}

	return 0.0f;
}

float Gamepad::getGamepadLeftTrigger() {
	return (m_currentState.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER] + 1.0f) / 2.0f;
}

float Gamepad::getGamepadRightTrigger() {
	return (m_currentState.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] + 1.0f) / 2.0f;
}

std::string Gamepad::getGamepadName() {
	return m_name;
}
