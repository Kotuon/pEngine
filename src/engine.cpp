/**
 * @file engine.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// std includes //
#include <cmath>
#include <string>

// Engine includes
  // System includes
#include "engine.hpp"
#include "graphics.hpp"
  // Object inclues //
#include "object_manager.hpp"
#include "object.hpp"
  // Component includes //
#include "component.hpp"
#include "model.hpp"
#include "physics.hpp"
#include "transform.hpp"
  // Misc includes //
#include "camera.hpp"
#include "file_reader.hpp"

  // Engine object
static Engine* engine = nullptr;

/**
 * @brief Initializes the engine and the systems in the engine
 * 
 */
void Engine::Initialize() {
      // Initializing engine
    engine = new Engine;
    if (!engine) {
        Trace::Message("Engine was not initialized.\n");
        return;
    }

      // Reading settings from json
    File_Reader settings("settings");
    File_Reader preset("preset/" + settings.Read_String("preset"));
    engine->gravConst = preset.Read_Double("gravConst");

      // Initializing sub systems
    if (!Camera::Initialize(settings)) return;
    if (!Graphics::Initialize(settings)) return;
    if (!Object_Manager::Initialize(preset)) return;

      // Setting up variables used for dt
    engine->currentTime = chrono::steady_clock::now();
    engine->accumulator = 0.f;
    engine->time = 0.f;
    engine->isRunning = true;
}

/**
 * @brief Updates object and camera. Object updates have a fixed time step,
 *        camera updates have variable time step
 * 
 */
void Engine::Update() {
      // Calculating dt
    engine->newTime = chrono::steady_clock::now();
    engine->timeTaken = engine->newTime - engine->currentTime;
    engine->deltaTime = float(engine->timeTaken.count()) * chrono::steady_clock::period::num / chrono::steady_clock::period::den;
    engine->currentTime = engine->newTime;
    engine->accumulator += engine->deltaTime;

    Camera::Update();
      // Only called when it is time (fixed time step)
    while (engine->accumulator >= engine->dt) {
          // Update objects
        Physics::UpdateGravity();
        Object_Manager::Update();
          // Update dt related variables
        engine->accumulator -= engine->dt;
        engine->time += engine->dt;
    }
}

/**
 * @brief Shutsdown systems and then engine
 * 
 */
void Engine::Shutdown() {
    Object_Manager::Shutdown();
    Graphics::Shutdown();
    Camera::Shutdown();
    delete engine;
}

/**
 * @brief Returns delta time (variable)
 * 
 * @return float Variable delta time
 */
float Engine::GetDeltaTime() {
    return engine->deltaTime;
}

/**
 * @brief Returns delta time (fixed)
 * 
 * @return float Fixed delta time
 */
float Engine::GetDt() { 
    return engine->dt;
}

/**
 * @brief Returns gravitational constant
 * 
 * @return double Gravitational constant
 */
double Engine::GetGravConst() {
    return engine->gravConst;
}