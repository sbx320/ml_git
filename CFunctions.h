#pragma once

#include "include/ILuaModuleManager.h"
#include "LuaVM.hpp"
#include "git2.h"

extern ILuaModuleManager10 *pModuleManager;

class CFunctions
{
public:
        static void      GitClone ( LuaVM& luaVM );
        static void      GitPull ( LuaVM& luaVM );
        static void      GitGetHeadId ( LuaVM& luaVM );

        static git_repository * repo;
};
