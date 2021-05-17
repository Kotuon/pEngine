
#include "object.hpp"

void Object::Update(float) {

}

void Object::AddComponent(Component* component) {
    component->SetParent(this);
    components.emplace(component->GetCType(), component);
}

void Object::SetId(unsigned id_) { id = id_; }

unsigned Object::GetId() const { return id; }