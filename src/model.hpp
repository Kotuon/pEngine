
#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <array>

#include <GL/gl.h>
#include <vec3.hpp>
#include <vec2.hpp>

#include "component.hpp"

using namespace std;
using namespace glm;

class Model : public Component {
    public:
        Model(GLenum mode_ = GL_TRIANGLES);
        Model(const Model& other);

        Model* Clone() const;
        bool Load(const char* filename);
        void Draw();
    private:
        struct Face {
            vector<vec3> vertices;
            vector<vec2> uvs;
            vector<vec3> normals;
            array<float, 3> color;
        };

        GLenum mode;
        vector<Face> faces;
};

#endif