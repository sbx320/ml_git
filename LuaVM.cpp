#include "LuaVM.hpp"

LuaVM::LuaVM ( lua_State * state )
{
    L = state;
}


template<>
void LuaVM::Push<std::string> ( const std::string& value )
{
    lua_pushlstring ( L, value.c_str ( ), value.length ( ) );
    ++numReturns;
}

template<>
void LuaVM::Push<const char*> ( const char* const& value )
{
    lua_pushstring ( L, value );
    ++numReturns;
}

template<>
void LuaVM::Push<char*> ( char* const& value )
{
    lua_pushstring ( L, value );
    ++numReturns;
}

template<>
void LuaVM::Push<bool> ( const bool& value )
{
    lua_pushboolean ( L, value );
    ++numReturns;
}

template<>
void LuaVM::Push<double> ( const double& value )
{
    lua_pushnumber ( L, value );
    ++numReturns;
}

template<>
void LuaVM::Push<int> ( const int& value )
{
    lua_pushnumber ( L, value );
    ++numReturns;
}

template<>
void LuaVM::Push<float> ( const float& value )
{
    lua_pushnumber ( L, value );
    ++numReturns;
}


template<>
bool LuaVM::DoesTypeAtIndexMatch<int> ( unsigned int currentIndex )
{
    return lua_isnumber ( L, currentIndex ) != 0;
}


template<>
bool LuaVM::DoesTypeAtIndexMatch<std::string> ( unsigned int currentIndex )
{
    return lua_isstring ( L, currentIndex ) != 0;
}


template<>
void LuaVM::Pop<int> ( int& value )
{
    value = static_cast<int>( lua_tonumber ( L, currentIndex ) );
}

template<>
void LuaVM::Pop<std::string> ( std::string& value )
{
    size_t len;
    const char *tmp = lua_tolstring ( L, currentIndex, &len );
    value.assign ( tmp, len );
}