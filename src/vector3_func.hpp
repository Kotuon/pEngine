
#pragma once
#ifndef VECTOR3_FUNC_HPP
#define VECTOR3_FUNC_HPP

// Library includes //
#include <glm.hpp>
#include <vec3.hpp>

class Vector3_Func {
    public:
        static glm::vec3 normalize(const glm::vec3 vec);
        static float distance(const glm::vec3 vec1, const glm::vec3 vec2);
        static glm::vec3 get_direction(const glm::vec3 vec1, const glm::vec3 vec2);
        static glm::vec3 zero_vec3();
        static float length(const glm::vec3 vec3);
};

#endif