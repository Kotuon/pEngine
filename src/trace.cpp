
#include <iostream>
#include <fstream>
#include <cstdarg>

#include "trace.hpp"

using namespace std;

static Trace trace;

void Trace::Init() {
    trace.trace_stream.open("output/trace.log", std::ofstream::out);

    if (!trace.trace_stream) cout << "File wasn't opened successfully.";
}

void Trace::Message(string message) {
    if (!trace.trace_stream) return;

    trace.trace_stream << message;
    cout << message;
}

void Trace::Shutdown() {
    if (trace.trace_stream) trace.trace_stream.close();
}