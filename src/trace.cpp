
#include <iostream>
#include <fstream>
#include <cstdarg>

#include "trace.hpp"

using namespace std;

static fstream trace_stream;

void TraceInit() {
    trace_stream.open("output/trace.log", std::ofstream::out);

    if (!trace_stream) cout << "File wasn't opened successfully.";
}

void TraceMessage(string message) {
    if (!trace_stream) return;

    trace_stream << message << endl;
}