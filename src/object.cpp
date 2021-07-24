/**
 * @file object.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Engine includes //
  // Object //
#include "object.hpp"
  // Component //
#include "behavior.hpp"
#include "model.hpp"
#include "object_manager.hpp"
#include "physics.hpp"
#include "transform.hpp"
  // Misc //
#include "file_reader.hpp"

/**
 * @brief Default constructor
 * 
 */
Object::Object() : id(-1) {}

/**
 * @brief Copy constructor
 * 
 * @param other Object to be copied
 */
Object::Object(const Object& other) {
    SetName(other.GetName());

      // Copying Behavior component
    Behavior* behavior = other.GetComponent<Behavior>();
    if (behavior) {
        Behavior* newBehavior = new Behavior(*behavior);
        AddComponent(newBehavior);
    }

      // Copying Model component
    Model* model = other.GetComponent<Model>();
    if (model) {
        Model* newModel = new Model(*model);
        AddComponent(newModel);
    }

      // Copying Physics component
    Physics* physics = other.GetComponent<Physics>();
    if (physics) {
        Physics* newPhysics = new Physics(*physics);
        AddComponent(newPhysics);
    }

      // Copying transform component
    Transform* transform = other.GetComponent<Transform>();
    if (transform) {
        Transform* newTransform = new Transform(*transform);
        AddComponent(newTransform);
    }
}

/**
 * @brief Creating object from a file
 * 
 * @param filename Name of file used to create object
 */
Object::Object(std::string filename) {
    Read(filename);
}

/**
 * @brief Clones this object
 * 
 * @return Object* 
 */
Object* Object::Clone() const {
    return new Object(*this);
}

/**
 * @brief Updates object (only physics for now)
 * 
 */
void Object::Update() {
    Behavior* behavior = GetComponent<Behavior>();
    if (behavior)
        behavior->Update();
    Physics* physics = GetComponent<Physics>();
    if (physics)
        physics->Update();
}

/**
 * @brief Adds component to object. Only one of each type of component
 * 
 * @param component Component to be added
 */
void Object::AddComponent(Component* component) {
    component->SetParent(this);
    components.emplace(component->GetCType(), component);
}

/**
 * @brief Sets the id of object
 * 
 * @param id_ Position in Object_Manager
 */
void Object::SetId(int id_) { id = id_; }

/**
 * @brief Returns the id of object
 * 
 * @return unsigned Position in Object_Manager
 */
int Object::GetId() const { return id; }

/**
 * @brief Sets name of object
 * 
 * @param name_ Name of object
 */
void Object::SetName(std::string name_) {
    name = Object_Manager::CheckName(name_, id);
}

/**
 * @brief Returns name of object
 * 
 * @return string Name of object
 */
std::string Object::GetName() const { return name; }

/**
 * @brief Reads object from file. This includes the components of an object
 * 
 * @param objectFilename 
 */
void Object::Read(std::string objectFilename) {
      // Getting data from file
    File_Reader object_reader(objectFilename);

    SetName(object_reader.Read_String("name"));
    filename = objectFilename;

      // Reading Behavior component form file
    Behavior* object_behavior = new Behavior(object_reader);
    AddComponent(object_behavior);

      // Reading Model component from file
    Model* object_model = new Model(object_reader);
    AddComponent(object_model);
    
      // Reading Physics component from file
    Physics* object_physics = new Physics(object_reader);
    AddComponent(object_physics);
    
      // Reading Transform component from file
    Transform* object_transform = new Transform(object_reader);
    AddComponent(object_transform);
}

void Object::Write() {
    File_Writer object_writer;
    object_writer.Write_String("name", name);

    Model* object_model = GetComponent<Model>();
    if (object_model) object_model->Write(object_writer);

    Transform* object_transform = GetComponent<Transform>();
    if (object_transform) object_transform->Write(object_writer);

    Physics* object_physics = GetComponent<Physics>();
    if (object_physics) object_physics->Write(object_writer);

    Behavior* object_behavior = GetComponent<Behavior>();
    if (object_behavior) object_behavior->Write(object_writer);

    object_writer.Write_File(std::string(name + ".json"));
}

std::unordered_map<CType, Component*> Object::GetComponentList() {
    return components;
}