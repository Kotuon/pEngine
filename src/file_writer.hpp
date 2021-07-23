
#pragma once
#ifndef FILE_WRITER_HPP
#define FILE_WRITER_HPP

// Library includes //
#include <json.h>
#include <json/writer.h>
#include <vec3.hpp>

class File_Writer {
    public:
        File_Writer();
        void Write_File(std::string filename);
    
        // void Write_Int(std::string valueName, int value);
        // void Write_String(std::string valueName, std::string value);
        void Write_Vec3(std::string valueName, glm::vec3 value);
        // void Write_Bool(std::string valueName, bool value);
        // void Write_Float(std::string valueName, float value);
        // void Write_Double(std::string valueName, double value);

        template <typename T>
        void Write_Value(std::string valueName, T value) {
            root[valueName.c_str()] = value;
        }

        // void Write_Object_Name(std::string objectName);
        // void Write_Object_Position(std::string objectName, glm::vec3 objectPosition);
        void Write_Behavior_Name(std::vector<std::string>& behaviorNames);
    private:
        Json::Value root; //!< Holds the data for the json file
};

#endif