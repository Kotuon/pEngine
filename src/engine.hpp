
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <chrono>

using namespace std;

class System;
class Engine {
    public:
        static void Initialize();
        static void Update();
        static void Shutdown();
        static float GetDeltaTime();
    private:
        bool isRunning;
        float deltaTime;
        chrono::steady_clock::time_point startTime;
        chrono::steady_clock::time_point oldStartTime;
};

#endif