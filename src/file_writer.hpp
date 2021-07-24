
#pragma once
#ifndef FILE_WRITER_HPP
#define FILE_WRITER_HPP

// std includes //
#include <string>
#include <vector>

// Library includes //
#include <document.h>
#include <filewritestream.h>
#include <prettywriter.h>
#include <vec3.hpp>

class File_Writer {
    public:
        File_Writer();
        void Write_File(std::string filename);

        void Write_Vec3(std::string valueName, glm::vec3 value);
        void Write_String(std::string valueName, std::string value);
        
        template <typename T>
        void Write_Value(std::string valueName, T value) {
            rapidjson::Value name(valueName.c_str(), rapidjson::SizeType(valueName.size()), root.GetAllocator());
            root.AddMember(name, value, root.GetAllocator());
        }

        // void Write_Object_Name(std::string objectName);
        // void Write_Object_Position(std::string objectName, glm::vec3 objectPosition);
        void Write_Behavior_Name(std::vector<std::string>& behaviorNames);
    private:
        rapidjson::Document root; //!< Holds the data for the json file
};

#endif