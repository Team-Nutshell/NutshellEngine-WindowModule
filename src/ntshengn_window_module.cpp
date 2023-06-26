#include "ntshengn_window_module.h"
#include "../external/Module/utils/ntshengn_module_defines.h"
#include "../external/Module/utils/ntshengn_dynamic_library.h"
#include "../external/Common/utils/ntshengn_defines.h"
#include "../external/Common/utils/ntshengn_enums.h"
#include <limits>

void NtshEngn::WindowModule::init() {
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::WindowModule::update(double dt) {
	NTSHENGN_UNUSED(dt);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::WindowModule::destroy() {
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

NtshEngn::WindowId NtshEngn::WindowModule::open(int width, int height, const std::string& title) {
	NTSHENGN_UNUSED(width);
	NTSHENGN_UNUSED(height);
	NTSHENGN_UNUSED(title);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return std::numeric_limits<WindowId>::max();
}

bool NtshEngn::WindowModule::isOpen(WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return false;
}

void NtshEngn::WindowModule::close(WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

uint64_t NtshEngn::WindowModule::windowCount() {
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return 0;
}

void NtshEngn::WindowModule::setSize(WindowId windowId, int width, int height) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(width);
	NTSHENGN_UNUSED(height);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

int NtshEngn::WindowModule::getWidth(WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return 0;
}

int NtshEngn::WindowModule::getHeight(WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return 0;
}

void NtshEngn::WindowModule::setPosition(WindowId windowId, int x, int y) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(x);
	NTSHENGN_UNUSED(y);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

int NtshEngn::WindowModule::getPositionX(WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return -1;
}

int NtshEngn::WindowModule::getPositionY(WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return -1;
}

void NtshEngn::WindowModule::setFullscreen(WindowId windowId, bool fullscreen) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(fullscreen);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NtshEngn::WindowModule::isFullscreen(WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return false;
}

void NtshEngn::WindowModule::setBorderless(WindowId windowId, bool borderless) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(borderless);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NtshEngn::WindowModule::isBorderless(WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return false;
}

void NtshEngn::WindowModule::setResizable(WindowId windowId, bool resizable) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(resizable);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NtshEngn::WindowModule::isResizable(WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return false;
}

void NtshEngn::WindowModule::pollEvents() {
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::WindowModule::setTitle(WindowId windowId, const std::string& title) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(title);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

NtshEngn::InputState NtshEngn::WindowModule::getKeyState(WindowId windowId, InputKeyboardKey key) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(key);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return InputState::None;
}

NtshEngn::InputState NtshEngn::WindowModule::getMouseButtonState(WindowId windowId, InputMouseButton mouseButton) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(mouseButton);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return InputState::None;
}

void NtshEngn::WindowModule::setCursorPosition(WindowId windowId, int x, int y) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(x);
	NTSHENGN_UNUSED(y);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

int NtshEngn::WindowModule::getCursorPositionX(WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return -1;
}

int NtshEngn::WindowModule::getCursorPositionY(WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return -1;
}

void NtshEngn::WindowModule::setCursorVisibility(WindowId windowId, bool visible) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(visible);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NtshEngn::WindowModule::isCursorVisible(WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return false;
}

NtshEngn::NativeWindowHandle NtshEngn::WindowModule::getNativeHandle(WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return nullptr;
}

NtshEngn::NativeWindowAdditionalInformation NtshEngn::WindowModule::getNativeAdditionalInformation(WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return nullptr;
}

extern "C" NTSHENGN_MODULE_API NtshEngn::WindowModuleInterface* createModule() {
	return new NtshEngn::WindowModule;
}

extern "C" NTSHENGN_MODULE_API void destroyModule(NtshEngn::WindowModuleInterface* m) {
	delete m;
}