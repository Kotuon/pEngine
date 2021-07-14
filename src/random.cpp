/**
 * @file random.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Engine includes //
#include "random.hpp"
#include "trace.hpp"

static Random* random = nullptr; //!< Random object

/**
 * @brief Initializes the random system
 * 
 * @return true 
 * @return false 
 */
bool Random::Initialize() {
      // Initializing random
    random = new Random;
    if (!random) {
        Trace::Message("Random failed to initialize.");
        return false;
    }

    return true;
}

/**
 * @brief Delete the random object
 * 
 * @return void
 */
void Random::Shutdown() {
    if (!random) return;

    delete random;
    random = nullptr;
}

/**
 * @brief Creates a random vec3
 * 
 * @param low Lower boundary in random gen
 * @param high Upper boundary in random gen
 * @return vec3 
 */
vec3 Random::random_vec3(float low, float high) {
      // Setup random gen
    mt19937 gen(random->rd());
    uniform_real_distribution<> dist(low, high);
      // Gen random vec3
    vec3 result_vec3 = { dist(gen), dist(gen), dist(gen) };
    return result_vec3;
}

/**
 * @brief Creates random float
 * 
 * @param low Lower boundary in random gen
 * @param high Upper boundary in random gen
 * @return float 
 */
float Random::random_float(float low, float high) {
      // Setup random gen
    mt19937 gen(random->rd());
    uniform_real_distribution<> dist(low, high);
      // Gen random float
    return dist(gen);
}