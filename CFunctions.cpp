#include "CFunctions.h"
#include "extra/CLuaArguments.h"
#include "git2.h"

void CFunctions::GitClone ( LuaVM& luaVM )
{
    std::string strUrl;
    std::string strPath;
    
    luaVM.GetParam ( strUrl );
    luaVM.GetParam ( strPath );

    if ( !luaVM.Good ( ) )
        return;

    git_repository *repos;
    git_clone_options opt = GIT_CLONE_OPTIONS_INIT;
    
    auto err = git_clone ( &repos, strUrl.c_str(), strPath.c_str(), &opt );

    if ( err < 0 )
        luaVM.Push ( giterr_last ( )->message );
    else
        luaVM.Push ( true );
}
