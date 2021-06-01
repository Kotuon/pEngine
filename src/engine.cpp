
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

    engine->startTime = chrono::steady_clock::now();
    engine->oldStartTime = chrono::steady_clock::now();
    engine->isRunning = true;

    Object_Manager::Initialize();

    Object* object = new Object;

    Model* model = new Model;
    model->Load("data/cube1.obj");
    object->AddComponent(model);

    Transform* transform = new Transform;
    transform->SetPosition(vec3(0.f, 0.f, -20.f));
    object->AddComponent(transform);

    Physics* physics = new Physics;
    physics->SetMass(10000.f);
    object->AddComponent(physics);

    for (int i = 0; i < 2; ++i) {
        Object* newObject = object->Clone();

        int switchVar = -1 * (i % 2);
        
        Transform* transform = newObject->GetComponent<Transform>(CType::CTransform);
        transform->SetPosition(vec3(i * 4 - 16, 5.f * switchVar, -20.f));

        Object_Manager::AddObject(newObject);
    }

    delete object;
}

void Engine::Update() {
    engine->startTime = chrono::steady_clock::now();
    engine->deltaTime = (engine->startTime - engine->oldStartTime).count();
    engine->oldStartTime = engine->startTime;
    Camera::Update();
    // for (int i = 0; i < 10; ++i) {
    //     Object* object = Object_Manager::FindObject(i);
    //     //Transform* transform = object->GetComponent<Transform>(CType::CTransform);
    //     //transform->SetRotation(transform->GetRotation() + .3f);

    //     Physics* physics = object->GetComponent<Physics>(CType::CPhysics);
    //     vec3 accel = { 10.f, 0.f, 0.f };
    //     physics->SetAcceleration(accel);
    // }
    Object_Manager::Update();
}

void Engine::Shutdown() {
    Camera::Shutdown();
    Graphics::Shutdown();
    delete engine;
}

float Engine::GetDeltaTime() {
    return engine->deltaTime;
}