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

#pragma once
#ifndef PHYSICS_HPP
#define PHYSICS_HPP

// std includes //
#include <vec3.hpp>

// Engine includes //
#include "component.hpp"
#include "file_reader.hpp"
#include "file_writer.hpp"

/*! Physics class */
class Physics : public Component {
    public:
        Physics();
        Physics(const Physics& other);
        Physics(File_Reader& reader);
        Physics* Clone() const;

        void SetAcceleration(glm::vec3 accel);
        glm::vec3 GetAcceleration() const;
        glm::vec3& GetAccelerationRef();

        void SetForces(glm::vec3 force);
        void AddForce(glm::vec3 force);
        glm::vec3 GetForces() const;
        glm::vec3& GetForcesRef();
        void ApplyForce(glm::vec3 direction, float power);

        void SetVelocity(glm::vec3 vel);
        glm::vec3 GetVelocity() const;
        glm::vec3& GetVelocityRef();

        void SetRotationalVelocity(glm::vec3 rotVel);
        glm::vec3 GetRotationalVelocity() const;
        glm::vec3& GetRotationalVelocityRef();

        void SetMass(float ma);
        float GetMass() const;
        float& GetMassRef();

        void Update();

        void UpdateGravity();

        void Read(File_Reader& reader);
        void Write(File_Writer& writer);

        static CType GetCType();
    private:
        glm::vec3 acceleration;        //!< Acceleration of object
        glm::vec3 forces;              //!< Forces acting on object (reset at end of each update)
        glm::vec3 velocity;            //!< Velocity of object
        glm::vec3 initialVelocity;     //!< Starting velocity
        glm::vec3 initialAcceleration; //!< Starting acceleration
        glm::vec3 rotationalVelocity;  //!< How fast is the object rotating
        float mass;                    //!< Mass of object
};

#endif