
#include "transform.hpp"

Transform::Transform() : Component(CType::CTransform), 
    position(vec3(0.f, 0.f, 0.f)), scale(vec3(1.f, 1.f, 1.f)), rotation(0.f) {}

Transform::Transform(const Transform& other) : Component(CType::CTransform) { 
    *this = other;
}

Transform::Transform(File_Reader& reader) : Component(CType::CTransform), 
    position(vec3(0.f, 0.f, 0.f)), scale(vec3(1.f, 1.f, 1.f)), rotation(0.f) {
    Read(reader);
}

Transform* Transform::Clone() const {
    return new Transform(*this);
}

void Transform::SetPosition(vec3 pos) { position = pos; }
vec3 Transform::GetPosition() const { return position; }

void Transform::SetOldPosition(vec3 oldPos) { oldPosition = oldPos; }
vec3 Transform::GetOldPosition() const { return oldPosition; }

void Transform::SetScale(vec3 sca) { scale = sca; }
vec3 Transform::GetScale() const { return scale; }

void Transform::SetRotation(float rot) { rotation = rot; }
float Transform::GetRotation() const { return rotation; }

void Transform::Read(File_Reader& reader) {
    SetScale(reader.Read_Vec3("scale"));
    SetRotation(reader.Read_Float("rotation"));
}