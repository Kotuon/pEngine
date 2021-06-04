
#include "object_manager.hpp"
#include "trace.hpp"
#include "file_reader.hpp"

static Object_Manager* object_manager = nullptr;

bool Object_Manager::Initialize() {
    object_manager = new Object_Manager;

    if (!object_manager) {
        Trace::Message("Object Manager was not initialized.");
        return false;
    }

    object_manager->objects.reserve(100);

    object_manager->ReadList();

    return true;
}

void Object_Manager::AddObject(Object* object) {
    object->SetId(object_manager->objects.size());
    object_manager->objects.emplace_back(object);
}

Object* Object_Manager::FindObject(unsigned id) {
    return object_manager->objects[id];
}

unsigned Object_Manager::GetSize() { return object_manager->objects.size(); }

void Object_Manager::Update() {
    for (unsigned i = 0; i < object_manager->objects.size(); ++i) {
        object_manager->FindObject(i)->Update();
    }
}

void Object_Manager::Shutdown() {
    if (!object_manager) return;

    for (unsigned i = 0; i < object_manager->objects.size(); ++i) {
        Object* object = object_manager->FindObject(i);
        if (object)
            delete object;
    }

    delete object_manager;
}

void Object_Manager::ReadList() {
    File_Reader reader("object_list");
    unsigned object_num = 0;

    while (true) {
        string object_name = reader.Read_String("object_" + to_string(object_num));
        if (object_name.compare("") == 0) break;

        Object* object = new Object(object_name);
        AddObject(object);
        ++object_num;
    }
}