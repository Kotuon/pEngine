/**
 * @file behavior_manager.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#ifndef BEHAVIOR_MANAGER_HPP
#define BEHAVIOR_MANAGER_HPP

// std includes //
#include <vector>
#include <unordered_map>
#include <functional>

// Engine includes //
#include "object.hpp"
#include "behavior.hpp"

using namespace std;

/*! Behavior_Manager class */
class Behavior_Manager {
    public: // Public functions
        static bool Initialize();
        static void Shutdown();
        static void UseBehaviors(Object* object, vector<int>& behaviorList);
        static int FindBehaviorIndex(string behaviorName);
    private: // Behavior functions
        void GravityBetweenObjects(Object* object);
        void Idle(Object* object);
    private: // Helper functions
        static vec3 ApplyForce(vec3 direction, Behavior* behavior);
        static void LaunchObject(vec3 direction, Object* object);
    private: // Member variables
        vector<function<void (Object*)>> behaviorFunctions; //!< List of function pointers for behaviors

    const unordered_map<string, int> ListOfBehaviors { //!< List of the possible behaviors
        { "GravityBetweenObjects", 0 },
        { "Idle", 1 }
    };
};

#endif