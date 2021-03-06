/**
 * @file file_reader.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// std includes //
#include <fstream>
#include <iostream>

// Library includes //
#include <filereadstream.h>

// Engine includes //
#include "file_reader.hpp"
#include "trace.hpp"

using namespace rapidjson;

/**
 * @brief Reads the json file data into the root variable
 * 
 * @param filename Name of the file to be read
 * @return true
 * @return false
 */
bool File_Reader::Read_File(std::string filename) {
      // Opening the json file
    std::string fileToOpen = filename;
    FILE* file = fopen(fileToOpen.c_str(), "r");
    if (!file) return false;

    char buffer[65536];
    FileReadStream stream(file, buffer, sizeof(buffer));
    root.ParseStream<0, UTF8<>, FileReadStream>(stream);

    fclose(file);
    return true;
}

/**
 * @brief Reads int from the json file stored in root
 * 
 * @param valueName Name of the int in the json file
 * @return int Value that was read
 */
int File_Reader::Read_Int(std::string valueName) {
      // Checking if the value is an int
    if (!root.HasMember(valueName.c_str())) {
        return 0;
    }
    return root[valueName.c_str()].GetInt();
}

/**
 * @brief Reads std::string from the json file stored in root
 * 
 * @param valueName Name of the std::string in the json file
 * @return std::string Value that was read
 */
std::string File_Reader::Read_String(std::string valueName) {
      // Checking if the value is a std::string
    if (!root.HasMember(valueName.c_str())) {
        return std::string("");
    }
    return root[valueName.c_str()].GetString();
}

/**
 * @brief Reads glm::vec3 from the json file stored in root. glm::vec3 is constructed
 *        from an array
 * 
 * @param valueName Name of the glm::vec3 in the json file
 * @return glm::vec3 Value that was read
 */
glm::vec3 File_Reader::Read_Vec3(std::string valueName) {
      // Checking if the value is an array
    if (!root.HasMember(valueName.c_str())) {
        return glm::vec3(0.f, 0.f, 0.f);
    }
    return glm::vec3(root[valueName.c_str()][0].GetFloat(), root[valueName.c_str()][1].GetFloat(), root[valueName.c_str()][2].GetFloat());
}

/**
 * @brief Reads bool from the json file stored in root
 * 
 * @param valueName Name of the bool in the json file
 * @return true 
 * @return false 
 */
bool File_Reader::Read_Bool(std::string valueName) {
      // Checking if the value is a bool
    if (!root.HasMember(valueName.c_str())) {
        return false;
    }
    return root[valueName.c_str()].GetBool();
}

/**
 * @brief Reads float from the json stored in root
 * 
 * @param valueName Name of the float in the json file
 * @return float Value that was read
 */
float File_Reader::Read_Float(std::string valueName) {
      // Checking if the value is a double (has decimal)
    if (!root.HasMember(valueName.c_str())) {
        return 0.f;
    }
    return root[valueName.c_str()].GetFloat();
}

/**
 * @brief Reads double from the json stored in root
 * 
 * @param valueName Name of the double in the json file
 * @return double Value that was read
 */
double File_Reader::Read_Double(std::string valueName) {
      // Checking if the value is a double (has decimal)
    if (!root.HasMember(valueName.c_str())) {
        return false;
    }
    return root[valueName.c_str()].GetDouble();
}

/**
 * @brief Reads the name of an object from an object list (preset folder)
 * 
 * @param valueName Specifies which object
 * @return std::string Name of the object
 */
std::string File_Reader::Read_Object_Name(std::string valueName) {
      // Checking if the value exists
    if (!root.HasMember(valueName.c_str())) {
        return std::string("");
    }
    if (!root[valueName.c_str()].HasMember("objectName")) {
        return std::string("");
    }

    return root[valueName.c_str()]["objectName"].GetString();
}

/**
 * @brief Reads the name of the template file for object
 * 
 * @param valueName 
 * @return std::string 
 */
std::string File_Reader::Read_Object_Template_Name(std::string valueName) {
      // Checking if the value exists
    if (!root.HasMember(valueName.c_str())) {
        return std::string("");
    }
    if (!root[valueName.c_str()].HasMember("templateName")) {
        return std::string("");
    }

    return root[valueName.c_str()]["templateName"].GetString();
}

/**
 * @brief Reads the position of an object from an object list (preset folder)
 * 
 * @param valueName Specifies which object
 * @return glm::vec3 Position of object
 */
glm::vec3 File_Reader::Read_Object_Position(std::string valueName) {
    if (!root[valueName.c_str()].HasMember("position")) {
        return glm::vec3(0.f, 0.f, 0.f);
    }

    Value& array = root[valueName.c_str()]["position"];
    return glm::vec3(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat());
}

/**
 * @brief Reads the scale of an object
 * 
 * @param valueName 
 * @return glm::vec3 
 */
glm::vec3 File_Reader::Read_Object_Scale(std::string valueName) {
      // Checking if value exists
    if (!root[valueName.c_str()].HasMember("scale")) {
        return glm::vec3(0.f, 0.f, 0.f);
    }

    Value& array = root[valueName.c_str()]["scale"];
    return glm::vec3(array[0].GetFloat(), array[1].GetFloat(), array[2].GetFloat());
}

/**
 * @brief Reads the name of the behavior
 * 
 * @param valueName Behavior to read
 * @return std::string Name of the behavior
 */
std::string File_Reader::Read_Behavior_Name(std::string valueName) {
      // Checking if value exists
    if (!root["behaviors"].HasMember(valueName.c_str())) {
        return std::string("");
    }

    return root["behaviors"][valueName.c_str()].GetString();
}