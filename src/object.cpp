
#include "object.hpp"
#include "transform.hpp"
#include "physics.hpp"
#include "model.hpp"
#include "file_reader.hpp"

Object::Object() {}

Object::Object(const Object& other) {
    SetName(other.GetName());
    Transform* transform = other.GetComponent<Transform>(CType::CTransform);
    if (transform) {
        Transform* newTransform = new Transform(*transform);
        AddComponent(newTransform);
    }

    Model* model = other.GetComponent<Model>(CType::CModel);
    if (model) {
        Model* newModel = new Model(*model);
        AddComponent(newModel);
    }

    Physics* physics = other.GetComponent<Physics>(CType::CPhysics);
    if (physics) {
        Physics* newPhysics = new Physics(*physics);
        AddComponent(newPhysics);
    }
}

Object::Object(string filename) {
    ReadObject(filename);
}

Object* Object::Clone() const {
    return new Object(*this);
}

void Object::Update() {
    Physics* physics = GetComponent<Physics>(CType::CPhysics);
    physics->Update();
}

void Object::AddComponent(Component* component) {
    component->SetParent(this);
    components.emplace(component->GetCType(), component);
}

void Object::SetId(unsigned id_) { id = id_; }
unsigned Object::GetId() const { return id; }

void Object::SetName(string name_) { name = name_; }
string Object::GetName() const { return name; }

void Object::ReadObject(string objectFilename) {
    File_Reader object_reader(objectFilename);

    SetName(object_reader.Read_String("name"));
    
    Model* object_model = new Model(object_reader);
    AddComponent(object_model);
    
    Transform* object_transform = new Transform(object_reader);
    AddComponent(object_transform);
    
    Physics* object_physics = new Physics(object_reader);
    AddComponent(object_physics);
}