/**
 * @file file_writer.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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

// Engine includes //
#include "object.hpp"

/*! File_Writer class */
class File_Writer {
    public:
        File_Writer();
        void Write_File(std::string filename);

        void Write_Vec3(std::string valueName, glm::vec3 value);
        void Write_String(std::string valueName, std::string value);
        
        /**
         * @brief Writes most values to root (can't do strings)
         * 
         * @tparam T 
         * @param valueName Name of value being written to root
         * @param value Value being written to root
         */
        template <typename T>
        void Write_Value(std::string valueName, T value) {
            rapidjson::Value name(valueName.c_str(), rapidjson::SizeType(valueName.size()), root.GetAllocator());
            root.AddMember(name, value, root.GetAllocator());
        }

        void Write_Behavior_Name(std::vector<std::string>& behaviorNames);
        void Write_Object_Data(Object* object);
    private:
        rapidjson::Document root; //!< Holds the data for the json file
};

#endif