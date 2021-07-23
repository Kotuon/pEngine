
// std includes //
#include <fstream>
#include <iostream>

// Engine includes //
#include "file_writer.hpp"

File_Writer::File_Writer() {}

void File_Writer::Write_File(std::string filename) {
    std::string fileToOpen = "data/json/" + filename;
    std::ofstream file(fileToOpen.c_str(), std::ifstream::binary);

    Json::StreamWriterBuilder builder;
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(root, &file);

    file.close();
}

// void File_Writer::Write_Int(std::string valueName, int value) {
//     root[valueName.c_str()] = value;
// }

// void File_Writer::Write_String(std::string valueName, std::string value) {
//     root[valueName.c_str()] = value;
// }

void File_Writer::Write_Vec3(std::string valueName, glm::vec3 value) {
    Json::Value vec(Json::arrayValue);
    vec.append(Json::Value(value.x));
    vec.append(Json::Value(value.y));
    vec.append(Json::Value(value.z));

    root[valueName.c_str()] = vec;
}

void File_Writer::Write_Behavior_Name(std::vector<std::string>& behaviorNames) {
    Json::Value behaviors;

    for (unsigned i = 0; i < behaviorNames.size(); ++i) {
        behaviors[std::string("behavior_" + std::to_string(i))] = behaviorNames[i];
    }

    root["behaviors"] = behaviors;
}