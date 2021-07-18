/**
 * @file random.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-07-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#ifndef RANDOM_HPP
#define RANDOM_HPP

// std includes //
#include <random>

// Library includes //
#include <vec3.hpp>

/*! Random class */
class Random {
    public:
        static bool Initialize();
        static void Shutdown();
        static glm::vec3 random_vec3(float low, float high);
        static float random_float(float low, float high);
    private:
    std::random_device rd; //!< Random device
};

#endif