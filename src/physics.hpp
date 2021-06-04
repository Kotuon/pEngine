
#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <vec3.hpp>

#include "component.hpp"
#include "file_reader.hpp"

using namespace glm;

class Physics : public Component {
    public:
        Physics();
        Physics(const Physics& other);
        Physics(File_Reader& reader);
        Physics* Clone() const;

        void SetAcceleration(vec3 accel);
        vec3 GetAcceleration() const;

        void SetForces(vec3 force);
        void AddForce(vec3 force);
        vec3 GetForces() const;

        void SetVelocity(vec3 vel);
        vec3 GetVelocity() const;

        void SetMass(float ma);
        float GetMass() const;

        void Update();

        static void UpdateGravity();

        void Read(File_Reader& reader);
    private:
        vec3 acceleration;
        vec3 forces;
        vec3 velocity;
        float mass;
};

#endif