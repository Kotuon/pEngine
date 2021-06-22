
#ifndef BEHAVIOR_MANAGER_HPP
#define BEHAVIOR_MANAGER_HPP

// std includes //
#include <vector>
#include <functional>

// Engine includes //
#include "object.hpp"

using namespace std;

class Behavior_Manager {
    public:
        static bool Initialize();
        static void Shutdown();
        static void UseBehaviors(Object* object, vector<int>& behaviorList);
    private:
        void GravityBetweenObjects(Object*);
    private:
        vector<function<void (Object*)>> behaviorFunctions;
};

#endif