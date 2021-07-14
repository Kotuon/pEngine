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

// Engine includes //
#include "file_reader.hpp"
#include "trace.hpp"

/**
 * @brief Creates File_Reader object and reads given file
 * 
 * @param filename Name of the file to be read
 */
File_Reader::File_Reader(string filename) {
    Read_File(filename);
}

/**
 * @brief Reads the json file data into the root variable
 * 
 * @param filename Name of the file to be read
 */
void File_Reader::Read_File(string filename) {
      // Opening the json file
    string fileToOpen = "data/json/" + filename;
    ifstream file(fileToOpen.c_str(), ifstream::binary);

      // Reading data from file into root variable
    Json::CharReaderBuilder reader;
    string errors;
    if (!parseFromStream(reader, file, &root, &errors)) {
        Trace::Message("Unable to read file '" + filename + "': " + errors + "\n");
    }

    file.close();
}

/**
 * @brief Reads int from the json file stored in root
 * 
 * @param valueName Name of the int in the json file
 * @return int Value that was read
 */
int File_Reader::Read_Int(string valueName) {
      // Checking if the value is an int
    if (!root[valueName].isInt()) {
        Trace::Message("Error reading int: " + valueName + "\n");
        return 0;
    }
    return root[valueName].asInt();
}

/**
 * @brief Reads string from the json file stored in root
 * 
 * @param valueName Name of the string in the json file
 * @return string Value that was read
 */
string File_Reader::Read_String(string valueName) {
      // Checking if the value is a string
    if (!root[valueName].isString()) {
        Trace::Message("Error reading string: " + valueName + "\n");
        return string("");
    }
    return root[valueName].asString();
}

/**
 * @brief Reads vec3 from the json file stored in root. vec3 is constructed
 *        from an array
 * 
 * @param valueName Name of the vec3 in the json file
 * @return vec3 Value that was read
 */
vec3 File_Reader::Read_Vec3(string valueName) {
      // Checking if the value is an array
    if (!root[valueName].isArray()) {
        Trace::Message("Error reading vec3: " + valueName + "\n");
        return vec3(0.f, 0.f, 0.f);
    }
    return vec3(root[valueName][0].asFloat(), root[valueName][1].asFloat(), root[valueName][2].asFloat());
}

/**
 * @brief Reads bool from the json file stored in root
 * 
 * @param valueName Name of the bool in the json file
 * @return true 
 * @return false 
 */
bool File_Reader::Read_Bool(string valueName) {
      // Checking if the value is a bool
    if (!root[valueName].isBool()) {
        Trace::Message("Error reading bool: " + valueName + "\n");
        return false;
    }
    return root[valueName].asBool();
}

/**
 * @brief Reads float from the json stored in root
 * 
 * @param valueName Name of the float in the json file
 * @return float Value that was read
 */
float File_Reader::Read_Float(string valueName) {
      // Checking if the value is a double (has decimal)
    if (!root[valueName].isDouble()) {
        Trace::Message("Error reading float: " + valueName + "\n");
        return 0.f;
    }
    return root[valueName].asFloat();
}

/**
 * @brief Reads double from the json stored in root
 * 
 * @param valueName Name of the double in the json file
 * @return double Value that was read
 */
double File_Reader::Read_Double(string valueName) {
      // Checking if the value is a double (has decimal)
    if (!root[valueName].isDouble()) {
        Trace::Message("Error reading double: " + valueName + "\n");
        return false;
    }
    return root[valueName].asDouble();
}

/**
 * @brief Reads the name of an object from an object list (preset folder)
 * 
 * @param valueName Specifies which object
 * @return string Name of the object
 */
string File_Reader::Read_Object_Name(string valueName) {
      // Checking if the value is a string
    if (!root[valueName]["objectName"].isString()) {
        Trace::Message("Error reading string: " + valueName + "\n");
        return string("");
    }
    return root[valueName]["objectName"].asString();
}

/**
 * @brief Reads the position of an object from an object list (preset folder)
 * 
 * @param valueName Specifies which object
 * @return vec3 Position of object
 */
vec3 File_Reader::Read_Object_Position(string valueName) {
      // Checking if the value is an array (used to construct vec3)
    if (!root[valueName]["position"].isArray()) {
        Trace::Message("Error reading string: " + valueName + "\n");
        return vec3(0.f, 0.f, 0.f);
    }
    return vec3(root[valueName]["position"][0].asFloat(), root[valueName]["position"][1].asFloat(), root[valueName]["position"][2].asFloat());
}

/**
 * @brief Reads the name of the behavior
 * 
 * @param valueName Behavior to read
 * @return string Name of the behavior
 */
string File_Reader::Read_Behavior_Name(string valueName) {
      // Checking if the value is a string
    if (!root["behaviors"][valueName].isString()) {
        Trace::Message("Error reading string: " + valueName + "\n");
        return string("");
    }
    return root["behaviors"][valueName].asString();
}