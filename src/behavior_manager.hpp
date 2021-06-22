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

#ifndef BEHAVIOR_MANAGER_HPP
#define BEHAVIOR_MANAGER_HPP

// std includes //
#include <vector>
#include <functional>

// Engine includes //
#include "object.hpp"

using namespace std;

/*! Behavior_Manager class */
class Behavior_Manager {
    public:
        static bool Initialize();
        static void Shutdown();
        static void UseBehaviors(Object* object, vector<int>& behaviorList);
    private:
        void GravityBetweenObjects(Object*);
    private:
        vector<function<void (Object*)>> behaviorFunctions; //!< List of function pointers for behaviors
};

#endif