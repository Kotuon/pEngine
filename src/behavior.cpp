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

}

/**
 * @brief Gets the CType of Behavior (used in Object::GetComponent<>())
 * 
 * @return CType 
 */
CType Behavior::GetCType() {
    return CType::CBehavior;
}