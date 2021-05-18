
#include "engine.hpp"
#include "graphics.hpp"
#include "object_manager.hpp"

#include "object.hpp"
#include "model.hpp"
#include "component.hpp"
#include "transform.hpp"

Engine* engine;

void Engine::Initialize() {
    engine = new Engine;
    if (!Graphics::Initialize()) return;

    engine->isRunning = true;

    Object_Manager::Initialize();

    Object* object = new Object;

    Model* model = new Model;
    model->Load("data/cube1.obj");
    object->AddComponent(model);

    Transform* transform = new Transform;
    transform->SetPosition(vec3(0.f, 0.f, -7.f));
    object->AddComponent(transform);

    Object_Manager::AddObject(object);
}

void Engine::Update(float) {
    Object* object = Object_Manager::FindObject(0);
    Transform* transform = object->GetComponent<Transform>(CType::CTransform);
    transform->SetRotation(transform->GetRotation() + .3f);

    vec3 pos = transform->GetPosition();

    static bool left = true;
    
    if (left && pos.x > -3.f) {
        pos.x -= .01f;
        if (pos.x <= -3.f) left = false;
    }
    else {
        pos.x += .01f;
        if (pos.x >= 3.f) left = true;
    }

    transform->SetPosition(pos);
}

void Engine::Shutdown() {
    Graphics::Shutdown();
    delete engine;
}