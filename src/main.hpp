
#ifndef MAIN_HPP
#define MAIN_HPP

#include "SDL.h"

SDL_Window* InitWindow();
SDL_Surface* InitScreenSurface(SDL_Window* window);

void Update(SDL_Window* window);
void Shutdown(SDL_Window* window);



#endif