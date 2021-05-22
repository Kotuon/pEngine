
#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <vec3.hpp>

#include "component.hpp"

class Physics : public Component {
    public:
    private:
        vec3 acceleration;
        vec3 forces;
        vec3 veloicty;
};

#endif