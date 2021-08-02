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
#include "object_manager.hpp"
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
 * @brief Deletes all of the lua states
 * 
 */
Behavior::~Behavior() {
    Clear();
}

/**
 * @brief Update for Behavior object. Calls Behavior manager giving list of its
 *        behaviors
 * 
 */
void Behavior::Update() {
    for (sol::state* state : states) {
        if (!state) continue;
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

      // Reads the name of the lua files
    while (true) {
          // Getting the name of the next lua file
        std::string behavior_name = reader.Read_Behavior_Name("behavior_" + std::to_string(behavior_num));
        if (behavior_name.compare("") == 0) break;
          // Adding lua filename to list
        scripts.emplace_back(behavior_name);
        ++behavior_num;
    }
      // Creating lua state for each of the scripts that were read in
    for (unsigned i = 0; i < scripts.size(); ++i) {
        sol::state* state = new sol::state;
        state->open_libraries(sol::lib::base, sol::lib::math, sol::lib::io, sol::lib::string);
        states.emplace_back(state);
    }
}

/**
 * @brief Gives the names of each lua file to the writer
 * 
 * @param writer 
 */
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

/**
 * @brief Setups up the interface between the engine and the lua files
 * 
 */
void Behavior::SetupClassesForLua() {
    for (sol::state* state : states) {
        ClassSetup(state);
    }

    for (unsigned i = 0; i < states.size(); ++i) {
        states[i]->script_file(std::string("data/scripts/" + scripts[i]).c_str());
        (*states[i])["Start"]();
    }
}

/**
 * @brief Returns list of lua filenames
 * 
 * @return std::vector<std::string>& 
 */
std::vector<std::string>& Behavior::GetScripts() { return scripts; }

/**
 * @brief Sends engine variables and functions to lua
 * 
 * @param state 
 */
void Behavior::ClassSetup(sol::state* state) {
      // Getting objects components
    //Physics* physics = GetParent()->GetComponent<Physics>();
    //Transform* transform = GetParent()->GetComponent<Transform>();

      // Giving lua random functions
    state->set_function("random_vec3", Random::random_vec3);
    state->set_function("random_float", Random::random_float);

      // Giving lua glm::vec3 wrapper class
    sol::usertype<glm::vec3> vec3_type = state->new_usertype<glm::vec3>("vec3",
        sol::constructors<glm::vec3(float, float, float), glm::vec3(float)>());
      // Giving lua glm::vec3 wrapper class variables
    vec3_type.set("x", &glm::vec3::x);
    vec3_type.set("y", &glm::vec3::y);
    vec3_type.set("z", &glm::vec3::z);
      // Giving lua glm::vec3 wrapper class functions
    state->set_function("normalize", Vector3_Func::normalize);
    state->set_function("distance", Vector3_Func::distance);
    state->set_function("get_direction", Vector3_Func::get_direction);
    state->set_function("zero_vec3", Vector3_Func::zero_vec3);
    state->set_function("length", Vector3_Func::length);
    state->set_function("add_float", Vector3_Func::add_float);
    state->set_function("add_vec3", Vector3_Func::add_vec3);

    state->set_function("FindObject", sol::overload(sol::resolve<Object*(int)>(&Object_Manager::FindObject), 
        sol::resolve<Object*(std::string)>(&Object_Manager::FindObject)));

      // Giving lua physics class
    sol::usertype<Physics> physics_type = state->new_usertype<Physics>("Physics",
        sol::constructors<Physics(), Physics(const Physics)>());
      // Giving lua physics class variables
    physics_type.set("acceleration", sol::property(Physics::GetAccelerationRef, &Physics::SetAcceleration));
    physics_type.set("forces",       sol::property(Physics::GetForcesRef,       &Physics::SetForces));
    physics_type.set("velocity",     sol::property(Physics::GetVelocityRef,     &Physics::SetVelocity));
      // Giving lua physics class functions
    physics_type.set_function("ApplyForce",    &Physics::ApplyForce);
    physics_type.set_function("UpdateGravity", &Physics::UpdateGravity);

      // Giving lua transform class
    sol::usertype<Transform> transform_type = state->new_usertype<Transform>("Transform",
        sol::constructors<Transform(), Transform(const Transform)>());
      // Giving lua transform class variables
    transform_type.set("position",      sol::property(Transform::GetPositionRef,      &Transform::SetPosition));
    transform_type.set("rotation",      sol::property(Transform::GetRotationRef,      &Transform::SetRotation));
    transform_type.set("scale",         sol::property(Transform::GetScaleRef,         &Transform::SetScale));
    transform_type.set("startPosition", sol::property(Transform::GetStartPositionRef, &Transform::SetStartPosition));

      // Giving lua object class
    state->set("object", GetParent());
    sol::usertype<Object> object_type = state->new_usertype<Object>("Object",
        sol::constructors<Object(), Object(const Object)>());
      // Giving lua object class variables
    object_type.set("name", sol::property(Object::GetNameRef, &Object::SetName));
    object_type.set("id",   sol::readonly_property(Object::GetId));
    object_type.set_function("GetPhysics", &Object::GetComponent<Physics>);
    object_type.set_function("GetTransform", &Object::GetComponent<Transform>);
}

/**
 * @brief Switches one script to another (replace)
 * 
 * @param scriptNum 
 * @param newScriptName 
 * @return true
 * @return false
 */
bool Behavior::SwitchScript(unsigned scriptNum, std::string newScriptName) {
      // Checking if this script is already attached
    if (CheckIfCopy(newScriptName)) return false;
    sol::state* state = states[scriptNum];
    scripts[scriptNum] = newScriptName;
      // Setting up new lua script
    state->script_file(std::string("data/scripts/" + scripts[scriptNum]).c_str());
    (*state)["Start"]();

    return true;
}

/**
 * @brief Attaching new script to the object
 * 
 * @param newScriptName 
 * @return true 
 * @return false 
 */
bool Behavior::AddScript(std::string newScriptName) {
      // Checking if this script is already attached
    if (CheckIfCopy(newScriptName)) return false;
      // Setting up new lua state
    sol::state* state = new sol::state;
    state->open_libraries(sol::lib::base, sol::lib::math, sol::lib::io, sol::lib::string);
    states.emplace_back(state);
      // Adding new script filename to list
    scripts.emplace_back(newScriptName);
    ClassSetup(state);
      // Setting up lua script to run
    states.back()->script_file(std::string("data/scripts/" + scripts.back()).c_str());
    (*states.back())["Start"]();

    return true;
}

/**
 * @brief Checks if the script is already attached to the object
 * 
 * @param newScriptName Name of script being checked
 * @return true 
 * @return false 
 */
bool Behavior::CheckIfCopy(std::string newScriptName) {
      // Checking if script is the same as an existing one
    for (std::string scriptName : scripts) {
        if (scriptName.compare(newScriptName) == 0) return true;
    }

      // Script is not a copy
    return false;
}

/**
 * @brief Clears states and state filenames from object
 * 
 */
void Behavior::Clear() {
    for (sol::state* state : states) {
        if (!state) continue;
        delete state;
        state = nullptr;
    }

    states.clear();
    scripts.clear();
}
