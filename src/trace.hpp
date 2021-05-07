
#ifndef TRACE_HPP
#define TRACE_HPP

#include <string>
#include <fstream>

using namespace std;

class Trace {
    public:
        static void Init();
        static void Message(string message);
        static void Shutdown();
    private:
        fstream trace_stream;
};


#endif