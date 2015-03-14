#include "CFunctions.h"
#include "extra/CLuaArguments.h"
#include "git2.h"

git_repository * CFunctions::repo;


bool GitErrorCheck ( LuaVM& luaVM, int error )
{
    if ( error < 0 )
    {
        auto err = giterr_last ( );
        luaVM.Push ( err->klass, err->message );
        return true;
    }
    return false;
}


void CFunctions::GitClone ( LuaVM& luaVM )
{
    std::string strUrl;
    std::string strPath;
    
    luaVM.GetParam ( strUrl );
    luaVM.GetParam ( strPath );

    if ( !luaVM.Good ( ) )
        return;

    git_clone_options opt = GIT_CLONE_OPTIONS_INIT;
    
    auto error = git_clone ( &repo, strUrl.c_str(), strPath.c_str(), &opt );

    if ( GitErrorCheck ( luaVM, error ) )
        return;

    luaVM.Push ( true );
}


void CFunctions::GitPull ( LuaVM& luaVM )
{
    std::string strPath;

    luaVM.GetParam ( strPath );

    if ( !luaVM.Good ( ) )
        return;

    // Open the repos
    int error = git_repository_open ( &repo, strPath.c_str ( ) );
    if ( GitErrorCheck ( luaVM, error ) )
        return;

    // Get the remote
    git_remote* remote;
    error = git_remote_lookup ( &remote, repo, "origin" );
    if ( GitErrorCheck ( luaVM, error ) )
        return;

    // Fetch changes from origin
    error = git_remote_fetch ( remote, NULL, NULL );
    if ( GitErrorCheck ( luaVM, error ) )
        return;

    // Merge changes
    // this is horrible
    std::vector<git_annotated_commit*> commits;
    
    git_repository_fetchhead_foreach ( repo, []
    (const char *ref_name, const char *remote_url, const git_oid *oid, unsigned int is_merge, void *pcommits ) -> int
    {
        std::vector<git_annotated_commit*>* commits = ( std::vector<git_annotated_commit*>* )pcommits;
        git_annotated_commit* commit;
        int error = git_annotated_commit_from_fetchhead ( &commit, repo, "master", remote_url, oid );
        commits->push_back ( commit );

        return error;
    }, (void*)&commits );

    git_merge_options mergopts = GIT_MERGE_OPTIONS_INIT;

    // Favor remote repository
    mergopts.file_favor = GIT_MERGE_FILE_FAVOR_THEIRS;

    error = git_merge ( repo, (const git_annotated_commit**)&commits [0], commits.size ( ), NULL, NULL );
    if ( GitErrorCheck ( luaVM, error ) )
        return;

    luaVM.Push ( true );
}

void CFunctions::GitGetHeadId ( LuaVM& luaVM )
{
    std::string strPath;

    luaVM.GetParam ( strPath );

    if ( !luaVM.Good ( ) )
        return;

    // Open the repo
    int error = git_repository_open ( &repo, strPath.c_str ( ) );
    if ( GitErrorCheck ( luaVM, error ) )
        return;

    git_oid head;
    error = git_reference_name_to_id ( &head, repo, "HEAD" );
    if ( GitErrorCheck ( luaVM, error ) )
        return;

    char buf [GIT_OID_HEXSZ + 1];
    
    git_oid_tostr ( buf, sizeof ( buf ), &head );
    luaVM.Push ( (char*)buf );

}