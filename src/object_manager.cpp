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
    if (id >= (int)object_manager->objects.size()) return nullptr;
    return object_manager->objects[id];
}

/**
 * @brief Finds object with the matching name
 * 
 * @param objectName Name to look for
 * @return Object* 
 */
Object* Object_Manager::FindObject(std::string objectName) {
    for (Object* object : object_manager->objects) {
        if (objectName.compare(object->GetName()) == 0)
            return object;
    }

    return nullptr;
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
        std::string template_name = preset.Read_Object_Template_Name("object_" + std::to_string(object_num));
        if (template_name.compare("") == 0) break;

          // Constructing the object 
        Object* object = new Object(template_name);
        object->SetName(object_name);
        object->SetTemplateName(template_name);
          // Reading in the objects position
        glm::vec3 position = preset.Read_Object_Position("object_" + std::to_string(object_num));
        glm::vec3 scale = preset.Read_Object_Scale("object_" + std::to_string(object_num));
        Transform* transform = object->GetComponent<Transform>();
        transform->SetPosition(position);
        transform->SetStartPosition(position);
        transform->SetScale(scale);
        Behavior* behavior = object->GetComponent<Behavior>();
        behavior->SetupClassesForLua();

          // Adding the object to the manager
        AddObject(object);

        ++object_num;
    }
}

/**
 * @brief Checks if the name of the given object is already being used. If it is
 *        being used it applies a number to the back.
 * 
 * @param objectName 
 * @param id 
 * @return std::string 
 */
std::string Object_Manager::CheckName(std::string objectName, int id) {
      // Checking if the name matches any other objects
    int objWithName = 0;
    for (Object* objToCheck : object_manager->objects) {
        if (id != -1 && objToCheck->GetId() == id) continue;
        if (objToCheck->GetName().find(objectName) != std::string::npos)
            ++objWithName;
    }

      // Updating the name
    if (objWithName > 0)
        return objectName + "_" + std::to_string(objWithName);
    
    return objectName;
}

/**
 * @brief Removes an object from the object_manager
 * 
 * @param id id of object to remove
 * @return void
 */
void Object_Manager::RemoveObject(int id) {
    if (id >= (int)object_manager->objects.size()) return;
    Object* objectToDelete = object_manager->objects[id];

      // Moves all the objects to the right of one being deleted to the left
    unsigned offset = 0;
    for (unsigned objectNum = id + 1; objectNum < object_manager->objects.size(); ++objectNum) {
        Object* objectToSwitch = object_manager->objects[objectNum];
        object_manager->objects[id + offset] = objectToSwitch;
        objectToSwitch->SetId(id + offset++);
    }

      // Deleting the object
    delete objectToDelete;
    objectToDelete = nullptr;
    object_manager->objects.pop_back();
}

/**
 * @brief Gives all of the object data to writer for output to file
 * 
 * @param writer
 * @return void
 */
void Object_Manager::Write(File_Writer& writer) {
    for (Object* object : object_manager->objects) {
        writer.Write_Object_Data(object);
    }
}
