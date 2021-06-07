/**
 * @file model_data_manager.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Engine includes //
#include "model_data_manager.hpp"
#include "trace.hpp"

static Model_Data_Manager* model_data_manager = nullptr; //!< Model_Data_Manager object

/**
 * @brief Initializes the model_data_manager
 * 
 * @return true 
 * @return false 
 */
bool Model_Data_Manager::Initialize() {
      // Initializing model_data_manager
    model_data_manager = new Model_Data_Manager;
    if (!model_data_manager) {
        Trace::Message("Model Data Manager was not initialized.");
        return false;
    }
    
    model_data_manager->models.reserve(10);
    return true;
}

/**
 * @brief Checks if model data has already been read in. If yes then it returns
 *        a pointer to that data. If no it reads it in and adds it to the model
 *        list
 * 
 * @param filename Name of file containing model data
 * @return Model_Data* Model data either read or gotten from list
 */
Model_Data* Model_Data_Manager::Get(string filename) {
      // Checks name of file against other model data objects
    for (Model_Data* model_data : model_data_manager->models) {
        if (model_data->GetFilename().compare(filename) == 0) {
            return model_data;
        }
    }

      // Creates new Model_Data object, then adds it to list
    Model_Data* data = new Model_Data;
    data->Load(filename);
    model_data_manager->models.emplace_back(data);

    return data;
}

/**
 * @brief Deletes all of the Model_Data objects in the models list then deletes
 *        model_data_manager
 * 
 * @return void
 */
void Model_Data_Manager::Shutdown() {
    if (!model_data_manager) return;

      // Deleting all of the Model_Data objects
    for (Model_Data* model_data : model_data_manager->models) {
        if (!model_data) continue;

        delete model_data;
        model_data = nullptr;
    }

    delete model_data_manager;
    model_data_manager = nullptr;
}