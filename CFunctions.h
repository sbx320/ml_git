#pragma once

#include "include/ILuaModuleManager.h"
#include "LuaVM.hpp"
extern ILuaModuleManager10 *pModuleManager;

class CFunctions
{
public:
        static void      GitClone ( LuaVM& luaVM );
        static void      GitPull ( LuaVM& luaVM );
        static void      GitPush ( LuaVM& luaVM );
};
