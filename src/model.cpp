
#include <cstdio>

#include "model.hpp"
#include "trace.hpp"
#include "object.hpp"
#include "transform.hpp"
#include "model_data_manager.hpp"

Model::Model(GLenum mode_) : Component(CType::CModel), mode(mode_), data(nullptr) {}

Model::Model(const Model& other) : Component(CType::CModel) {
    *this = other;
    data = new Model_Data(*other.data);
}

Model::Model(File_Reader& reader, GLenum mode_) : Component(CType::CModel), mode(mode_), data(nullptr) {
    Read(reader);
}

Model* Model::Clone() const {
    return new Model(*this);
}

void Model::Load(string filename) {
    data = Model_Data_Manager::Get(filename);
}

void Model::Draw() {
    Transform* transform = GetParent()->GetComponent<Transform>();

    vec3 pos = transform->GetPosition();
    vec3 scale = transform->GetScale();
    glTranslatef((GLfloat)pos.x, (GLfloat)pos.y, (GLfloat)pos.z);
    glScalef(scale.x, scale.y, scale.z);
    glRotatef(transform->GetRotation(), 1.f, 1.f, 1.f);

    glBegin(mode);
    data->Draw();
    glEnd();
}

void Model::Read(File_Reader reader) {
    Load(reader.Read_String("modelToLoad"));
}

CType Model::GetCType() {
    return CType::CModel;
}