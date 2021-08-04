/**
 * @file trace.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// std includes //
#include <iostream>
#include <cstdarg>

// Engine includes //
#include "trace.hpp"

static Trace* trace = nullptr; //!< Trace object

/**
 * @brief Initializes the trace system
 * 
 * @return void
 */
void Trace::Initialize() {
    trace = new Trace;

      // Opens output file
    trace->trace_stream.open(std::string(getenv("USERPROFILE")) + "/Documents/pEngine/trace.log", std::ofstream::out);
    if (!trace->trace_stream) std::cout << "Trace file wasn't opened successfully.\n";
}

/**
 * @brief Prints a message into the output file
 * 
 * @param message Message to be printed
 * @return void
 */
void Trace::Message(std::string message) {
    if (!trace->trace_stream) return;
    
    trace->trace_stream << message;
    std::cout << message;
}

/**
 * @brief Closes output file and deletes trace object
 * 
 * @return void
 */
void Trace::Shutdown() {
      // Closing output file
    if (trace->trace_stream) trace->trace_stream.close();

    delete trace;
    trace = nullptr;
}