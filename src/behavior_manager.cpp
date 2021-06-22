
// Engine includes //
#include "behavior_manager.hpp"
#include "trace.hpp"
#include "physics.hpp"

static Behavior_Manager* behavior_manager = nullptr;

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

void Behavior_Manager::Shutdown() {
    if (!behavior_manager) return;

      // Delete behavior_manager object
    delete behavior_manager;
    behavior_manager = nullptr;
}

void Behavior_Manager::UseBehaviors(Object* object, vector<int>& behaviorList) {
    for (int behavior : behaviorList) {
        behavior_manager->behaviorFunctions[behavior](object);
    }
}

void Behavior_Manager::GravityBetweenObjects(Object*) {
    Physics::UpdateGravity();
}