/**
 * @file editor.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#ifndef EDITOR_HPP
#define EDITOR_HPP

// Engine includes //
#include "object.hpp"
#include "model.hpp"
#include "physics.hpp"
#include "trace.hpp"

/*! Editor class */
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
        bool isOpen;            //!< Whether the editor window is open or not
        int selected_object;    //!< Current object selected in the scene window
        bool takeKeyboardInput; //!< Whether the program should take keyboard input
};

#endif