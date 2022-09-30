#include "ntsh_window_module.h"
#include "../external/Module/ntsh_module_defines.h"
#include "../external/Module/ntsh_dynamic_library.h"
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

extern "C" NTSH_MODULE_API NutshellWindowModuleInterface * createModule() {
    return new NutshellWindowModule;
}

extern "C" NTSH_MODULE_API void destroyModule(NutshellWindowModuleInterface * m) {
    delete m;
}