#include "ntshengn_window_module.h"
#include "../Module/utils/ntshengn_module_defines.h"
#include "../Module/utils/ntshengn_dynamic_library.h"
#include "../Common/utils/ntshengn_defines.h"
#include "../Common/utils/ntshengn_enums.h"
#include "../Common/resources/ntshengn_resources_graphics.h"
#include <algorithm>

void NtshEngn::WindowModule::init() {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void NtshEngn::WindowModule::update(double dt) {
	NTSHENGN_UNUSED(dt);

	for (auto it = m_windows.begin(); it != m_windows.end(); ) {
		if (it->second->shouldClose()) {
			it = m_windows.erase(it);
		}
		else {
			it->second->update();
			it++;
		}
	}

	pollEvents();

	for (uint8_t i = GLFW_JOYSTICK_1; i < GLFW_JOYSTICK_LAST + 1; i++) {
		if (m_gamepadIDs.find(i) != m_gamepadIDs.end()) {
			if (!glfwJoystickPresent(i)) {
				m_gamepads.erase(m_gamepadIDs[i]);
				m_gamepadIDs.erase(i);
			}
		}
		else {
			if (glfwJoystickPresent(i)) {
				m_gamepads[m_gamepadID++] = std::make_unique<Gamepad>(i);
				m_gamepadIDs[i] = m_gamepadID - 1;
			}
		}
	}

	for (auto& gamepad : m_gamepads) {
		gamepad.second->update();
	}
}

void NtshEngn::WindowModule::destroy() {
	for (auto it = m_windows.begin(); it != m_windows.end(); it++) {
		it->second->close();
	}
	glfwTerminate();
}

NtshEngn::WindowID NtshEngn::WindowModule::openWindow(int width, int height, const std::string& title) {
	m_windows[m_windowID] = std::make_unique<GLFWWindow>(width, height, title);

	if (m_mainWindow == NTSHENGN_WINDOW_UNKNOWN) {
		m_mainWindow = m_windowID;
	}

	return m_windowID++;
}

bool NtshEngn::WindowModule::isWindowOpen(WindowID windowID) {
	return (m_windows.find(windowID) != m_windows.end()) ? !m_windows[windowID]->shouldClose() : false;
}

void NtshEngn::WindowModule::closeWindow(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	m_windows[windowID]->close();
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

	m_windows[windowID]->setSize(width, height);
}

int NtshEngn::WindowModule::getWindowWidth(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->getWidth();
}

int NtshEngn::WindowModule::getWindowHeight(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->getHeight();
}

void NtshEngn::WindowModule::setWindowPosition(WindowID windowID, int x, int y) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	m_windows[windowID]->setPosition(x, y);
}

int NtshEngn::WindowModule::getWindowPositionX(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->getPositionX();
}

int NtshEngn::WindowModule::getWindowPositionY(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->getPositionY();
}

void NtshEngn::WindowModule::setWindowFullscreen(WindowID windowID, bool fullscreen) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	m_windows[windowID]->setFullscreen(fullscreen);
}

bool NtshEngn::WindowModule::isWindowFullscreen(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->isFullscreen();
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
	glfwPollEvents();
}

void NtshEngn::WindowModule::setWindowTitle(WindowID windowID, const std::string& title) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	m_windows[windowID]->setTitle(title);
}

void NtshEngn::WindowModule::setWindowIcon(WindowID windowID, const Image& image) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	m_windows[windowID]->setIcon(image);
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

	return m_windows[windowID]->getCursorPositionX();
}

int NtshEngn::WindowModule::getCursorPositionY(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->getCursorPositionY();
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
	std::vector<GamepadID> gamepads;

	for (auto it = m_gamepads.begin(); it != m_gamepads.end(); it++) {
		gamepads.push_back(it->first);
	}

	return gamepads;
}

NtshEngn::InputState NtshEngn::WindowModule::getGamepadButtonState(GamepadID gamepadID, InputGamepadButton button) {
	NTSHENGN_ASSERT(m_gamepads.find(gamepadID) != m_gamepads.end());

	return m_gamepads[gamepadID]->getGamepadButtonState(button);
}

float NtshEngn::WindowModule::getGamepadStickAxisX(GamepadID gamepadID, InputGamepadStick stick) {
	NTSHENGN_ASSERT(m_gamepads.find(gamepadID) != m_gamepads.end());

	return m_gamepads[gamepadID]->getGamepadStickAxisX(stick);
}

float NtshEngn::WindowModule::getGamepadStickAxisY(GamepadID gamepadID, InputGamepadStick stick) {
	NTSHENGN_ASSERT(m_gamepads.find(gamepadID) != m_gamepads.end());

	return m_gamepads[gamepadID]->getGamepadStickAxisY(stick);
}

float NtshEngn::WindowModule::getGamepadLeftTrigger(GamepadID gamepadID) {
	NTSHENGN_ASSERT(m_gamepads.find(gamepadID) != m_gamepads.end());

	return m_gamepads[gamepadID]->getGamepadLeftTrigger();
}

float NtshEngn::WindowModule::getGamepadRightTrigger(GamepadID gamepadID) {
	NTSHENGN_ASSERT(m_gamepads.find(gamepadID) != m_gamepads.end());

	return m_gamepads[gamepadID]->getGamepadRightTrigger();
}

std::string NtshEngn::WindowModule::getGamepadName(GamepadID gamepadID) {
	NTSHENGN_ASSERT(m_gamepads.find(gamepadID) != m_gamepads.end());

	return m_gamepads[gamepadID]->getGamepadName();
}

int NtshEngn::WindowModule::getMonitorWidth() {
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

	return videoMode->width;
}

int NtshEngn::WindowModule::getMonitorHeight() {
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

	return videoMode->height;
}

int NtshEngn::WindowModule::getMonitorRefreshRate() {
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

	return videoMode->refreshRate;
}

float NtshEngn::WindowModule::getMonitorDisplayScaling() {
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	float scaleX;
	glfwGetMonitorContentScale(monitor, &scaleX, NULL);

	return scaleX;
}

NtshEngn::NativeWindowHandle NtshEngn::WindowModule::getWindowNativeHandle(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());

	return m_windows[windowID]->getNativeHandle();
}

NtshEngn::NativeWindowAdditionalInformation NtshEngn::WindowModule::getWindowNativeAdditionalInformation(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	
	return m_windows[windowID]->getNativeAdditionalInformation();
}

extern "C" NTSHENGN_MODULE_API NtshEngn::WindowModuleInterface* createModule() {
	return new NtshEngn::WindowModule;
}

extern "C" NTSHENGN_MODULE_API void destroyModule(NtshEngn::WindowModuleInterface* m) {
	delete m;
}