
#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <vec3.hpp>

#include "component.hpp"

using namespace glm;

class Transform : public Component {
    public:
        Transform();

        void SetPosition(vec3 pos);
        vec3 GetPosition() const;

        void SetScale(vec3 sca);
        vec3 GetScale() const;

        void SetRotation(float rot);
        float GetRotation() const;
    private:
        vec3 position;
        vec3 scale;
        float rotation;
};

#endif