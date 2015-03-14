# ml_git
Simple Git module for the MTA:SA server. 

## Important:
Path variables are not being sanitized, prevent access via ACL or other measures if you use this.
All functions either return true (on success) or and error code plus an error message (on failure).

## Available functions: 

    bool/<int string> gitClone(string url, string path)

Clones the repository at ''url'' into the folder ''path'' (as seen from the root folder of the MTA Server). 

Example:

    gitClone("https://github.com/sbx320/awesomeresource.git", "awesomeresource")

Clones https://github.com/sbx320/awesomeresource.git into the the resources folder with the resource name "awesomeresource"

-----

bool/<int string> gitPull(string path)

Updates the repository at ''path'' from the remote origin.

Example:

    gitPull("awesomeresource")

-----

string/<int string> gitHeadId(string path)

Gets the SHA Hash of the current HEAD revision for the repository at ''path''.
