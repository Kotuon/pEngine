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

// Library includes //
#include <vec3.hpp>

// Engine includes //
#include "component.hpp"
#include "file_reader.hpp"

using namespace std;
using namespace glm;

/*! Behavior class */
class Behavior : public Component {
    public:
        Behavior();
        Behavior(const Behavior& other);
        Behavior(File_Reader& reader);
        Behavior* Clone() const;

        void Update();

        void Read(File_Reader& reader);

        void SetStartPos(vec3 startPos_);
        vec3 GetStartPos() const;

        float GetMaxVelocity() const;
        float GetIdleRadius() const;
        float GetPushForce() const;
        float GetDirVariation() const;
        float GetPushVariation() const;

        static CType GetCType();
    private:
        vector<int> behaviorList; //!< List of behaviors to call
        vec3 startPos;            //!< Start position of the object
        float maxVelocity;        //!< Fastest the object can move
        float idleRadius;         //!< Furthest that object can be from startPos
        float pushForce;          //!< Strength of force applied to object
        float dirVariation;       //!< Amount of variation applied to object's direction
        float pushVariation;      //!< Amount of variation applied to object's push force
};

#endif