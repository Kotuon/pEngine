/**
 * @file behavior_manager.cpp
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
#include "trace.hpp"
#include "physics.hpp"

static Behavior_Manager* behavior_manager = nullptr; //!< Behavior_Manager object

/**
 * @brief Initializes the behavior_manager and fills list with function pointers
 * 
 * @return true 
 * @return false 
 */
bool Behavior_Manager::Initialize() {
    behavior_manager = new Behavior_Manager;
    if (!behavior_manager) {
        Trace::Message("Behavior Manager was not initialized.\n");
        return false;
    }

    function<void (Object*)> gravFunc = bind(&Behavior_Manager::GravityBetweenObjects, 
        behavior_manager, placeholders::_1);
    behavior_manager->behaviorFunctions.emplace_back(gravFunc);
    return true;
}

/**
 * @brief Shutdown the behavior_manager
 * 
 * @return void
 */
void Behavior_Manager::Shutdown() {
    if (!behavior_manager) return;

      // Delete behavior_manager object
    delete behavior_manager;
    behavior_manager = nullptr;
}

/**
 * @brief Uses the list of behaviors on the given object
 * 
 * @param object       Object to be used
 * @param behaviorList List of behaviors to use
 * @return void
 */
void Behavior_Manager::UseBehaviors(Object* object, vector<int>& behaviorList) {
    for (int behavior : behaviorList) {
        behavior_manager->behaviorFunctions[behavior](object);
    }
}

/**
 * @brief Calls Physics function to calculate gravity between all the objects
 * 
 */
void Behavior_Manager::GravityBetweenObjects(Object*) {
    Physics::UpdateGravity();
}