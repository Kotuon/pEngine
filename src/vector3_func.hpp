/**
 * @file vector3_func.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#ifndef VECTOR3_FUNC_HPP
#define VECTOR3_FUNC_HPP

// Library includes //
#include <glm.hpp>
#include <vec3.hpp>

/*! Vector3_Func class */
class Vector3_Func {
    public:
        static glm::vec3 normalize(const glm::vec3 vec);
        static float distance(const glm::vec3 vec1, const glm::vec3 vec2);
        static glm::vec3 get_direction(const glm::vec3 vec1, const glm::vec3 vec2);
        static glm::vec3 zero_vec3();
        static float length(const glm::vec3 vec3);
        static glm::vec3 add_float(const glm::vec3 vec, float num);
        static glm::vec3 add_vec3(const glm::vec3 vec1, const glm::vec3 vec2);
};

#endif