#pragma once

#include "include/ILuaModuleManager.h"
extern ILuaModuleManager10 *pModuleManager;

class CFunctions
{
public:
        static int      GitClone ( lua_State* luaVM );
        static int      GitPull  ( lua_State* luaVM );
        static int      GitPush  ( lua_State* luaVM );
};
