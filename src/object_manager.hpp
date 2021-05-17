
#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

#include <vector>

#include "object.hpp"

using namespace std;

class Object_Manager {
    public:
        static void Initialize();
        static void AddObject(Object* object);
        static Object* FindObject(unsigned id);
        static unsigned GetSize();
    private:
        vector<Object*> objects;
};

#endif