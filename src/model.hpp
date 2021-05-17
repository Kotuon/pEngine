
#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <array>

#include <freeglut.h>
#include <vec3.hpp>
#include <vec2.hpp>

using namespace std;
using namespace glm;

class Model {
    public:
        Model(GLenum mode_);
        bool Load(const char* filename);
        void Draw();
    private:
        struct Face {
            vector<vec3> vertices;
            vector<vec2> uvs;
            vector<vec3> normals;
            array<GLfloat, 3> color;
        };

        GLenum mode;
        vector<Face> faces;
};

#endif