
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <unordered_map>

#include "component.hpp"
#include "trace.hpp"

using namespace std;

class Object {
    public:
        void Update(float);

        void AddComponent(Component* component);

        template <typename T>
        T* GetComponent(CType type) const {
            auto found = components.find(type);
            if (found == components.end()) {
                Trace::Message("Component not found.\n");
                return nullptr;
            }

            return (T*)found->second;
        }

        void SetId(unsigned id_);
        unsigned GetId() const;
    private:
        unordered_map<CType, Component*> components;
        unsigned id;
};

#endif