/**
 * @file file_reader.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#ifndef FILE_READER_HPP
#define FILE_READER_HPP

// std includes //
#include <string>

// Library includes //
#include <document.h>
#include <vec3.hpp>

/*! File_Reader class */
class File_Reader {
    public:
        File_Reader(std::string filename);
        void Read_File(std::string filename);

        int Read_Int(std::string valueName);
        std::string Read_String(std::string valueName);
        glm::vec3 Read_Vec3(std::string valueName);
        bool Read_Bool(std::string valueName);
        float Read_Float(std::string valueName);
        double Read_Double(std::string valueName);

        std::string Read_Object_Name(std::string valueName);
        std::string Read_Object_Template_Name(std::string valueName);
        glm::vec3 Read_Object_Position(std::string valueName);

        std::string Read_Behavior_Name(std::string valueName);

    private:
        rapidjson::Document root; //!< Holds the data of the json file
};

#endif