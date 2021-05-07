
#include <iostream>
#include <string>

#include "SDL.h"
#include "trace.hpp"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main (int argc, char *argv[]) {
   TraceInit();

    SDL_Window* window = nullptr;
   
    SDL_Surface* screenSurface = nullptr;

   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      string error_message("SDL could not initialize! SDL_Error: ");
      TraceMessage(error_message + SDL_GetError());
   }
   else {
      window = SDL_CreateWindow("Testing SDL", SDL_WINDOWPOS_UNDEFINED,
         SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 
         SDL_WINDOW_SHOWN);
      
      if (!window) {
         string error_message("Window could not be created! SDL_Error: ");
         TraceMessage(error_message + SDL_GetError());
      }
      else {
         screenSurface = SDL_GetWindowSurface(window);

         SDL_FillRect(screenSurface, nullptr,
            SDL_MapRGB(screenSurface->format, 0xFF,  0xFF, 0xFF));

         SDL_UpdateWindowSurface(window);

         SDL_Delay(2000);
      }
   }

   SDL_DestroyWindow(window);

   SDL_Quit();

   return 0;
}