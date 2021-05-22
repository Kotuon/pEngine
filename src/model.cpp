
#include <cstdio>
#include <string>

#include "model.hpp"
#include "trace.hpp"
#include "object.hpp"
#include "transform.hpp"

Model::Model(GLenum mode_) : Component(CType::CModel), mode(mode_) {}

Model::Model(const Model& other) : Component(CType::CModel) {
    *this = other;
}

Model* Model::Clone() const {
    return new Model(*this);
}

bool Model::Load(const char* filename) {
    vector<unsigned> vertex_indices, uv_indices, normal_indices;
    vector<vec3> temp_vertices;
    vector<vec2> temp_uvs;
    vector<vec3> temp_normals;
    
    FILE* file = fopen(filename, "r");
    if (!file) {
        Trace::Message("File was not successfully opened.");
        return false;
    }

    while (true) {
        char line_header[256];

        int res = fscanf(file, "%s", line_header);
        if (res == EOF) break;

        if (strcmp(line_header,"v") == 0) {
            vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.emplace_back(vertex);
            continue;
        }

        if (strcmp(line_header, "vt") == 0) {
            vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.emplace_back(uv);
            continue;
        }

        if (strcmp(line_header, "vn") == 0) {
            vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.emplace_back(normal);
            continue;
        }

        if (strcmp(line_header, "f") == 0) {
            Face face;

            unsigned vertex_index[3], uv_index[3], normal_index[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertex_index[0], &uv_index[0], &normal_index[0],
                &vertex_index[1], &uv_index[1], &normal_index[1], &vertex_index[2], &uv_index[2], &normal_index[2]);//,
                //&vertex_index[3], &uv_index[3], &normal_index[3]);
            
            if (matches != 9) {
                Trace::Message("File is incompatible with this parser. Export using different settings.");
                return false;
            }

            face.vertices.emplace_back(temp_vertices[vertex_index[0] - 1]);
            face.vertices.emplace_back(temp_vertices[vertex_index[1] - 1]);
            face.vertices.emplace_back(temp_vertices[vertex_index[2] - 1]);
            //face.vertices.emplace_back(temp_vertices[vertex_index[3] - 1]);

            face.uvs.emplace_back(temp_uvs[uv_index[0] - 1]);
            face.uvs.emplace_back(temp_uvs[uv_index[1] - 1]);
            face.uvs.emplace_back(temp_uvs[uv_index[2] - 1]);
            //face.uvs.emplace_back(temp_uvs[uv_index[3] - 1]);

            face.normals.emplace_back(temp_normals[normal_index[0] - 1]);
            face.normals.emplace_back(temp_normals[normal_index[1] - 1]);
            face.normals.emplace_back(temp_normals[normal_index[2] - 1]);
            //face.normals.emplace_back(temp_normals[normal_index[3] - 1]);

            if (faces.size() % 6 == 0) {
                face.color[0] = 0.f;
                face.color[1] = 1.f;
                face.color[2] = 0.f;
            }
            else if (faces.size() % 6 == 1) {
                face.color[0] = 1.f;
                face.color[1] = .5f;
                face.color[2] = 0.f;
            }
            else if (faces.size() % 6 == 2) {
                face.color[0] = 1.f;
                face.color[1] = 0.f;
                face.color[2] = 0.f;
            }
            else if (faces.size() % 6 == 3) {
                face.color[0] = 1.f;
                face.color[1] = 1.f;
                face.color[2] = 0.f;
            }
            else if (faces.size() % 6 == 4) {
                face.color[0] = 0.f;
                face.color[1] = 0.f;
                face.color[2] = 1.f;
            }
            else if (faces.size() % 6 == 5) {
                face.color[0] = 1.f;
                face.color[1] = 0.f;
                face.color[2] = 1.f;
            }

            faces.emplace_back(face);
        }
    }

    return true;
}

void Model::Draw() {
    Transform* transform = GetParent()->GetComponent<Transform>(CType::CTransform);

    vec3 pos = transform->GetPosition();
    glTranslatef((GLfloat)pos.x, (GLfloat)pos.y, (GLfloat)pos.z);
    glRotatef(transform->GetRotation(), 1.f, 1.f, 1.f);

    glTranslatef(0.f, 0.f, 0.f);
    glBegin(mode);
        for (unsigned i = 0; i < faces.size(); ++i) {
            glColor3f(faces[i].color[0], faces[i].color[1], faces[i].color[2]);
            for (unsigned j = 0; j < faces[i].vertices.size(); ++j) {
                glVertex3f(faces[i].vertices[j].x, 
                           faces[i].vertices[j].y, 
                           faces[i].vertices[j].z);
            }

            for (unsigned j = 0; j < faces[i].uvs.size(); ++j) {
                glTexCoord2f(faces[i].uvs[j].x,
                             1 - faces[i].uvs[j].x);
            }
        }
    glEnd();
}