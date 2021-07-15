/**
 * @file main.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Engine includes //
#include "trace.hpp"
#include "engine.hpp"
#include "graphics.hpp"

#include "lua.hpp"

using namespace std;

void test_lua() {
    int error_code = 0;
    lua_State *lua = luaL_newstate();
    luaL_openlibs(lua);
    luaL_dofile(lua, "data/scripts/test.lua");
    lua_close(lua);
}

/**
 * @brief Main function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main (int argc, char *argv[]) {
      // Initializing systems
    Trace::Initialize();
    Engine::Initialize();

    test_lua();
      // Engine update loop
    Graphics::Update();

      // Shutting down systems
    Engine::Shutdown();
    Trace::Shutdown();

    return 0;
}