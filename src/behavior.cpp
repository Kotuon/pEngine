/**
 * @file behavior.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Library includes //
#include <glm.hpp>

// Engine includes //
#include "behavior.hpp"
#include "engine.hpp"
#include "object.hpp"
#include "physics.hpp"
#include "random.hpp"
#include "transform.hpp"
#include "vector3_func.hpp"

/**
 * @brief Creates an empty Behavior object
 * 
 */
Behavior::Behavior() : Component(CType::CBehavior) {}

/**
 * @brief Copy constructor
 * 
 * @param other Behavior object to copy
 */
Behavior::Behavior(const Behavior& other) : Component(CType::CBehavior) {
    *this = other;
}

/**
 * @brief Creates Behavior object using file
 * 
 * @param reader Data from file
 */
Behavior::Behavior(File_Reader& reader) : Component(CType::CBehavior) {
    Read(reader);
}

/**
 * @brief Clones current Behavior object
 * 
 * @return Behavior* 
 */
Behavior* Behavior::Clone() const {
    return new Behavior(*this);
}

/**
 * @brief Update for Behavior object. Calls Behavior manager giving list of its
 *        behaviors
 * 
 */
void Behavior::Update() {
    for (sol::state* state : states) {
        (*state)["FixedUpdate"](Engine::GetDt());
    }
}

/**
 * @brief Reads in the behaviors to be used
 * 
 * @param reader Data from file
 */
void Behavior::Read(File_Reader& reader) {
    unsigned behavior_num = 0;

    while (true) {
    std::string behavior_name = reader.Read_Behavior_Name("behavior_" + std::to_string(behavior_num));
        if (behavior_name.compare("") == 0) break;

        scripts.emplace_back(behavior_name);
        ++behavior_num;
    }

    for (std::string& script : scripts) {
        sol::state* state = new sol::state;
        state->open_libraries(sol::lib::base, sol::lib::math, sol::lib::io, sol::lib::string);
        states.emplace_back(state);
    }
}

void Behavior::Write(File_Writer& writer) {
    writer.Write_Behavior_Name(scripts);
}

/**
 * @brief Gets the CType of Behavior (used in Object::GetComponent<>())
 * 
 * @return CType 
 */
CType Behavior::GetCType() {
    return CType::CBehavior;
}

void Behavior::SetupClassesForLua() {
    for (sol::state* state : states) {
        ClassSetup(state);
    }

    for (unsigned i = 0; i < states.size(); ++i) {
        states[i]->script_file(std::string("data/scripts/" + scripts[i]).c_str());
        (*states[i])["Start"]();
    }
}

std::vector<std::string>& Behavior::GetScripts() { return scripts; }

void Behavior::ClassSetup(sol::state* state) {
    Physics* physics = GetParent()->GetComponent<Physics>();
    Transform* transform = GetParent()->GetComponent<Transform>();

    state->set_function("random_vec3", Random::random_vec3);
    state->set_function("random_float", Random::random_float);

    sol::usertype<glm::vec3> vec3_type = state->new_usertype<glm::vec3>("vec3",
        sol::constructors<glm::vec3(float, float, float)>());
    vec3_type["x"] = &glm::vec3::x;
    vec3_type["y"] = &glm::vec3::y;
    vec3_type["z"] = &glm::vec3::z;

    state->set_function("normalize", Vector3_Func::normalize);
    state->set_function("distance", Vector3_Func::distance);
    state->set_function("get_direction", Vector3_Func::get_direction);
    state->set_function("zero_vec3", Vector3_Func::zero_vec3);
    state->set_function("length", Vector3_Func::length);

    state->set("physics", physics);
    sol::usertype<Physics> physics_type = state->new_usertype<Physics>("Physics",
        sol::constructors<Physics(), Physics(const Physics)>());
    physics_type["acceleration"] = sol::property(Physics::GetAccelerationRef, &Physics::SetAcceleration);
    physics_type["forces"] = sol::property(Physics::GetForcesRef, &Physics::SetForces);
    physics_type["velocity"] = sol::property(Physics::GetVelocityRef, &Physics::SetVelocity);
    physics_type.set_function("ApplyForce", &Physics::ApplyForce);
    physics_type.set_function("UpdateGravity", &Physics::UpdateGravity);

    (*state)["transform"] = transform;
    sol::usertype<Transform> transform_type = state->new_usertype<Transform>("Transform",
        sol::constructors<Transform(), Transform(const Transform)>());
    transform_type["position"] = sol::property(Transform::GetPositionRef, &Transform::SetPosition);
    transform_type["rotation"] = sol::property(Transform::GetRotationRef, &Transform::SetRotation);
    transform_type["scale"] = sol::property(Transform::GetScaleRef, &Transform::SetScale);
    transform_type.set("startPosition", sol::property(Transform::GetStartPositionRef, &Transform::SetStartPosition));
}

void Behavior::SwitchScript(unsigned scriptNum, std::string newScriptName) {
    sol::state* state = states[scriptNum];
    delete state;
    state = new sol::state;
    state->open_libraries(sol::lib::base, sol::lib::math, sol::lib::io, sol::lib::string);

    scripts[scriptNum] = newScriptName;
    ClassSetup(state);

    states[scriptNum]->script_file(std::string("data/scripts/" + scripts[scriptNum]).c_str());
    (*states[scriptNum])["Start"]();
}

void Behavior::AddScript(std::string newScriptName) {
    sol::state* state = new sol::state;
    state->open_libraries(sol::lib::base, sol::lib::math, sol::lib::io, sol::lib::string);
    states.emplace_back(state);

    scripts.emplace_back(newScriptName);
    ClassSetup(state);

    states.back()->script_file(std::string("data/scripts/" + scripts.back()).c_str());
    (*states.back())["Start"]();
}