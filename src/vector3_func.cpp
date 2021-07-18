
#include "vector3_func.hpp"

glm::vec3 Vector3_Func::normalize(const glm::vec3 vec) {
    return glm::normalize(vec);
}

float Vector3_Func::distance(const glm::vec3 vec1, const glm::vec3 vec2) {
    return glm::distance(vec1, vec2);
}

glm::vec3 Vector3_Func::get_direction(const glm::vec3 vec1, const glm::vec3 vec2) {
    return vec1 - vec2;
}

glm::vec3 Vector3_Func::zero_vec3() {
    return glm::vec3(0.f, 0.f, 0.f);
}

float Vector3_Func::length(const glm::vec3 vec) {
    return glm::length(vec);
}
