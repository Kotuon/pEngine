/**
 * @file object.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef OBJECT_HPP
#define OBJECT_HPP

// std includes //
#include <unordered_map>
#include <string>

// Engine includes //
#include "component.hpp"
#include "trace.hpp"

using namespace std;

/*! unordered_map tp relate CType enum to string (only used in GetComponent) */
static unordered_map<CType, string> CNames = {
    { CType::CModel, "Model" },
    { CType::CPhysics, "Physics" },
    { CType::CTransform, "Transform" }
};

/*! Object class */
class Object {
    public:
        Object();
        Object(const Object& other);
        Object(string filename);

        Object* Clone() const;
    
        void Update();

        void AddComponent(Component* component);

        /**
         * @brief Get a component of the object (const)
         * 
         * @tparam T Component class to return
         * @param type Type of component
         * @return T* Pointer to the component
         */
        template <typename T>
        T* GetComponent() const {
              // Searching for component using the type (enum as int)
            auto found = components.find(T::GetCType());
            if (found == components.end()) {
                Trace::Message("Component not found." + CNames[T::GetCType()] + "\n");
                return nullptr;
            }
              // Cast found component into correct type
            return (T*)found->second;
        }        
        
        /**
         * @brief Get a component of the object
         * 
         * @tparam T Component class to return
         * @param type Type of component
         * @return T* Pointer to the component
         */
        template <typename T>
        T* GetComponent() {
              // Searching for component using the type (enum as int)
            auto found = components.find(T::GetCType());
            if (found == components.end()) {
                Trace::Message("Component not found." + CNames[T::GetCType()] + "\n");
                return nullptr;
            }
              // Cast found component into correct type
            return (T*)found->second;
        }

        void SetId(unsigned id_);
        unsigned GetId() const;

        void SetName(string name_);
        string GetName() const;

        void ReadObject(string objectFilename);
    private:
        unordered_map<CType, Component*> components; //!< List of components
        unsigned id; //!< Location of object in object_manager
        string name; //!< Name of the object
};

#endif