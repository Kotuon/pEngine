
#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <string>

#include <json.h>
#include <reader.h>
#include <vec3.hpp>

using namespace std;
using namespace glm;

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
        Json::Value root;
};

#endif