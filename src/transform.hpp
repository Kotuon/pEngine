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

#pragma once
#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

// std includes //
#include <vec3.hpp>

// Engine includes //
#include "component.hpp"
#include "file_reader.hpp"
#include "file_writer.hpp"

/*! Transform class */
class Transform : public Component {
    public:
        Transform();
        Transform(const Transform& other);
        Transform(File_Reader& reader);
        Transform* Clone() const;

        void SetPosition(glm::vec3 pos);
        glm::vec3 GetPosition() const;
        glm::vec3& GetPositionRef();

        void SetOldPosition(glm::vec3 oldPos);
        glm::vec3 GetOldPosition() const;

        void SetScale(glm::vec3 sca);
        glm::vec3 GetScale() const;
        glm::vec3& GetScaleRef();

        void SetRotation(glm::vec3 rot);
        glm::vec3 GetRotation() const;
        glm::vec3& GetRotationRef();

        void SetStartPosition(glm::vec3 startPosition_);
        glm::vec3 GetStartPosition() const;
        glm::vec3& GetStartPositionRef();

        void Read(File_Reader& reader);
        void Write(File_Writer& writer);

        static CType GetCType();
    private:
        glm::vec3 position;      //!< Position of object
        glm::vec3 oldPosition;   //!< Previous position of object
        glm::vec3 scale;         //!< Scale of object
        glm::vec3 rotation;      //!< Rotation of object
        glm::vec3 startPosition; //!< Starting position of the object
};

#endif