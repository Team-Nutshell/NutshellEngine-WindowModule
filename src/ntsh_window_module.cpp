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

void NutshellWindowModule::close() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NutshellWindowModule::shouldClose() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return false;
}

void NutshellWindowModule::setSize(int width, int height) {
	NTSH_UNUSED(width);
	NTSH_UNUSED(height);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

int NutshellWindowModule::getWidth() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}

int NutshellWindowModule::getHeight() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return 0;
}

bool NutshellWindowModule::isFullscreen() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return false;
}

void NutshellWindowModule::setFullscreen(bool fullscreen) {
	NTSH_UNUSED(fullscreen);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NutshellWindowModule::pollEvents() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NutshellWindowModule::setTitle(const std::string& title) {
	NTSH_UNUSED(title);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

NtshInputState NutshellWindowModule::getKeyState(NtshInputKeyboardKey key) {
	NTSH_UNUSED(key);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return NtshInputState::None;
}

NtshInputState NutshellWindowModule::getButtonState(NtshInputMouseButton button) {
	NTSH_UNUSED(button);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return NtshInputState::None;
}

void NutshellWindowModule::setMousePosition(int x, int y) {
	NTSH_UNUSED(x);
	NTSH_UNUSED(y);
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

int NutshellWindowModule::getMouseXPosition() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return -1;
}

int NutshellWindowModule::getMouseYPosition() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return -1;
}

#ifdef NTSH_OS_WINDOWS
HWND NutshellWindowModule::getNativeHandle() {
	NTSH_MODULE_FUNCTION_NOT_IMPLEMENTED();
	return nullptr;
}
#elif NTSH_OS_LINUX
Window NutshellWindowModule::getNativeHandle() {
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