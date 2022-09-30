#pragma once
#include "../external/Common/module_interfaces/ntsh_window_module_interface.h"
#include "../external/glfw/include/GLFW/glfw3.h"

class NutshellWindowModule : public NutshellWindowModuleInterface {
private:
    GLFWwindow* m_window = nullptr;
public:
    NutshellWindowModule() : NutshellWindowModuleInterface("Nutshell Window Test Module") {}

    void init();
    void update(double dt);
    void destroy();
};