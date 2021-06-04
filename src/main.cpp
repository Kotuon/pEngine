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

#include <SDL.h>

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
int SDL_main (int argc, char *argv[]) {
   Trace::Initialize();

   Engine::Initialize();

   Graphics::Update();

   Engine::Shutdown();

   Trace::Shutdown();

   return 0;
}