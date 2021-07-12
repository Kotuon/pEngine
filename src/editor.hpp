
#ifndef EDITOR_HPP
#define EDITOR_HPP

// Engine includes //
#include "object.hpp"

class Editor {
    public:
        static bool Initialize();
        static void Update();
        static void Render();
        static void Shutdown();
    private:
        void Display_Dockspace();
        void Display_Scene();
        void Display_Components();
        void Display_World_Settings();
        void Display_Camera_Settings();

        void Display_Model(Object* object);
        void Display_Physics(Object* object);
        void Display_Transform(Object* object);
    private:
        bool isOpen;
        int selected_object;
};

#endif