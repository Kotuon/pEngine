
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <unordered_map>
#include <string>

#include "component.hpp"
#include "trace.hpp"

using namespace std;

static unordered_map<CType, string> CNames = {
    { CType::CModel, "Model" },
    { CType::CPhysics, "Physics" },
    { CType::CTransform, "Transform" }
};

class Object {
    public:
        Object();
        Object(const Object& other);
        Object(string filename);

        Object* Clone() const;
    
        void Update();

        void AddComponent(Component* component);

        template <typename T>
        T* GetComponent(CType type) const {
            auto found = components.find(type);
            if (found == components.end()) {
                Trace::Message("Component not found." + CNames[type] + "\n");
                return nullptr;
            }

            return (T*)found->second;
        }        
        
        template <typename T>
        T* GetComponent(CType type) {
            auto found = components.find(type);
            if (found == components.end()) {
                Trace::Message("Component not found." + CNames[type] + "\n");
                return nullptr;
            }

            return (T*)found->second;
        }

        void SetId(unsigned id_);
        unsigned GetId() const;

        void SetName(string name_);
        string GetName() const;

        void ReadObject(string objectFilename);
    private:
        unordered_map<CType, Component*> components;
        unsigned id;
        string name;
};

#endif