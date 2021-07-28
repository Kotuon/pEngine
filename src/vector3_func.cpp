/**
 * @file vector3_func.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Engine includes //
#include "vector3_func.hpp"

/**
 * @brief Wrapper for the glm normalize function
 * 
 * @param vec Input vec3
 * @return glm::vec3 
 */
glm::vec3 Vector3_Func::normalize(const glm::vec3 vec) {
    return glm::normalize(vec);
}

/**
 * @brief Wrapper for the glm distance function
 * 
 * @param vec1 First input vec3
 * @param vec2 Second input vec3
 * @return float 
 */
float Vector3_Func::distance(const glm::vec3 vec1, const glm::vec3 vec2) {
    return glm::distance(vec1, vec2);
}

/**
 * @brief Wrapper for subtracting two glm vectors to make a new vector
 * 
 * @param vec1 First input vec3
 * @param vec2 Second input vec3
 * @return glm::vec3 
 */
glm::vec3 Vector3_Func::get_direction(const glm::vec3 vec1, const glm::vec3 vec2) {
    return vec1 - vec2;
}

/**
 * @brief Creates a glm::vec3 filled with zeroes
 * 
 * @return glm::vec3 
 */
glm::vec3 Vector3_Func::zero_vec3() {
    return glm::vec3(0.f, 0.f, 0.f);
}

/**
 * @brief Wrapper for the glm length function
 * 
 * @param vec Input vec3
 * @return float 
 */
float Vector3_Func::length(const glm::vec3 vec) {
    return glm::length(vec);
}
