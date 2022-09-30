#pragma once
#include "../external/Common/module_interfaces/ntsh_window_module_interface.h"

class NutshellWindowModule : public NutshellWindowModuleInterface {
public:
    NutshellWindowModule() : NutshellWindowModuleInterface("Nutshell Window Test Module") {}

    void init();
    void update(double dt);
    void destroy();
};