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

using namespace std;

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

      // Engine update loop
    Graphics::Update();

      // Shuting down systems
    Engine::Shutdown();
    Trace::Shutdown();

    return 0;
}