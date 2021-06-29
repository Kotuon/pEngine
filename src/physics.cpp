/**
 * @file physics.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// std includes //
#include <cmath>

// Library includes //
#include <glm.hpp>

// Engine includes
  // System
#include "engine.hpp"
  // Object
#include "object_manager.hpp"
#include "object.hpp"
  // Component
#include "physics.hpp"
#include "transform.hpp"

/**
 * @brief Creates Physics object with default values
 * 
 */
Physics::Physics() : Component(CType::CPhysics),
    acceleration(vec3(0.f, 0.f, 0.f)), forces(vec3(0.f, 0.f, 0.f)), 
    velocity(vec3(0.f, 0.f, 0.f)), mass(1.f) {}

/**
 * @brief Copy constructor
 * 
 * @param other Physics object to be copied
 */
Physics::Physics(const Physics& other) : Component(CType::CPhysics) {
    *this = other;
}

/**
 * @brief Creates Physics object using file
 * 
 * @param reader File to use for making physics object
 */
Physics::Physics(File_Reader& reader) : Component(CType::CPhysics),
    acceleration(vec3(0.f, 0.f, 0.f)), forces(vec3(0.f, 0.f, 0.f)), 
    velocity(vec3(0.f, 0.f, 0.f)), mass(1.f) {
    Read(reader);
}

/**
 * @brief Clone Physics object
 * 
 * @return Physics* Cloned Physics object
 */
Physics* Physics::Clone() const {
    return new Physics(*this);
}

/**
 * @brief Sets acceleration of object
 * 
 * @param accel 
 */
void Physics::SetAcceleration(vec3 accel) { acceleration = accel; }

/**
 * @brief Returns acceleration of object
 * 
 * @return vec3 
 */
vec3 Physics::GetAcceleration() const { return acceleration; }

/**
 * @brief Sets forces acting on object
 * 
 * @param force 
 */
void Physics::SetForces(vec3 force) { forces = force; }

/**
 * @brief Adds a force to the current forces acting on the object
 * 
 * @param force 
 */
void Physics::AddForce(vec3 force) { forces += force; }

/**
 * @brief Returns the forces acting on the object
 * 
 * @return vec3 
 */
vec3 Physics::GetForces() const { return forces; }

/**
 * @brief Sets the velocity of the object
 * 
 * @param vel 
 */
void Physics::SetVelocity(vec3 vel) { velocity = vel; }

/**
 * @brief Returns the current velocity of the object
 * 
 * @return vec3 
 */
vec3 Physics::GetVelocity() const { return velocity; }

/**
 * @brief Sets the mass of the object
 * 
 * @param ma 
 */
void Physics::SetMass(float ma) { mass = ma; }

/**
 * @brief Returns the mass of the object
 * 
 * @return float 
 */
float Physics::GetMass() const { return mass; }

/**
 * @brief Updates the physics of the object
 * 
 */
void Physics::Update() {
      // Finding the acceleration of the object using F=ma
    acceleration = forces / mass;

      // Updating velocity
    vec3 oldVel = velocity;
    velocity += (acceleration * Engine::GetDt());

      // Updating position
    Transform* transform = GetParent()->GetComponent<Transform>();
    vec3 position = transform->GetPosition();
    transform->SetOldPosition(position);
    position = (velocity * Engine::GetDt()) + position;
    transform->SetPosition(position);

      // Resetting the forces acting on the object
    forces = vec3(0.f, 0.f, 0.f);
}

/**
 * @brief Calculates the gravitational pull each object has on each other
 * 
 */
void Physics::UpdateGravity() {
      // Gets the needed components for the current object
    Object* object = GetParent();
    Transform* transform = object->GetComponent<Transform>();
    Physics* physics = object->GetComponent<Physics>();
    vec3 position = transform->GetPosition();

      // For each object
    for (unsigned i = 0; i < Object_Manager::GetSize(); ++i) {
        if (i == object->GetId()) continue;
          // Gets needed components for the object being checked
        Object* other = Object_Manager::FindObject(i);
        Physics* otherPhysics = other->GetComponent<Physics>();
        Transform* otherTransform = other->GetComponent<Transform>();
        vec3 otherPosition = otherTransform->GetPosition();
          // Finding the distance between the objects
        double distance = sqrt(pow(double(otherPosition.x - position.x), 2.0) + 
            pow(double(otherPosition.y - position.y), 2.0) +
            pow(double(otherPosition.z - position.z), 2.0));
          // Calculating the force the objects apply on each other
        double magnitude = Engine::GetGravConst() * ((physics->mass * otherPhysics->mass)) / pow(distance, 2.0);
          // Getting the direction (normalized)
        vec3 direction = otherPosition - position;
        vec3 normDirection = normalize(direction);
          // Applying gravitational force to normalized direction
        vec3 force = normDirection * float(magnitude);
          // Adding the gravitational force to the forces on object
        physics->AddForce(force);
    }
}

/**
 * @brief Reads data for Physics object from file
 * 
 * @param reader File to be read from
 */
void Physics::Read(File_Reader& reader) {
    SetAcceleration(reader.Read_Vec3("acceleration"));
    SetVelocity(reader.Read_Vec3("velocity"));
    SetMass(reader.Read_Float("mass"));
}

/**
 * @brief Gets the CType of Physics (used in Object::GetComponent<>())
 * 
 * @return CType 
 */
CType Physics::GetCType() {
    return CType::CPhysics;
}