
#ifndef MODEL_DATA_MANAGER_HPP
#define MODEL_DATA_MANAGER_HPP

#include <vector>
#include <string>

#include "model_data.hpp"

using namespace std;

class Model_Data_Manager {
    public:
        static bool Initialize();
        static Model_Data* Get(string filename);
        static void Shutdown();
    private:
        vector<Model_Data*> models;
};

#endif