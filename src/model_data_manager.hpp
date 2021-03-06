/**
 * @file model_data_manager.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#ifndef MODEL_DATA_MANAGER_HPP
#define MODEL_DATA_MANAGER_HPP

// std includes //
#include <vector>
#include <string>

// Engine includes //
#include "model_data.hpp"
#include "file_reader.hpp"

/*! Model_Data_Manager class */
class Model_Data_Manager {
    public:
        static bool Initialize();
        static Model_Data* Get(File_Reader& reader);
        static Model_Data* Get(std::string modelName);
        static void Shutdown();
    private:
        std::vector<Model_Data*> models; //!< List of the different Model_Data objects
};

#endif