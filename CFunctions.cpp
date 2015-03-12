#include "CFunctions.h"
#include "extra/CLuaArguments.h"

int CFunctions::GitClone ( lua_State* luaVM )
{
    if ( luaVM )
    {
        CLuaArguments args;
        args.PushString("Hello World!");
        args.PushArguments(luaVM);
        return 1;
    }
    return 0;
}