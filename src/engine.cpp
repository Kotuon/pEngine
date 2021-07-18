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
  // System //
#include "engine.hpp"
#include "graphics.hpp"
  // Object //
#include "object_manager.hpp"
#include "object.hpp"
  // Component //
#include "component.hpp"
#include "model_data_manager.hpp"
#include "physics.hpp"
  // Misc //
#include "camera.hpp"
#include "editor.hpp"
#include "file_reader.hpp"
#include "random.hpp"
#include "texture_manager.hpp"

static Engine* engine = nullptr; //!< Engine object

/**
 * @brief Initializes the engine and the systems in the engine
 * 
 * @return void
 */
void Engine::Initialize() {
      // Initializing engine
    engine = new Engine;
    if (!engine) {
        Trace::Message("Engine was not initialized.\n");
        return;
    }

    engine->lightPower = 1000.f;
    engine->lightPos = glm::vec3(4, 4, 0);
      // Reading settings from json
    File_Reader settings("settings.json");
    engine->presetName = settings.Read_String("preset");
    
    File_Reader preset("preset/" + engine->presetName);
    engine->gravConst = preset.Read_Double("gravConst");

      // Initializing sub systems
    if (!Model_Data_Manager::Initialize()) return;
    if (!Texture_Manager::Initialize()) return;
    if (!Camera::Initialize(settings)) return;
    if (!Graphics::Initialize(settings)) return;
    if (!Object_Manager::Initialize(preset)) return;
    if (!Random::Initialize()) return;
    if (!Editor::Initialize()) return;

      // Setting up variables used for dt
    engine->currentTime = std::chrono::steady_clock::now();
    engine->accumulator = 0.f;
    engine->time = 0.f;
    engine->isRunning = true;
}

/**
 * @brief Updates object and camera. Object updates have a fixed time step,
 *        camera updates have variable time step
 * 
 * @return void
 */
void Engine::Update() {
      // Calculating dt
    engine->newTime = std::chrono::steady_clock::now();
    engine->timeTaken = engine->newTime - engine->currentTime;
    engine->deltaTime = float(engine->timeTaken.count()) * 
        std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
    engine->currentTime = engine->newTime;
    engine->accumulator += engine->deltaTime;

    Editor::Update();
    Camera::Update();
      // Only called when it is time (fixed time step)
    while (engine->accumulator >= engine->dt) {
          // Update objects
        Object_Manager::Update();
          // Update dt related variables
        engine->accumulator -= engine->dt;
        engine->time += engine->dt;
    }
}

/**
 * @brief Shutdown systems and then engine
 * 
 * @return void
 */
void Engine::Shutdown() {
    if (!engine) return;
    
      // Shutdown sub systems
    Editor::Shutdown();
    Random::Shutdown();
    Object_Manager::Shutdown();
    Graphics::Shutdown();
    Camera::Shutdown();
    Texture_Manager::Shutdown();
    Model_Data_Manager::Shutdown();

      // Delete engine object
    delete engine;
    engine = nullptr;
}

/**
 * @brief Resets the objects in the engine
 * 
 * @return void
 */
void Engine::Restart() {
      // Removing all current objects
    Object_Manager::Shutdown();

      // Initializing object manager
    File_Reader settings("settings.json");
    engine->presetName = settings.Read_String("preset");

    File_Reader preset("preset/" + engine->presetName);
    if (!Object_Manager::Initialize(preset)) return;
}

/**
 * @brief Resets the engine to the given preset
 * 
 * @param presetName Given preset
 * @return void
 */
void Engine::Restart(std::string presetName) {
      // Removing all current objects
    Object_Manager::Shutdown();

      // Initializing object manager
    File_Reader settings("settings.json");
    engine->presetName = presetName;

    File_Reader preset("preset/" + engine->presetName);
    if (!Object_Manager::Initialize(preset)) return;
}

/**
 * @brief Returns delta time (variable)
 * 
 * @return float Variable delta time
 */
float Engine::GetDeltaTime() { return engine->deltaTime; }

/**
 * @brief Returns delta time (fixed)
 * 
 * @return float Fixed delta time
 */
float Engine::GetDt() { return engine->dt; }

/**
 * @brief Returns gravitational constant
 * 
 * @return double Gravitational constant
 */
double& Engine::GetGravConst() { return engine->gravConst; }

/**
 * @brief Returns the name of the current preset
 * 
 * @return std::string 
 */
std::string Engine::GetPresetName() { return engine->presetName; }

/**
 * @brief Returns reference to power of the light in the scene
 * 
 * @return float& 
 */
float& Engine::GetLightPower() { return engine->lightPower; }

/**
 * @brief Returns reference to the position of the light in the scene
 * 
 * @return glm::vec3& 
 */
glm::vec3& Engine::GetLightPos() { return engine->lightPos; }