
#include <cmath>

#include "engine.hpp"
#include "graphics.hpp"
#include "object_manager.hpp"
#include "object.hpp"
#include "model.hpp"
#include "component.hpp"
#include "transform.hpp"
#include "camera.hpp"
#include "physics.hpp"

Engine* engine;

void Engine::Initialize() {
    engine = new Engine;
    Camera::Initialize(1920, 1080);
    if (!Graphics::Initialize()) return;

    Object_Manager::Initialize();

    Object* sun = new Object;

    Model* sun_model = new Model;
    sun_model->Load("data/sun.obj");
    sun->AddComponent(sun_model);

    Transform* sun_transform = new Transform;
    sun_transform->SetPosition(vec3(0.f, 0.f, -200.f));
    sun->AddComponent(sun_transform);

    Physics* sun_physics = new Physics;
    sun_physics->SetMass(1989000);
    sun->AddComponent(sun_physics);

    Object_Manager::AddObject(sun);

    Object* earth = new Object;

    Model* earth_model = new Model;
    earth_model->Load("data/earth.obj");
    earth->AddComponent(earth_model);

    Transform* earth_transform = new Transform;
    earth_transform->SetPosition(vec3(200.f, 0.f, -200.f));
    earth->AddComponent(earth_transform);

    Physics* earth_physics = new Physics;
    earth_physics->SetMass(5.972f);
    vec3 vel = { 0.f, 0.f, 257.5522277f };
    earth_physics->SetVelocity(vel);
    earth->AddComponent(earth_physics);

    Object_Manager::AddObject(earth);

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

    while (engine->accumulator >= engine->dt) {
        Camera::Update();

        Physics::UpdateGravity();
        Object_Manager::Update();

        engine->accumulator -= engine->dt;
        engine->time += engine->dt;
    }
}

void Engine::Shutdown() {
    Camera::Shutdown();
    Graphics::Shutdown();
    delete engine;
}

float Engine::GetDeltaTime() {
    return engine->deltaTime;
}

float Engine::GetDt() { 
    return engine->dt;
}