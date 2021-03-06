/**
 * @file transform.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Engine includes //
#include "transform.hpp"

/**
 * @brief Creates Transform object with default values
 * 
 */
Transform::Transform() : Component(CType::CTransform), 
    position(glm::vec3(0.f, 0.f, 0.f)), scale(glm::vec3(1.f, 1.f, 1.f)), rotation(glm::vec3(0.f, 0.f, 0.f)) {}

/**
 * @brief Copy constructor
 * 
 * @param other 
 */
Transform::Transform(const Transform& other) : Component(CType::CTransform) { 
    *this = other;
}

/**
 * @brief Creates Transform object using file
 * 
 * @param reader File to use for making Transform object
 */
Transform::Transform(File_Reader& reader) : Component(CType::CTransform), 
    position(glm::vec3(0.f, 0.f, 0.f)), scale(glm::vec3(1.f, 1.f, 1.f)), rotation(glm::vec3(0.f, 0.f, 0.f)) {
    Read(reader);
}

/**
 * @brief Clones current Transform object
 * 
 * @return Transform* Cloned Transform
 */
Transform* Transform::Clone() const {
    return new Transform(*this);
}

/**
 * @brief Sets position of object
 * 
 * @param pos 
 */
void Transform::SetPosition(glm::vec3 pos) { position = pos; }

/**
 * @brief Returns position of object
 * 
 * @return glm::vec3 
 */
glm::vec3 Transform::GetPosition() const { return position; }

/**
 * @brief Returns position reference of object
 * 
 * @return glm::vec3& 
 */
glm::vec3& Transform::GetPositionRef() { return position; }

/**
 * @brief Sets old position of object
 * 
 * @param oldPos 
 */
void Transform::SetOldPosition(glm::vec3 oldPos) { oldPosition = oldPos; }

/**
 * @brief Returns old position of object
 * 
 * @return glm::vec3 
 */
glm::vec3 Transform::GetOldPosition() const { return oldPosition; }

/**
 * @brief Sets scale of object
 * 
 * @param sca 
 */
void Transform::SetScale(glm::vec3 sca) { scale = sca; }

/**
 * @brief Returns scale of object
 * 
 * @return glm::vec3 
 */
glm::vec3 Transform::GetScale() const { return scale; }

/**
 * @brief Returns scale reference of object
 * 
 * @return glm::vec3& 
 */
glm::vec3& Transform::GetScaleRef() { return scale; }

/**
 * @brief Sets rotation of object
 * 
 * @param rot 
 */
void Transform::SetRotation(glm::vec3 rot) { rotation = rot; }

/**
 * @brief Returns rotation of object
 * 
 * @return float 
 */
glm::vec3 Transform::GetRotation() const { return rotation; }

/**
 * @brief Returns rotation reference of object
 * 
 * @return glm::vec3& 
 */
glm::vec3& Transform::GetRotationRef() { return rotation; }

/**
 * @brief Sets the start position of the object
 * 
 * @param startPosition_ 
 */
void Transform::SetStartPosition(glm::vec3 startPosition_) { startPosition = startPosition_; }

/**
 * @brief Returns the saved start position of the object
 * 
 * @return glm::vec3 
 */
glm::vec3 Transform::GetStartPosition() const { return startPosition; }

/**
 * @brief Returns a reference to the start position of the object
 * 
 * @return glm::vec3& 
 */
glm::vec3& Transform::GetStartPositionRef() { return startPosition; }

/**
 * @brief Reads data for Transform object from file
 * 
 * @param reader File to read from
 */
void Transform::Read(File_Reader&) {
    //SetRotation(reader.Read_Float("rotation"));
}

/**
 * @brief Gives transform data to writer object
 * 
 * @param writer 
 */
void Transform::Write(File_Writer& writer) {
    writer.Write_Vec3("rotation", rotation);
}

/**
 * @brief Gets the CType of Transform (used in Object::GetComponent<>())
 * 
 * @return CType 
 */
CType Transform::GetCType() {
    return CType::CTransform;
}