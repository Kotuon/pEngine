
#include <fstream>
#include <iostream>

#include "file_reader.hpp"
#include "trace.hpp"

File_Reader::File_Reader(string filename) {
    Read_File(filename);
}

void File_Reader::Read_File(string filename) {
    string fileToOpen = "data/json/" + filename + ".json";
    ifstream file(fileToOpen.c_str(), ifstream::binary);

    Json::CharReaderBuilder reader;
    string errors;
    if (!parseFromStream(reader, file, &root, &errors)) {
        Trace::Message("Unable to read file '" + filename + "': " + errors + "\n");
    }

    file.close();
}

int File_Reader::Read_Int(string valueName) {
    if (!root[valueName].isInt()) {
        Trace::Message("Error reading int: " + valueName + "\n");
        return 0;
    }
    return root[valueName].asInt();
}

string File_Reader::Read_String(string valueName) {
    if (!root[valueName].isString()) {
        Trace::Message("Error reading string: " + valueName + "\n");
        return string("");
    }
    return root[valueName].asString();
}

vec3 File_Reader::Read_Vec3(string valueName) {
    if (!root[valueName].isArray()) {
        Trace::Message("Error reading vec3: " + valueName + "\n");
        return vec3(0.f, 0.f, 0.f);
    }
    return vec3(root[valueName][0].asFloat(), root[valueName][1].asFloat(), root[valueName][2].asFloat());
}

bool File_Reader::Read_Bool(string valueName) {
    if (!root[valueName].isBool()) {
        Trace::Message("Error reading bool: " + valueName + "\n");
        return false;
    }

    return root[valueName].asBool();
}

float File_Reader::Read_Float(string valueName) {
    if (!root[valueName].isDouble()) {
        Trace::Message("Error reading float: " + valueName + "\n");
        return false;
    }

    return root[valueName].asFloat();
}

double File_Reader::Read_Double(string valueName) {
    if (!root[valueName].isDouble()) {
        Trace::Message("Error reading double: " + valueName + "\n");
        return false;
    }

    return root[valueName].asDouble();
}

string File_Reader::Read_Object_Name(string valueName) {
    if (!root[valueName]["objectName"].isString()) {
        Trace::Message("Error reading string: " + valueName + "\n");
        return string("");
    }
    return root[valueName]["objectName"].asString();
}

vec3 File_Reader::Read_Object_Position(string valueName) {
    if (!root[valueName]["position"].isArray()) {
        Trace::Message("Error reading string: " + valueName + "\n");
        return vec3(0.f, 0.f, 0.f);
    }
    return vec3(root[valueName]["position"][0].asFloat(), root[valueName]["position"][1].asFloat(), root[valueName]["position"][2].asFloat());
}
