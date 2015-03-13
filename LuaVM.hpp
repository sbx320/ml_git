#pragma once

#include <map>
extern "C"
{
    #include "lua.h"
}

class LuaVM
{
public:
    LuaVM ( ) = delete;
    LuaVM ( lua_State * state );
    ~LuaVM ( ) = default;

    void RegisterFunction ( const std::string& name, lua_CFunction func );

    /* Pushing of Lua Values to the stack */
    template<typename T>
    void Push ( const T& value );

    template<typename T, typename... S>
    void Push ( const T& value, S... args )
    {
        Push ( value );
        Push ( args... );
    }

    void Push ( ) {};

    /* Popping T from the stack */
    template<typename T>
    void Pop ( T& value );

    /* Attempts to read a T from the stack*/
    template<typename T>
    void GetParam ( T& e )
    {
        stackDump(L);
        if ( hasError )
            return;

        if ( DoesTypeAtIndexMatch<T> ( currentIndex ) )
        {
            Pop ( e );
            currentIndex++;
            return;
        }

        hasError = true;
        error = "Expected T at argument " + std::to_string ( currentIndex );
    }

    template<typename T>
    bool DoesTypeAtIndexMatch ( unsigned int index );

    template<typename T>
    void GetParam ( T& e, const T& def );

    bool Good ( ) { return !hasError; }
public:
    template <void ( *T )( LuaVM & )>
    static int LuaFunctionDispatcher ( lua_State* L )
    {
        auto vm = LuaVM ( L );
        vm.numReturns = 0;
        vm.currentIndex = 1;
        vm.hasError = false;
        T ( vm );
        return vm.numReturns;
    }
private:
    int numReturns;
    int currentIndex;
    std::string error;
    bool hasError;
private:
    lua_State * L;
};