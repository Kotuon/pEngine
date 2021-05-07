
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <vector>

using namespace std;

class System;
class Engine {
    public:
        static void Init();
        static void Update(float dt);
        static void Shutdown();
    private:
        vector<System*> systems;
};

#endif