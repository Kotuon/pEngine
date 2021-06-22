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

#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

// std includes //
#include <vector>

// Engine includes //
#include "component.hpp"
#include "file_reader.hpp"

using namespace std;

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
    private:
        vector<int> behaviorList; //!< List of behaviors to call
};

#endif