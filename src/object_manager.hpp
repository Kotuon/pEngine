/**
 * @file object_manager.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

// std includes //
#include <vector>

// Engine includes //
#include "object.hpp"
#include "file_reader.hpp"
#include "file_writer.hpp"

/*! Object_Manager class */
class Object_Manager {
    public:
        static bool Initialize(File_Reader& preset);
        static void AddObject(Object* object);
        static Object* FindObject(int id);
        static Object* FindObject(std::string objectName);
        static unsigned GetSize();
        static void Update();
        static void Shutdown();
        void ReadList(File_Reader& preset);
        static std::string CheckName(std::string objectName, int id);
        static void RemoveObject(int id);
        static void Write(File_Writer& writer);
    private:
        std::vector<Object*> objects; //!< Current objects being tracked by the engine
};

#endif