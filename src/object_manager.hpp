
#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

#include <vector>

#include "object.hpp"
#include "file_reader.hpp"

using namespace std;

class Object_Manager {
    public:
        static bool Initialize(File_Reader& preset);
        static void AddObject(Object* object);
        static Object* FindObject(unsigned id);
        static unsigned GetSize();
        static void Update();
        static void Shutdown();
        void ReadList(File_Reader& preset);
    private:
        vector<Object*> objects;
};

#endif