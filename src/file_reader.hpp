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

#ifndef FILE_READER_HPP
#define FILE_READER_HPP

// std includes //
#include <string>

// Library includes //
#include <json.h>
#include <reader.h>
#include <vec3.hpp>

using namespace std;
using namespace glm;

/*! File_Reader class */
class File_Reader {
    public:
        File_Reader(string filename);
        void Read_File(string filename);

        int Read_Int(string valueName);
        string Read_String(string valueName);
        vec3 Read_Vec3(string valueName);
        bool Read_Bool(string valueName);
        float Read_Float(string valueName);
        double Read_Double(string valueName);

        string Read_Object_Name(string valueName);
        vec3 Read_Object_Position(string valueName);

    private:
        Json::Value root; //!< Holds the data of the json file
};

#endif