
#include <cmath>

#include <glm.hpp>

#include "physics.hpp"
#include "engine.hpp"
#include "object.hpp"
#include "transform.hpp"
#include "object_manager.hpp"

Physics::Physics() : Component(CType::CPhysics),
    acceleration(vec3(0.f, 0.f, 0.f)), forces(vec3(0.f, 0.f, 0.f)), 
    velocity(vec3(0.f, 0.f, 0.f)), mass(1.f) {}

Physics::Physics(const Physics& other) : Component(CType::CPhysics) {
    *this = other;
}

Physics* Physics::Clone() const {
    return new Physics(*this);
}

void Physics::SetAcceleration(vec3 accel) { acceleration = accel; }
vec3 Physics::GetAcceleration() const { return acceleration; }

void Physics::SetForces(vec3 force) { forces = force; }
void Physics::AddForce(vec3 force) { forces += force; }
vec3 Physics::GetForces() const { return forces; }

void Physics::SetVelocity(vec3 vel) { velocity = vel; }
vec3 Physics::GetVelocity() const { return velocity; }

void Physics::SetMass(float ma) { mass = ma; }
float Physics::GetMass() const { return mass; }

void Physics::Update() {
    acceleration = (forces /** Engine::GetDt()*/) / mass;

    vec3 oldVel = velocity;
    velocity += (acceleration * Engine::GetDt());
    //if (dot(velocity, velocity) > 1.f) velocity = oldVel;

    Transform* transform = GetParent()->GetComponent<Transform>(CType::CTransform);
    vec3 position = transform->GetPosition();
    transform->SetOldPosition(position);
    position = (velocity * Engine::GetDt()) + position;
    transform->SetPosition(position);

    forces = vec3(0.f, 0.f, 0.f);
}

void Physics::UpdateGravity() {
    for (unsigned i = 0; i < Object_Manager::GetSize(); ++i) {
        Object* object = Object_Manager::FindObject(i);
        Transform* transform = object->GetComponent<Transform>(CType::CTransform);
        Physics* physics = object->GetComponent<Physics>(CType::CPhysics);
        vec3 position = transform->GetPosition();

        for (unsigned j = 0; j < Object_Manager::GetSize(); ++j) {
            if (i == j) continue;

            Object* other = Object_Manager::FindObject(j);
            Physics* otherPhysics = other->GetComponent<Physics>(CType::CPhysics);
            Transform* otherTransform = other->GetComponent<Transform>(CType::CTransform);

            vec3 otherPosition = otherTransform->GetPosition();

            double distance = sqrt(pow(double(otherPosition.x - position.x), 2.0) + 
                pow(double(otherPosition.y - position.y), 2.0) +
                pow(double(otherPosition.z - position.z), 2.0));
            double magnitude = physics->G * ((physics->mass * otherPhysics->mass)) / pow(distance, 2.0);

            vec3 direction = otherPosition - position;
            vec3 normDirection = normalize(direction);
            vec3 force = normDirection * float(magnitude);

            physics->AddForce(force);
        }
    }
}