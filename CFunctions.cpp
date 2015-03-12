#include "CFunctions.h"
#include "extra/CLuaArguments.h"
#include "git2.h"

int CFunctions::GitClone ( lua_State* luaVM )
{
    if ( !luaVM )
        return 0;

    if ( !lua_type ( luaVM, -1 ) ||
         !lua_type ( luaVM, -2 ))
    {
        lua_pushboolean ( luaVM, false );
    }

    auto url = lua_tostring ( luaVM, -1 );
    auto path = lua_tostring ( luaVM, -2 );

    git_repository *repos;
    git_clone_options opt = GIT_CLONE_OPTIONS_INIT;
    
    auto err = git_clone ( &repos, url, path, &opt );

    if ( err == -1 )
        lua_pushstring ( luaVM, giterr_last ( )->message );
    else
        lua_pushboolean ( luaVM, true );
    return 1;
}

int CFunctions::GitPull( lua_State* luaVM )
{
    return 1;
}



int CFunctions::GitPush ( lua_State* luaVM )
{
    return 0;
}