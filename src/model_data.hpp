
#ifndef MODEL_DATA_HPP
#define MODEL_DATA_HPP

#include <vector>
#include <array>
#include <string>

#include <vec3.hpp>
#include <vec2.hpp>

using namespace std;
using namespace glm;


class Model_Data {
    public:
        Model_Data();
        Model_Data(const Model_Data& other);

        bool Load(string filename);
        void Draw() const;
    private:
        struct Face {
            vector<vec3> vertices;
            vector<vec2> uvs;
            vector<vec3> normals;
            array<float, 3> color;
        }; 
        vector<Face> faces;
};

#endif