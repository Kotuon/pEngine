/**
 * @file engine.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#ifndef ENGINE_HPP
#define ENGINE_HPP

// std includes //
#include <chrono> // steady_clock
#include <string>

// Library includes //
#include <vec3.hpp>

/*! Engine class */
class Engine {
    public:
        static void Initialize();
        static void Update();
        static void Shutdown();
        static void Restart();
        static void Restart(std::string presetName);
        static float GetDeltaTime();
        static float GetDt();
        static double& GetGravConst();
        static std::string GetPresetName();
        static float& GetLightPower();
        static glm::vec3& GetLightPos();
        static void Write();
        static void SetPresetName(std::string presetName_);
    private:
        bool  isRunning;        //!< state of the main loop
        float deltaTime;        //!< time between frames
        float accumulator;      //!< amount of unused time for physics updates
        float time;             //!< total time
        const float dt = 0.01f; //!< fixed delta time for physics updates

        std::chrono::steady_clock::time_point currentTime; //!< current read time
        std::chrono::steady_clock::time_point newTime;     //!< newest read time
        std::chrono::steady_clock::duration timeTaken;     //!< time between frames

        double gravConst;  //!< gravitational constant (used in physics)
        std::string presetName; //!< name of the preset being used

        float lightPower; //!< Power of the light in the scene
        glm::vec3 lightPos;    //!< Position of the light in the scene
};

#endif