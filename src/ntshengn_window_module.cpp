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

NtshEngn::WindowId NtshEngn::WindowModule::open(int width, int height, const std::string& title) {
	m_windows[m_id] = std::make_unique<GLFWWindow>(width, height, title);

	return m_id++;
}

bool NtshEngn::WindowModule::isOpen(NtshEngn::WindowId windowId) {
	return (m_windows.find(windowId) != m_windows.end()) ? !m_windows[windowId]->shouldClose() : false;
}

void NtshEngn::WindowModule::close(NtshEngn::WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->close();
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

void NtshEngn::WindowModule::setSize(NtshEngn::WindowId windowId, int width, int height) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setSize(width, height);
}

int NtshEngn::WindowModule::getWidth(NtshEngn::WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getWidth();
}

int NtshEngn::WindowModule::getHeight(NtshEngn::WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getHeight();
}

void NtshEngn::WindowModule::setPosition(NtshEngn::WindowId windowId, int x, int y) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setPosition(x, y);
}

int NtshEngn::WindowModule::getPositionX(NtshEngn::WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getPositionX();
}

int NtshEngn::WindowModule::getPositionY(NtshEngn::WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getPositionY();
}

void NtshEngn::WindowModule::setFullscreen(NtshEngn::WindowId windowId, bool fullscreen) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setFullscreen(fullscreen);
}

bool NtshEngn::WindowModule::isFullscreen(NtshEngn::WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isFullscreen();
}

void NtshEngn::WindowModule::pollEvents() {
	glfwPollEvents();
}

void NtshEngn::WindowModule::setTitle(NtshEngn::WindowId windowId, const std::string& title) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setTitle(title);
}

NtshEngn::InputState NtshEngn::WindowModule::getKeyState(NtshEngn::WindowId windowId, NtshEngn::InputKeyboardKey key) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getKeyState(key);
}

NtshEngn::InputState NtshEngn::WindowModule::getMouseButtonState(NtshEngn::WindowId windowId, NtshEngn::InputMouseButton mouseButton) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getMouseButtonState(mouseButton);
}

void NtshEngn::WindowModule::setCursorPosition(NtshEngn::WindowId windowId, int x, int y) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setCursorPosition(x, y);
}

int NtshEngn::WindowModule::getCursorPositionX(NtshEngn::WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getCursorPositionX();
}

int NtshEngn::WindowModule::getCursorPositionY(NtshEngn::WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getCursorPositionY();
}

void NtshEngn::WindowModule::setCursorVisibility(NtshEngn::WindowId windowId, bool visible) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setCursorVisibility(visible);
}

bool NtshEngn::WindowModule::isCursorVisible(NtshEngn::WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isCursorVisible();
}

NtshEngn::NativeWindowHandle NtshEngn::WindowModule::getNativeHandle(NtshEngn::WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getNativeHandle();
}

NtshEngn::NativeWindowAdditionalInformation NtshEngn::WindowModule::getNativeAdditionalInformation(NtshEngn::WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getNativeAdditionalInformation();
}

extern "C" NTSHENGN_MODULE_API NtshEngn::WindowModuleInterface* createModule() {
	return new NtshEngn::WindowModule;
}

extern "C" NTSHENGN_MODULE_API void destroyModule(NtshEngn::WindowModuleInterface* m) {
	delete m;
}