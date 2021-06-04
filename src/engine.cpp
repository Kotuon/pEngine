
#include <cmath>
#include <string>

#include "engine.hpp"
#include "graphics.hpp"
#include "object_manager.hpp"
#include "object.hpp"
#include "model.hpp"
#include "component.hpp"
#include "transform.hpp"
#include "camera.hpp"
#include "physics.hpp"
#include "file_reader.hpp"

static Engine* engine = nullptr;

void Engine::Initialize() {
    engine = new Engine;
    if (!engine) {
        Trace::Message("Engine was not initialized.\n");
        return;
    }

    if (!Camera::Initialize(1920, 1080)) return;
    if (!Graphics::Initialize()) return;
    if (!Object_Manager::Initialize()) return;

    // Object* sun = new Object("sun");
    // Object_Manager::AddObject(sun);

    // Object* earth = new Object("earth");
    // Object_Manager::AddObject(earth);

    engine->currentTime = chrono::steady_clock::now();
    engine->accumulator = 0.f;
    engine->time = 0.f;
    engine->isRunning = true;

}

void Engine::Update() {
    engine->newTime = chrono::steady_clock::now();
    engine->timeTaken = engine->newTime - engine->currentTime;
    engine->deltaTime = float(engine->timeTaken.count()) * chrono::steady_clock::period::num / chrono::steady_clock::period::den;
    engine->currentTime = engine->newTime;

    engine->accumulator += engine->deltaTime;

    Camera::Update();
    while (engine->accumulator >= engine->dt) {

        Physics::UpdateGravity();
        Object_Manager::Update();

        engine->accumulator -= engine->dt;
        engine->time += engine->dt;
    }
}

void Engine::Shutdown() {
    Object_Manager::Shutdown();
    Graphics::Shutdown();
    Camera::Shutdown();
    delete engine;
}

float Engine::GetDeltaTime() {
    return engine->deltaTime;
}

float Engine::GetDt() { 
    return engine->dt;
}