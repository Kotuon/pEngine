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

// Library includes //
#include <glm.hpp>
#include <vec3.hpp>

// Engine includes //
#include "behavior_manager.hpp"
#include "trace.hpp"
#include "physics.hpp"
#include "transform.hpp"
#include "random.hpp"

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

    function<void (Object*)> idleFunc = bind(&Behavior_Manager::Idle, 
        behavior_manager, placeholders::_1);
    behavior_manager->behaviorFunctions.emplace_back(idleFunc);

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
        if (behavior == -1) continue;

        behavior_manager->behaviorFunctions[behavior](object);
    }
}

/**
 * @brief Finds the index of a behavior
 * 
 * @param behaviorName Name of the behavior to be found
 * @return int 
 */
int Behavior_Manager::FindBehaviorIndex(string behaviorName) {
      // Finding index of behavior
    auto result = behavior_manager->ListOfBehaviors.find(behaviorName);

      // Returning if found or -1 if not found
    if (result == behavior_manager->ListOfBehaviors.end()) return -1;
    return result->second;
}

/**
 * @brief Calls Physics function to calculate gravity between all the objects
 * 
 * @param object Object to set gravity for
 */
void Behavior_Manager::GravityBetweenObjects(Object* object) {
    Physics* object_physics = object->GetComponent<Physics>();
    object_physics->UpdateGravity();
}

/**
 * @brief Particles idle by moving in a radius around their start position
 * 
 * @param object 
 */
void Behavior_Manager::Idle(Object* object) {
    Behavior* behavior = object->GetComponent<Behavior>();
    Physics* physics = object->GetComponent<Physics>();
    Transform* transform = object->GetComponent<Transform>();

      // Check if the object is not moving
    if (physics->GetVelocity() == vec3(0.f, 0.f, 0.f)) {
        LaunchObject(normalize(Random::random_vec3(-100.f, 100.f)), object);
        return;
    }

      // Check if the object is in its idle area
    // float distanceFromStart = distance(transform->GetPosition(), behavior->GetStartPos());
    // float combinedRadius = transform->GetScale().x + behavior->GetIdleRadius();
    // if (distanceFromStart > combinedRadius) {
    //     LaunchObject(normalize(behavior->GetStartPos() - transform->GetPosition()),
    //         object);
    //     return;
    // }

    // if (length(physics->GetVelocity()) < behavior->GetMaxVelocity()) {
    //     LaunchObject(normalize(physics->GetVelocity()), object);
    // }
}

/**
 * @brief Applies force in the given direction
 * 
 * @param direction Direction to apply force in
 * @param behavior Behavior of the object
 * @return vec3 
 */
vec3 Behavior_Manager::ApplyForce(vec3 direction, Behavior*) {
    // direction = normalize(direction + behavior->GetDirVariation());
    // direction *= (behavior->GetPushForce() + behavior->GetPushVariation());

    return direction;
}

/**
 * @brief Launches object in the given direction
 * 
 * @param direction Direction to launch
 * @param object Object to launch
 * @return void
 */
void Behavior_Manager::LaunchObject(vec3 direction, Object* object) {
    Behavior* behavior = object->GetComponent<Behavior>();
    Physics* physics = object->GetComponent<Physics>();

    vec3 forceToApply = ApplyForce(direction, behavior);

    physics->AddForce(forceToApply);
}