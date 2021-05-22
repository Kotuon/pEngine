
#include "object.hpp"
#include "transform.hpp"
#include "physics.hpp"
#include "model.hpp"

Object::Object() {}

Object::Object(const Object& other) {
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

Object* Object::Clone() const {
    return new Object(*this);
}

void Object::Update(float) {

}

void Object::AddComponent(Component* component) {
    component->SetParent(this);
    components.emplace(component->GetCType(), component);
}

void Object::SetId(unsigned id_) { id = id_; }

unsigned Object::GetId() const { return id; }