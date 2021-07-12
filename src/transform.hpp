/**
 * @file transform.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

// std includes //
#include <vec3.hpp>

// Engine includes //
#include "component.hpp"
#include "file_reader.hpp"

using namespace glm;

/*! Transform class */
class Transform : public Component {
    public:
        Transform();
        Transform(const Transform& other);
        Transform(File_Reader& reader);
        Transform* Clone() const;

        void SetPosition(vec3 pos);
        vec3 GetPosition() const;
        vec3& GetPosition();

        void SetOldPosition(vec3 oldPos);
        vec3 GetOldPosition() const;

        void SetScale(vec3 sca);
        vec3 GetScale() const;
        vec3& GetScale();

        void SetRotation(vec3 rot);
        vec3 GetRotation() const;
        vec3& GetRotation();

        void Read(File_Reader& reader);

        static CType GetCType();
    private:
        vec3 position;    //!< Position of object
        vec3 oldPosition; //!< Previous position of object
        vec3 scale;       //!< Scale of object
        vec3 rotation;    //!< Rotation of object
};

#endif