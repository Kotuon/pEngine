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

/**
 * @brief Main function
 * 
 * @return int 
 */
int main (int, char *[]) {
      // Initializing systems
    Trace::Initialize();
    if (!Engine::Initialize()) return -1;
      // Engine update loop
    Graphics::Update();

      // Shutting down systems
    Engine::Shutdown();
    Trace::Shutdown();

    return 0;
}