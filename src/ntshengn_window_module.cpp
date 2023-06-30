#include "ntshengn_window_module.h"
#include "../external/Module/utils/ntshengn_module_defines.h"
#include "../external/Module/utils/ntshengn_dynamic_library.h"
#include "../external/Common/utils/ntshengn_defines.h"
#include "../external/Common/utils/ntshengn_enums.h"

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

bool NtshEngn::WindowModule::isOpen(WindowID windowId) {
	return (m_windows.find(windowId) != m_windows.end()) ? !m_windows[windowId]->shouldClose() : false;
}

void NtshEngn::WindowModule::close(WindowID windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->close();
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

void NtshEngn::WindowModule::setSize(WindowID windowId, int width, int height) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setSize(width, height);
}

int NtshEngn::WindowModule::getWidth(WindowID windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getWidth();
}

int NtshEngn::WindowModule::getHeight(WindowID windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getHeight();
}

void NtshEngn::WindowModule::setPosition(WindowID windowId, int x, int y) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setPosition(x, y);
}

int NtshEngn::WindowModule::getPositionX(WindowID windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getPositionX();
}

int NtshEngn::WindowModule::getPositionY(WindowID windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getPositionY();
}

void NtshEngn::WindowModule::setFullscreen(WindowID windowId, bool fullscreen) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setFullscreen(fullscreen);
}

bool NtshEngn::WindowModule::isFullscreen(WindowID windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isFullscreen();
}

void NtshEngn::WindowModule::setBorderless(WindowID windowId, bool borderless) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setBorderless(borderless);
}

bool NtshEngn::WindowModule::isBorderless(WindowID windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isBorderless();
}

void NtshEngn::WindowModule::setResizable(WindowID windowId, bool resizable) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setResizable(resizable);
}

bool NtshEngn::WindowModule::isResizable(WindowID windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isResizable();
}

void NtshEngn::WindowModule::pollEvents() {
	glfwPollEvents();
}

void NtshEngn::WindowModule::setTitle(WindowID windowId, const std::string& title) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setTitle(title);
}

NtshEngn::InputState NtshEngn::WindowModule::getKeyState(WindowID windowId, InputKeyboardKey key) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getKeyState(key);
}

NtshEngn::InputState NtshEngn::WindowModule::getMouseButtonState(WindowID windowId, InputMouseButton mouseButton) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getMouseButtonState(mouseButton);
}

void NtshEngn::WindowModule::setCursorPosition(WindowID windowId, int x, int y) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setCursorPosition(x, y);
}

int NtshEngn::WindowModule::getCursorPositionX(WindowID windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getCursorPositionX();
}

int NtshEngn::WindowModule::getCursorPositionY(WindowID windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getCursorPositionY();
}

void NtshEngn::WindowModule::setCursorVisibility(WindowID windowId, bool visible) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setCursorVisibility(visible);
}

bool NtshEngn::WindowModule::isCursorVisible(WindowID windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isCursorVisible();
}

NtshEngn::NativeWindowHandle NtshEngn::WindowModule::getNativeHandle(WindowID windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getNativeHandle();
}

NtshEngn::NativeWindowAdditionalInformation NtshEngn::WindowModule::getNativeAdditionalInformation(WindowID windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getNativeAdditionalInformation();
}

extern "C" NTSHENGN_MODULE_API NtshEngn::WindowModuleInterface* createModule() {
	return new NtshEngn::WindowModule;
}

extern "C" NTSHENGN_MODULE_API void destroyModule(NtshEngn::WindowModuleInterface* m) {
	delete m;
}