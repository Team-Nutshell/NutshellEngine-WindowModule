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

bool NtshEngn::WindowModule::isOpen(WindowId windowId) {
	return (m_windows.find(windowId) != m_windows.end()) ? !m_windows[windowId]->shouldClose() : false;
}

void NtshEngn::WindowModule::close(WindowId windowId) {
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

void NtshEngn::WindowModule::setSize(WindowId windowId, int width, int height) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setSize(width, height);
}

int NtshEngn::WindowModule::getWidth(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getWidth();
}

int NtshEngn::WindowModule::getHeight(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getHeight();
}

void NtshEngn::WindowModule::setPosition(WindowId windowId, int x, int y) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setPosition(x, y);
}

int NtshEngn::WindowModule::getPositionX(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getPositionX();
}

int NtshEngn::WindowModule::getPositionY(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getPositionY();
}

void NtshEngn::WindowModule::setFullscreen(WindowId windowId, bool fullscreen) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setFullscreen(fullscreen);
}

bool NtshEngn::WindowModule::isFullscreen(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isFullscreen();
}

void NtshEngn::WindowModule::setBorderless(WindowId windowId, bool borderless) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setBorderless(borderless);
}

bool NtshEngn::WindowModule::isBorderless(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isBorderless();
}

void NtshEngn::WindowModule::setResizable(WindowId windowId, bool resizable) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setResizable(resizable);
}

bool NtshEngn::WindowModule::isResizable(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isResizable();
}

void NtshEngn::WindowModule::pollEvents() {
	glfwPollEvents();
}

void NtshEngn::WindowModule::setTitle(WindowId windowId, const std::string& title) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setTitle(title);
}

NtshEngn::InputState NtshEngn::WindowModule::getKeyState(WindowId windowId, InputKeyboardKey key) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getKeyState(key);
}

NtshEngn::InputState NtshEngn::WindowModule::getMouseButtonState(WindowId windowId, InputMouseButton mouseButton) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getMouseButtonState(mouseButton);
}

void NtshEngn::WindowModule::setCursorPosition(WindowId windowId, int x, int y) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setCursorPosition(x, y);
}

int NtshEngn::WindowModule::getCursorPositionX(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getCursorPositionX();
}

int NtshEngn::WindowModule::getCursorPositionY(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getCursorPositionY();
}

void NtshEngn::WindowModule::setCursorVisibility(WindowId windowId, bool visible) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	m_windows[windowId]->setCursorVisibility(visible);
}

bool NtshEngn::WindowModule::isCursorVisible(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->isCursorVisible();
}

NtshEngn::NativeWindowHandle NtshEngn::WindowModule::getNativeHandle(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getNativeHandle();
}

NtshEngn::NativeWindowAdditionalInformation NtshEngn::WindowModule::getNativeAdditionalInformation(WindowId windowId) {
	NTSHENGN_ASSERT(m_windows.find(windowId) != m_windows.end());
	return m_windows[windowId]->getNativeAdditionalInformation();
}

extern "C" NTSHENGN_MODULE_API NtshEngn::WindowModuleInterface* createModule() {
	return new NtshEngn::WindowModule;
}

extern "C" NTSHENGN_MODULE_API void destroyModule(NtshEngn::WindowModuleInterface* m) {
	delete m;
}