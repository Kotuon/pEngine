
// Engine includes //
#include "behavior.hpp"

Behavior::Behavior() : Component(CType::CBehavior) {}

Behavior::Behavior(const Behavior& other) : Component(CType::CBehavior) {
    *this = other;
}

Behavior::Behavior(File_Reader& reader) : Component(CType::CBehavior) {
    Read(reader);
}

Behavior* Behavior::Clone() const {
    return new Behavior(*this);
}

void Behavior::Update() {
    
}

void Behavior::Read(File_Reader& reader) {

}

CType Behavior::GetCType() {
    return CType::CBehavior;
}