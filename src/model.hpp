
#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <array>
#include <string>

#include <GL/gl.h>
#include <vec3.hpp>
#include <vec2.hpp>

#include "component.hpp"
#include "file_reader.hpp"
#include "model_data.hpp"

using namespace std;
using namespace glm;

class Model : public Component {
    public:
        Model(GLenum mode_ = GL_TRIANGLES);
        Model(const Model& other);
        Model(File_Reader& reader, GLenum mode_ = GL_TRIANGLES);
        Model* Clone() const;

        bool Load(string filename);
        void Draw();

        void Read(File_Reader reader);

        static CType GetCType();
    private:
        GLenum mode;
        Model_Data* data;
};

#endif