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

Ntsh::WindowId NutshellWindowModule::open(int width, int height, const std::string& title) {
	NTSH_UNUSED(width);
	NTSH_UNUSED(height);
	NTSH_UNUSED(title);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}

bool NutshellWindowModule::isOpen(Ntsh::WindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return false;
}

void NutshellWindowModule::close(Ntsh::WindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

uint64_t NutshellWindowModule::windowCount() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}

void NutshellWindowModule::setSize(Ntsh::WindowId windowId, int width, int height) {
	NTSH_UNUSED(windowId);
	NTSH_UNUSED(width);
	NTSH_UNUSED(height);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

int NutshellWindowModule::getWidth(Ntsh::WindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}

int NutshellWindowModule::getHeight(Ntsh::WindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}

void NutshellWindowModule::setPosition(Ntsh::WindowId windowId, int x, int y) {
	NTSH_UNUSED(windowId);
	NTSH_UNUSED(x);
	NTSH_UNUSED(y);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

int NutshellWindowModule::getPositionX(Ntsh::WindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return -1;
}

int NutshellWindowModule::getPositionY(Ntsh::WindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return -1;
}

void NutshellWindowModule::setFullscreen(Ntsh::WindowId windowId, bool fullscreen) {
	NTSH_UNUSED(windowId);
	NTSH_UNUSED(fullscreen);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NutshellWindowModule::isFullscreen(Ntsh::WindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return false;
}

void NutshellWindowModule::pollEvents() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NutshellWindowModule::setTitle(Ntsh::WindowId windowId, const std::string& title) {
	NTSH_UNUSED(windowId);
	NTSH_UNUSED(title);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

Ntsh::InputState NutshellWindowModule::getKeyState(Ntsh::WindowId windowId, Ntsh::InputKeyboardKey key) {
	NTSH_UNUSED(windowId);
	NTSH_UNUSED(key);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return Ntsh::InputState::None;
}

Ntsh::InputState NutshellWindowModule::getMouseButtonState(Ntsh::WindowId windowId, Ntsh::InputMouseButton mouseButton) {
	NTSH_UNUSED(windowId);
	NTSH_UNUSED(mouseButton);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return Ntsh::InputState::None;
}

void NutshellWindowModule::setCursorPosition(Ntsh::WindowId windowId, int x, int y) {
	NTSH_UNUSED(windowId);
	NTSH_UNUSED(x);
	NTSH_UNUSED(y);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

int NutshellWindowModule::getCursorPositionX(Ntsh::WindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return -1;
}

int NutshellWindowModule::getCursorPositionY(Ntsh::WindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return -1;
}

void NutshellWindowModule::setCursorVisibility(Ntsh::WindowId windowId, bool visible) {
	NTSH_UNUSED(windowId);
	NTSH_UNUSED(visible);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NutshellWindowModule::isCursorVisible(Ntsh::WindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return false;
}

#if defined(NTSH_OS_WINDOWS)
HWND NutshellWindowModule::getNativeHandle(Ntsh::WindowId windowId) {
	NTSH_UNUSED(windowId);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return nullptr;
}
#elif defined(NTSH_OS_LINUX)
Window NutshellWindowModule::getNativeHandle(Ntsh::WindowId windowId) {
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