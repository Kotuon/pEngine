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

// std includes //
#include <string>

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
Object* Object_Manager::FindObject(int id) {
    if (id >= object_manager->objects.size()) return nullptr;
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
        std::string object_name = preset.Read_Object_Name("object_" + std::to_string(object_num));
        if (object_name.compare("") == 0) break;

          // Constructing the object 
        Object* object = new Object(object_name);
          // Reading in the objects position
        glm::vec3 position = preset.Read_Object_Position("object_" + std::to_string(object_num));
        Transform* transform = object->GetComponent<Transform>();
        transform->SetPosition(position);
        transform->SetStartPosition(position);
        Behavior* behavior = object->GetComponent<Behavior>();
        behavior->SetupClassesForLua();

          // Adding the object to the manager
        AddObject(object);
        object->Write();

        ++object_num;
    }
}

/**
 * @brief Checks if the name of the given object is already being used. If it is
 *        being used it applies a number to the back.
 * 
 * @param object 
 */
std::string Object_Manager::CheckName(std::string objectName, int id) {
    int objWithName = 0;
    for (Object* objToCheck : object_manager->objects) {
        if (id != -1 && objToCheck->GetId() == id) continue;
        if (objToCheck->GetName().find(objectName) != std::string::npos)
            ++objWithName;
    }

    if (objWithName > 0)
        return objectName + "_" + std::to_string(objWithName);
    
    return objectName;
}

void Object_Manager::RemoveObject(int id) {
    if (id >= object_manager->objects.size()) return;
    Object* objectToDelete = object_manager->objects[id];

    unsigned offset = 0;
    for (unsigned objectNum = id + 1; objectNum < object_manager->objects.size(); ++objectNum) {
        Object* objectToSwitch = object_manager->objects[objectNum];
        object_manager->objects[id + offset] = objectToSwitch;
        objectToSwitch->SetId(id + offset++);
    }

    delete objectToDelete;
    objectToDelete = nullptr;
    object_manager->objects.pop_back();
}