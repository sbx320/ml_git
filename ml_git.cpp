#include "ml_git.h"
#include "git2.h"

ILuaModuleManager10 *pModuleManager = NULL;

MTAEXPORT bool InitModule ( ILuaModuleManager10 *pManager, char *szModuleName, char *szAuthor, float *fVersion )
{
    pModuleManager = pManager;

    // Set the module info
    strncpy ( szModuleName, MODULE_NAME, MAX_INFO_LENGTH );
    strncpy ( szAuthor, MODULE_AUTHOR, MAX_INFO_LENGTH );
    (*fVersion) = MODULE_VERSION;
    git_libgit2_init ( );
    return true;
}


MTAEXPORT void RegisterFunctions ( lua_State * luaVM )
{
    if ( pModuleManager && luaVM )
    {
        pModuleManager->RegisterFunction ( luaVM, "gitClone", CFunctions::GitClone );
        pModuleManager->RegisterFunction ( luaVM, "gitPull", CFunctions::GitPull );
        pModuleManager->RegisterFunction ( luaVM, "gitPush", CFunctions::GitPush );
    }
}


MTAEXPORT bool DoPulse ( void )
{
    return true;
}

MTAEXPORT bool ShutdownModule ( void )
{
    git_libgit2_shutdown ( );
    return true;
}

MTAEXPORT bool ResourceStopping ( lua_State * luaVM )
{
    return true;
}

MTAEXPORT bool ResourceStopped ( lua_State * luaVM )
{
    return true;
}