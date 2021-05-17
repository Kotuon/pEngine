
#include "transform.hpp"

Transform::Transform() : Component(CType::CTransform), 
    position(vec3(0.f, 0.f, 0.f)), scale(vec3(0.f, 0.f, 0.f)), rotation(0.f) {}

void Transform::SetPosition(vec3 pos) { position = pos; }

vec3 Transform::GetPosition() const { return position; }

void Transform::SetScale(vec3 sca) { scale = sca; }

vec3 Transform::GetScale() const { return scale; }

void Transform::SetRotation(float rot) { rotation = rot; }

GLfloat Transform::GetRotation() const { return rotation; }
