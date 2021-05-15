
#include "engine.hpp"
#include "graphics.hpp"

Engine* engine;

void Engine::Initialize() {
    engine = new Engine;

    Graphics::Initialize();
    
    engine->isRunning = true;
}

void Engine::Update(float) {
    SDL_Event event;
    
    while (engine->isRunning) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                engine->isRunning = false;
            }
        }
    }

    Graphics::Render();
    Graphics::SwapWindow();
}

void Engine::Shutdown() {
    Graphics::Shutdown();
    delete engine;
}