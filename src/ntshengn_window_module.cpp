#include "ntshengn_window_module.h"
#include "../Module/utils/ntshengn_module_defines.h"
#include "../Module/utils/ntshengn_dynamic_library.h"
#include "../Common/utils/ntshengn_defines.h"
#include "../Common/utils/ntshengn_enums.h"
#include "../Common/resources/ntshengn_resources_graphics.h"

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
			it->second->updateInputs(dt);
			it++;
		}
	}

	pollEvents();
}

void NtshEngn::WindowModule::destroy() {
	for (auto it = m_windows.begin(); it != m_windows.end(); it++) {
		it->second->close();
	}
	glfwTerminate();
}

NtshEngn::WindowID NtshEngn::WindowModule::open(int width, int height, const std::string& title) {
	m_windows[m_id] = std::make_unique<GLFWWindow>(width, height, title);

	if (m_mainWindow == std::numeric_limits<WindowID>::max()) {
		m_mainWindow = m_id;
	}

	return m_id++;
}

bool NtshEngn::WindowModule::isOpen(WindowID windowID) {
	return (m_windows.find(windowID) != m_windows.end()) ? !m_windows[windowID]->shouldClose() : false;
}

void NtshEngn::WindowModule::close(WindowID windowID) {
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

void NtshEngn::WindowModule::setSize(WindowID windowID, int width, int height) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	m_windows[windowID]->setSize(width, height);
}

int NtshEngn::WindowModule::getWidth(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	return m_windows[windowID]->getWidth();
}

int NtshEngn::WindowModule::getHeight(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	return m_windows[windowID]->getHeight();
}

void NtshEngn::WindowModule::setPosition(WindowID windowID, int x, int y) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	m_windows[windowID]->setPosition(x, y);
}

int NtshEngn::WindowModule::getPositionX(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	return m_windows[windowID]->getPositionX();
}

int NtshEngn::WindowModule::getPositionY(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	return m_windows[windowID]->getPositionY();
}

void NtshEngn::WindowModule::setFullscreen(WindowID windowID, bool fullscreen) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	m_windows[windowID]->setFullscreen(fullscreen);
}

bool NtshEngn::WindowModule::isFullscreen(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	return m_windows[windowID]->isFullscreen();
}

void NtshEngn::WindowModule::setBorderless(WindowID windowID, bool borderless) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	m_windows[windowID]->setBorderless(borderless);
}

bool NtshEngn::WindowModule::isBorderless(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	return m_windows[windowID]->isBorderless();
}

void NtshEngn::WindowModule::setResizable(WindowID windowID, bool resizable) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	m_windows[windowID]->setResizable(resizable);
}

bool NtshEngn::WindowModule::isResizable(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	return m_windows[windowID]->isResizable();
}

void NtshEngn::WindowModule::pollEvents() {
	glfwPollEvents();
}

void NtshEngn::WindowModule::setTitle(WindowID windowID, const std::string& title) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	m_windows[windowID]->setTitle(title);
}

void NtshEngn::WindowModule::setIcon(WindowID windowID, const Image& image) {
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

void NtshEngn::WindowModule::setCursorVisibility(WindowID windowID, bool visible) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	m_windows[windowID]->setCursorVisibility(visible);
}

bool NtshEngn::WindowModule::isCursorVisible(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	return m_windows[windowID]->isCursorVisible();
}

NtshEngn::NativeWindowHandle NtshEngn::WindowModule::getNativeHandle(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	return m_windows[windowID]->getNativeHandle();
}

NtshEngn::NativeWindowAdditionalInformation NtshEngn::WindowModule::getNativeAdditionalInformation(WindowID windowID) {
	NTSHENGN_ASSERT(m_windows.find(windowID) != m_windows.end());
	return m_windows[windowID]->getNativeAdditionalInformation();
}

extern "C" NTSHENGN_MODULE_API NtshEngn::WindowModuleInterface* createModule() {
	return new NtshEngn::WindowModule;
}

extern "C" NTSHENGN_MODULE_API void destroyModule(NtshEngn::WindowModuleInterface* m) {
	delete m;
}