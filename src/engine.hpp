
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
        static float GetDt();
    private:
        bool isRunning;
        float deltaTime;
        float accumulator;
        float time;
        const float dt = 0.01f;
        chrono::steady_clock::time_point currentTime;
        chrono::steady_clock::time_point newTime;
        chrono::steady_clock::duration timeTaken;
};

#endif