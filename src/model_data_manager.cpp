
#include "model_data_manager.hpp"

static Model_Data_Manager* model_data_manager = nullptr;

bool Model_Data_Manager::Initialize() {
    model_data_manager = new Model_Data_Manager;
    if (!model_data_manager) return false;
    
    model_data_manager->models.reserve(10);
    return true;
}

Model_Data* Model_Data_Manager::Get(string filename) {
    for (Model_Data* model_data : model_data_manager->models) {
        if (model_data->GetFilename().compare(filename) == 0) {
            return model_data;
        }
    }

    Model_Data* data = new Model_Data;
    data->Load(filename);
    model_data_manager->models.emplace_back(data);

    return data;
}

void Model_Data_Manager::Shutdown() {
    if (!model_data_manager) return;

    for (Model_Data* model_data : model_data_manager->models) {
        if (!model_data) continue;

        delete model_data;
        model_data = nullptr;
    }

    delete model_data_manager;
    model_data_manager = nullptr;
}