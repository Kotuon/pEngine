
#ifndef ENGINE_HPP
#define ENGINE_HPP

using namespace std;

class System;
class Engine {
    public:
        static void Initialize();
        static void Update(float dt);
        static void Shutdown();
    private:
        bool isRunning;
};

#endif