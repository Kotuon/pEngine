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

#ifndef MODEL_DATA_MANAGER_HPP
#define MODEL_DATA_MANAGER_HPP

// std includes //
#include <vector>
#include <string>

// Engine includes //
#include "model_data.hpp"

using namespace std;

/*! Model_Data_Manager class */
class Model_Data_Manager {
    public:
        static bool Initialize();
        static Model_Data* Get(string filename);
        static void Shutdown();
    private:
        vector<Model_Data*> models; //!< List of the different Model_Data objects
};

#endif