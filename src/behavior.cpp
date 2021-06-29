/**
 * @file behavior.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Engine includes //
#include "behavior_manager.hpp"
#include "behavior.hpp"
#include "random.hpp"

/**
 * @brief Creates an empty Behavior object
 * 
 */
Behavior::Behavior() : Component(CType::CBehavior) {}

/**
 * @brief Copy constructor
 * 
 * @param other Behavior object to copy
 */
Behavior::Behavior(const Behavior& other) : Component(CType::CBehavior) {
    *this = other;
}

/**
 * @brief Creates Behavior object using file
 * 
 * @param reader Data from file
 */
Behavior::Behavior(File_Reader& reader) : Component(CType::CBehavior) {
    Read(reader);
}

/**
 * @brief Clones current Behavior object
 * 
 * @return Behavior* 
 */
Behavior* Behavior::Clone() const {
    return new Behavior(*this);
}

/**
 * @brief Update for Behavior object. Calls Behavior manager giving list of its
 *        behaviors
 * 
 */
void Behavior::Update() {
    Behavior_Manager::UseBehaviors(GetParent(), behaviorList);
}

/**
 * @brief Reads in the behaviors to be used
 * 
 * @param reader Data from file
 */
void Behavior::Read(File_Reader& reader) {
    unsigned behavior_num = 0;

    while (true) {
    string behavior_name = reader.Read_Behavior_Name("behavior_" + to_string(behavior_num));
        if (behavior_name.compare("") == 0) break;

        behaviorList.emplace_back(Behavior_Manager::FindBehaviorIndex(behavior_name));
        ++behavior_num;
    }

    maxVelocity = reader.Read_Float("maxVelocity");
    idleRadius = reader.Read_Float("idleRadius");
    pushForce = reader.Read_Float("pushForce");
    dirVariation = reader.Read_Float("dirVariation");
    pushVariation = reader.Read_Float("pushVariation");
}

/**
 * @brief Sets the start position of the object
 * 
 * @param startPos_ Start position of the object
 */
void Behavior::SetStartPos(vec3 startPos_) {
    startPos = startPos_;
}

/**
 * @brief Returns the start position of the object
 * 
 * @return vec3 
 */
vec3 Behavior::GetStartPos() const {
    return startPos;
}

float Behavior::GetMaxVelocity() const {
    return maxVelocity;
}

float Behavior::GetIdleRadius() const {
    return idleRadius;
}

/**
 * @brief Returns strength of force
 * 
 * @return float 
 */
float Behavior::GetPushForce() const {
    return pushForce;
}

/**
 * @brief Returns the variation of an object's direction
 * 
 * @return float 
 */
float Behavior::GetDirVariation() const {
    return Random::random_float(-dirVariation, dirVariation);
}

/**
 * @brief Returns the variation of an object's push force
 * 
 * @return float 
 */
float Behavior::GetPushVariation() const {
    return Random::random_float(-pushVariation, pushVariation);
}

/**
 * @brief Gets the CType of Behavior (used in Object::GetComponent<>())
 * 
 * @return CType 
 */
CType Behavior::GetCType() {
    return CType::CBehavior;
}