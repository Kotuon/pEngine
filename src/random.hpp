
#ifndef RANDOM_HPP
#define RANDOM_HPP

// std includes //
#include <random>

// Library includes //
#include <vec3.hpp>

using namespace std;
using namespace glm;

class Random {
    public:
        static bool Initialize();
        static void Shutdown();
        static vec3 random_vec3(float low, float high);
        static float random_float(float low, float high);
    private:
    random_device rd;
};

#endif