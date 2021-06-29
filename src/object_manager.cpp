/**
 * @file object_manager.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Engine includes //
#include "behavior.hpp"
#include "object_manager.hpp"
#include "trace.hpp"
#include "transform.hpp"

static Object_Manager* object_manager = nullptr; //!< Object_Manager object

/**
 * @brief Initializes the object_manager object. Reads in objects for the given
 *        preset
 * 
 * @param preset List of objects for this preset
 * @return true 
 * @return false 
 */
bool Object_Manager::Initialize(File_Reader& preset) {
      // Initializing object_manager
    object_manager = new Object_Manager;
    if (!object_manager) {
        Trace::Message("Object Manager was not initialized.");
        return false; // Failed to initialize
    }

      // Adding objects from preset into engine
    object_manager->objects.reserve(10);
    object_manager->ReadList(preset);

    return true; // Successful initialization
}

/**
 * @brief Adds object to object_manager
 * 
 * @param object Object to be added
 * @return void
 */
void Object_Manager::AddObject(Object* object) {
      // Tells object its location in object_manager object list
    object->SetId(object_manager->objects.size());
    object_manager->objects.emplace_back(object);
}

/**
 * @brief Finds a object using its id (location in object list) giving instant access
 * 
 * @param id Location of object in object_manager object list
 * @return Object* 
 */
Object* Object_Manager::FindObject(unsigned id) {
    return object_manager->objects[id];
}

/**
 * @brief Gets the size of the object_manager object list
 * 
 * @return unsigned Size of object list
 */
unsigned Object_Manager::GetSize() { return object_manager->objects.size(); }

/**
 * @brief Calls the update function for each object in the object list
 * 
 * @return void
 */
void Object_Manager::Update() {
    for (unsigned i = 0; i < object_manager->objects.size(); ++i) {
        object_manager->FindObject(i)->Update();
    }
}

/**
 * @brief Deletes all objects in the manager and then the object manager
 * 
 * @return void
 */
void Object_Manager::Shutdown() {
    if (!object_manager) return; // If the object_manager doesn't exist

      // Deleting each object in the manager
    for (unsigned i = 0; i < object_manager->objects.size(); ++i) {
        Object* object = object_manager->FindObject(i);
        if (object)
            delete object;
    }

      // Deleting the manager
    delete object_manager;
    object_manager = nullptr;
}

/**
 * @brief Reads in objects from a preset list that is given
 * 
 * @param preset List of objects to be added
 */
void Object_Manager::ReadList(File_Reader& preset) {
      // Track which object we are on
    unsigned object_num = 0;

      // Reads objects until there is a failed read
    while (true) {
          // Getting the name of the objects file
        string object_name = preset.Read_Object_Name("object_" + to_string(object_num));
        if (object_name.compare("") == 0) break;

          // Constructing the object 
        Object* object = new Object(object_name);
          // Reading in the objects position
        vec3 position = preset.Read_Object_Position("object_" + to_string(object_num));
        Transform* transform = object->GetComponent<Transform>();
        transform->SetPosition(position);
        Behavior* behavior = object->GetComponent<Behavior>();
        behavior->SetStartPos(position);

          // Adding the object to the manager
        AddObject(object);

        ++object_num;
    }
}