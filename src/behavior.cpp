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

// Engine includes //
#include "behavior_manager.hpp"
#include "behavior.hpp"
#include "engine.hpp"
#include "random.hpp"

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
    for (lua_State* state : states) {
        lua_getglobal(state, "Update");
        lua_pushnumber(state, Engine::GetDeltaTime());
        lua_call(state, 1, 0);

        lua_getglobal(state, "FixedUpdate");
        lua_pushnumber(state, Engine::GetDt());
        lua_call(state, 1, 0);
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
    string behavior_name = reader.Read_Behavior_Name("behavior_" + to_string(behavior_num));
        if (behavior_name.compare("") == 0) break;

        scripts.emplace_back(behavior_name);
        ++behavior_num;
    }
    
    for (string script : scripts) {
        states.emplace_back();
        states.back() = luaL_newstate();
        luaL_openlibs(states.back());
        luaL_dofile(states.back(), string("data/scripts/" + script).c_str());
    }
}

/**
 * @brief Gets the CType of Behavior (used in Object::GetComponent<>())
 * 
 * @return CType 
 */
CType Behavior::GetCType() {
    return CType::CBehavior;
}