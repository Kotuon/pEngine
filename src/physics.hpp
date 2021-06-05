/**
 * @file physics.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef PHYSICS_HPP
#define PHYSICS_HPP

// std includes //
#include <vec3.hpp>

// Engine includes //
#include "component.hpp"
#include "file_reader.hpp"

using namespace glm;

/*! Physics class */
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

        static CType GetCType();
    private:
        vec3 acceleration; //!< Acceleration of object
        vec3 forces;       //!< Forces acting on object (reset at end of each update)
        vec3 velocity;     //!< Velocity of object
        float mass;        //!< Mass of object
};

#endif