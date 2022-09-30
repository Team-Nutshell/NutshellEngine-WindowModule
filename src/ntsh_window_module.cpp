#include "ntsh_window_module.h"
#include "../external/Module/ntsh_module_defines.h"
#include "../external/Module/ntsh_dynamic_library.h"
#include "../external/Common/ntsh_engine_enums.h"

void NutshellWindowModule::init() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_window = glfwCreateWindow(1280, 720, m_name.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(m_window, this);
}

void NutshellWindowModule::update(double dt) {
    NTSH_UNUSED(dt);
    NTSH_MODULE_WARNING("update() function not implemented.");
}

void NutshellWindowModule::destroy() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

extern "C" NTSH_MODULE_API NutshellWindowModuleInterface * createModule() {
    return new NutshellWindowModule;
}

extern "C" NTSH_MODULE_API void destroyModule(NutshellWindowModuleInterface * m) {
    delete m;
}