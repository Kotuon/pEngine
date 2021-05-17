
#include "component.hpp"

Component::Component(CType type_) : type(type_) {}

void Component::SetParent(Object* object) { parent = object; }

Object* Component::GetParent() const { return parent; }

CType Component::GetCType() const { return type; }