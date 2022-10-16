#include "ntsh_window_module.h"
#include "../external/Module/ntsh_module_defines.h"
#include "../external/Module/ntsh_dynamic_library.h"
#include "../external/Common/ntsh_engine_defines.h"
#include "../external/Common/ntsh_engine_enums.h"

void NutshellWindowModule::init() {
	NTSH_MODULE_WARNING("init() function not implemented.");
}

void NutshellWindowModule::update(double dt) {
	NTSH_UNUSED(dt);
	NTSH_MODULE_WARNING("update() function not implemented.");
}

void NutshellWindowModule::destroy() {
	NTSH_MODULE_WARNING("destroy() function not implemented.");
}

void NutshellWindowModule::closeWindow() {
	NTSH_MODULE_WARNING("closeWindow() function not implemented.");
}

bool NutshellWindowModule::shouldClose() {
	NTSH_MODULE_WARNING("shouldClose() function not implemented.");
	return false;
}

void NutshellWindowModule::setWindowSize(int width, int height) {
	NTSH_UNUSED(width);
	NTSH_UNUSED(height);
	NTSH_MODULE_WARNING("setWindowSize() function not implemented.");
}

int NutshellWindowModule::getWindowWidth() {
	NTSH_MODULE_WARNING("getWindowWidth() function not implemented.");
	return 0;
}

int NutshellWindowModule::getWindowHeight() {
	NTSH_MODULE_WARNING("getWindowHeight() function not implemented.");
	return 0;
}

bool NutshellWindowModule::isFullscreen() {
	NTSH_MODULE_WARNING("isFullscreen() function not implemented.");
	return false;
}

void NutshellWindowModule::setFullscreen(bool fullscreen) {
	NTSH_UNUSED(fullscreen);
	NTSH_MODULE_WARNING("setFullscreen() function not implemented.");
}

bool NutshellWindowModule::gotResized() {
	NTSH_MODULE_WARNING("gotResized() function not implemented.");
	return false;
}

void NutshellWindowModule::setTitle(const std::string& title) {
	NTSH_UNUSED(title);
	NTSH_MODULE_WARNING("setTitle() function not implemented.");
}

#ifdef NTSH_OS_WINDOWS
HWND NutshellWindowModule::getWindowHandle() {
	NTSH_MODULE_WARNING("getWindowHandle() function not implemented.");
	return nullptr;
}
#elif NTSH_OS_LINUX
Window NutshellWindowModule::getWindowHandle() {
	NTSH_MODULE_WARNING("getWindowHandle() function not implemented.");
	return 0;
}
#endif

extern "C" NTSH_MODULE_API NutshellWindowModuleInterface* createModule() {
	return new NutshellWindowModule;
}

extern "C" NTSH_MODULE_API void destroyModule(NutshellWindowModuleInterface* m) {
	delete m;
}