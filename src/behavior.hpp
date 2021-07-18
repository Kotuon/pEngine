/**
 * @file behavior.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

// std includes //
#include <vector>

// Library includes //
#include <vec3.hpp>
#include <lua.hpp>
#include <sol/sol.hpp>

// Engine includes //
#include "component.hpp"
#include "file_reader.hpp"

/*! Behavior class */
class Behavior : public Component {
    public:
        Behavior();
        Behavior(const Behavior& other);
        Behavior(File_Reader& reader);
        Behavior* Clone() const;

        void Update();

        void Read(File_Reader& reader);

        static CType GetCType();

        void SetupClassesForLua();
    private:
        std::vector<std::string> scripts;
        std::vector<sol::state*> states;
};

#endif