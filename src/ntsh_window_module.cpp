#include "ntsh_window_module.h"
#include "../external/Module/utils/ntsh_module_defines.h"
#include "../external/Module/utils/ntsh_dynamic_library.h"
#include "../external/Common/utils/ntsh_engine_defines.h"
#include "../external/Common/utils/ntsh_engine_enums.h"

void NutshellWindowModule::init() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NutshellWindowModule::update(double dt) {
	NTSH_UNUSED(dt);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NutshellWindowModule::destroy() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

NtshWindowId NutshellWindowModule::open() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}

bool NutshellWindowModule::isOpen(NtshWindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return false;
}

void NutshellWindowModule::close(NtshWindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

uint64_t NutshellWindowModule::windowCount() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}

void NutshellWindowModule::setSize(NtshWindowId windowId, int width, int height) {
	NTSH_UNUSED(windowId);
	NTSH_UNUSED(width);
	NTSH_UNUSED(height);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

int NutshellWindowModule::getWidth(NtshWindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}

int NutshellWindowModule::getHeight(NtshWindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}

void NutshellWindowModule::setPosition(NtshWindowId windowId, int x, int y) {
	NTSH_UNUSED(windowId);
	NTSH_UNUSED(x);
	NTSH_UNUSED(y);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

int NutshellWindowModule::getPositionX(NtshWindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return -1;
}

int NutshellWindowModule::getPositionY(NtshWindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return -1;
}

void NutshellWindowModule::setFullscreen(NtshWindowId windowId, bool fullscreen) {
	NTSH_UNUSED(windowId);
	NTSH_UNUSED(fullscreen);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NutshellWindowModule::isFullscreen(NtshWindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return false;
}

void NutshellWindowModule::pollEvents() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NutshellWindowModule::setTitle(NtshWindowId windowId, const std::string& title) {
	NTSH_UNUSED(windowId);
	NTSH_UNUSED(title);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

NtshInputState NutshellWindowModule::getKeyState(NtshWindowId windowId, NtshInputKeyboardKey key) {
	NTSH_UNUSED(windowId);
	NTSH_UNUSED(key);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return NtshInputState::None;
}

NtshInputState NutshellWindowModule::getMouseButtonState(NtshWindowId windowId, NtshInputMouseButton mouseButton) {
	NTSH_UNUSED(windowId);
	NTSH_UNUSED(mouseButton);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return NtshInputState::None;
}

void NutshellWindowModule::setCursorPosition(NtshWindowId windowId, int x, int y) {
	NTSH_UNUSED(windowId);
	NTSH_UNUSED(x);
	NTSH_UNUSED(y);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

int NutshellWindowModule::getCursorPositionX(NtshWindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return -1;
}

int NutshellWindowModule::getCursorPositionY(NtshWindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return -1;
}

void NutshellWindowModule::setCursorVisibility(NtshWindowId windowId, bool visible) {
	NTSH_UNUSED(windowId);
	NTSH_UNUSED(visible);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NutshellWindowModule::isCursorVisible(NtshWindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return false;
}

#if defined(NTSH_OS_WINDOWS)
HWND NutshellWindowModule::getNativeHandle(NtshWindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return nullptr;
}
#elif defined(NTSH_OS_LINUX)
Window NutshellWindowModule::getNativeHandle(NtshWindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}
#endif

extern "C" NTSH_MODULE_API NutshellWindowModuleInterface* createModule() {
	return new NutshellWindowModule;
}

extern "C" NTSH_MODULE_API void destroyModule(NutshellWindowModuleInterface* m) {
	delete m;
}