
#include "object_manager.hpp"

static Object_Manager* object_manager;

void Object_Manager::Initialize() {
    object_manager = new Object_Manager;

    object_manager->objects.reserve(100);
}

void Object_Manager::AddObject(Object* object) {
    object->SetId(object_manager->objects.size());
    object_manager->objects.emplace_back(object);
}

Object* Object_Manager::FindObject(unsigned id) {
    return object_manager->objects[id];
}

unsigned Object_Manager::GetSize() { return object_manager->objects.size(); }