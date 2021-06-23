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
#include "physics.hpp"
#include "transform.hpp"
  // Misc //
#include "file_reader.hpp"

/**
 * @brief Default constructor
 * 
 */
Object::Object() {}

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
Object::Object(string filename) {
    ReadObject(filename);
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
    behavior->Update();
    Physics* physics = GetComponent<Physics>();
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
void Object::SetId(unsigned id_) { id = id_; }

/**
 * @brief Returns the id of object
 * 
 * @return unsigned Position in Object_Manager
 */
unsigned Object::GetId() const { return id; }

/**
 * @brief Sets name of object
 * 
 * @param name_ Name of object
 */
void Object::SetName(string name_) { name = name_; }

/**
 * @brief Returns name of object
 * 
 * @return string Name of object
 */
string Object::GetName() const { return name; }

/**
 * @brief Reads object from file. This includes the components of an object
 * 
 * @param objectFilename 
 */
void Object::ReadObject(string objectFilename) {
      // Getting data from file
    File_Reader object_reader(objectFilename);

    SetName(object_reader.Read_String("name"));

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