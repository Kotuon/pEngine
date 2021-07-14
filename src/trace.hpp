/**
 * @file trace.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once
#ifndef TRACE_HPP
#define TRACE_HPP

// std includes //
#include <string>
#include <fstream>

using namespace std;

/*! Trace class */
class Trace {
    public:
        static void Initialize();
        static void Message(string message);
        static void Shutdown();
    private:
        fstream trace_stream; //!< Output file
};


#endif