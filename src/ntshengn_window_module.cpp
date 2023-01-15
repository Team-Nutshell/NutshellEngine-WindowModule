#include "ntshengn_window_module.h"
#include "../external/Module/utils/ntshengn_module_defines.h"
#include "../external/Module/utils/ntshengn_dynamic_library.h"
#include "../external/Common/utils/ntshengn_defines.h"
#include "../external/Common/utils/ntshengn_enums.h"

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
	return 0;
}

bool NtshEngn::WindowModule::isOpen(NtshEngn::WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return false;
}

void NtshEngn::WindowModule::close(NtshEngn::WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

uint64_t NtshEngn::WindowModule::windowCount() {
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}

void NtshEngn::WindowModule::setSize(NtshEngn::WindowId windowId, int width, int height) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(width);
	NTSHENGN_UNUSED(height);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

int NtshEngn::WindowModule::getWidth(NtshEngn::WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}

int NtshEngn::WindowModule::getHeight(NtshEngn::WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}

void NtshEngn::WindowModule::setPosition(NtshEngn::WindowId windowId, int x, int y) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(x);
	NTSHENGN_UNUSED(y);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

int NtshEngn::WindowModule::getPositionX(NtshEngn::WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return -1;
}

int NtshEngn::WindowModule::getPositionY(NtshEngn::WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return -1;
}

void NtshEngn::WindowModule::setFullscreen(NtshEngn::WindowId windowId, bool fullscreen) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(fullscreen);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NtshEngn::WindowModule::isFullscreen(NtshEngn::WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return false;
}

void NtshEngn::WindowModule::pollEvents() {
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::WindowModule::setTitle(NtshEngn::WindowId windowId, const std::string& title) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(title);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

NtshEngn::InputState NtshEngn::WindowModule::getKeyState(NtshEngn::WindowId windowId, NtshEngn::InputKeyboardKey key) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(key);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return NtshEngn::InputState::None;
}

NtshEngn::InputState NtshEngn::WindowModule::getMouseButtonState(NtshEngn::WindowId windowId, NtshEngn::InputMouseButton mouseButton) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(mouseButton);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return NtshEngn::InputState::None;
}

void NtshEngn::WindowModule::setCursorPosition(NtshEngn::WindowId windowId, int x, int y) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(x);
	NTSHENGN_UNUSED(y);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

int NtshEngn::WindowModule::getCursorPositionX(NtshEngn::WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return -1;
}

int NtshEngn::WindowModule::getCursorPositionY(NtshEngn::WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return -1;
}

void NtshEngn::WindowModule::setCursorVisibility(NtshEngn::WindowId windowId, bool visible) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_UNUSED(visible);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NtshEngn::WindowModule::isCursorVisible(NtshEngn::WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return false;
}

#if defined(NTSHENGN_OS_WINDOWS)
HWND NtshEngn::WindowModule::getNativeHandle(NtshEngn::WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return nullptr;
}
#elif defined(NTSHENGN_OS_LINUX)
Window NtshEngn::WindowModule::getNativeHandle(NtshEngn::WindowId windowId) {
	NTSHENGN_UNUSED(windowId);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}
#endif

extern "C" NTSHENGN_MODULE_API NtshEngn::WindowModuleInterface* createModule() {
	return new NtshEngn::WindowModule;
}

extern "C" NTSHENGN_MODULE_API void destroyModule(NtshEngn::WindowModuleInterface* m) {
	delete m;
}