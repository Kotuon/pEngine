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

#include <iostream>
#include <string>

#include "main.hpp"
#include "trace.hpp"
#include "engine.hpp"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

/**
 * @brief Inititalizes the sdl window
 * 
 * @return SDL_Window* 
 */
SDL_Window* InitWindow() {
   SDL_Window* window = nullptr;
   
   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      string error_message("SDL could not initialize! SDL_Error: ");
      Trace::Message(error_message + SDL_GetError());

      Shutdown(window);

      return nullptr;
   }
   window = SDL_CreateWindow("Testing SDL", SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 
      SDL_WINDOW_SHOWN);
   
   if (!window) {
      string error_message("Window could not be created! SDL_Error: ");
      Trace::Message(error_message + SDL_GetError());

      Shutdown(window);

      return nullptr;
   }

   return window;
}

/**
 * @brief Initializes the sdl screen
 * 
 * @param window 
 * @return SDL_Surface* 
 */
SDL_Surface* Initscreen_surface(SDL_Window* window) {
   SDL_Surface* screen_surface = nullptr;

   screen_surface = SDL_GetWindowSurface(window);
   SDL_FillRect(screen_surface, nullptr,
      SDL_MapRGB(screen_surface->format, 0xFF,  0xFF, 0xFF));

   return screen_surface;
}

/**
 * @brief Update loop for application
 * 
 * @param window
 */
void Update(SDL_Window* window) {
   bool isRunning = true;
   SDL_Event event_handler;

   while (isRunning) {

      while(SDL_PollEvent(&event_handler) != 0) {
          if(event_handler.type == SDL_QUIT) {
              isRunning = false;
          }
      }

      Engine::Update(0.f);

      SDL_UpdateWindowSurface(window);
   }
}

/**
 * @brief Shutsdown sdl and engine systems in proper order
 * 
 * @param window 
 */
void Shutdown(SDL_Window* window) {
   SDL_DestroyWindow(window);
   SDL_Quit();

   Engine::Shutdown();
   Trace::Shutdown();
}

/**
 * @brief Main function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main (int argc, char *argv[]) {
   Trace::Init();
   Engine::Init();

   SDL_Window* window = InitWindow();
   SDL_Surface* screen_surface = Initscreen_surface(window);

   Update(window);

   Shutdown(window);

   return 0;
}