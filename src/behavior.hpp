
#ifndef BEHAVIOR_HPP
#define BEHAVIOR_HPP

// std includes //
#include <vector>

// Engine includes //
#include "component.hpp"
#include "file_reader.hpp"

using namespace std;

class Behavior : public Component {
    public:
        Behavior();
        Behavior(const Behavior& other);
        Behavior(File_Reader& reader);
        Behavior* Clone() const;

        void Update();

        void Read(File_Reader& reader);

        static CType GetCType();
    private:
        vector<unsigned> behaviorList;
};

#endif