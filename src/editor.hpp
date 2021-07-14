
#ifndef EDITOR_HPP
#define EDITOR_HPP

// Engine includes //
#include "object.hpp"
#include "model.hpp"
#include "physics.hpp"
#include "trace.hpp"

class Editor {
    public:
        static bool Initialize();
        static void Update();
        static void Render();
        static void Shutdown();

        static bool GetTakeKeyboardInput();
    private:
        void Display_Dockspace();
        void Display_Scene();
        void Display_Components();
        void Display_World_Settings();
        void Display_Camera_Settings();

        void Display_Model(Model* model);
        void Display_Physics(Physics* physics);
        void Display_Transform(Transform* transform);
    private:
        bool isOpen;
        int selected_object;
        bool takeKeyboardInput;
};

#endif