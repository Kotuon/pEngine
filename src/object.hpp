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

#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP

// std includes //
#include <unordered_map>
#include <string>

// Engine includes //
#include "component.hpp"
#include "trace.hpp"

/*! unordered_map tp relate CType enum to string (only used in GetComponent) */
static std::unordered_map<CType, std::string> CNames = {
    { CType::CModel, "Model" },
    { CType::CPhysics, "Physics" },
    { CType::CTransform, "Transform" }
};

/*! Object class */
class Object {
    public:
        Object();
        Object(const Object& other);
        Object(std::string filename);

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
                return nullptr;
            }
              // Cast found component into correct type
            return (T*)found->second;
        }

        template <typename T>
        void RemoveComponent() {
            auto found = components.find(T::GetCType());
            if (found == components.end()) return;

            delete found->second;
            found->second = nullptr;

            components.erase(found->first);
        }

        void SetId(int id_);
        int GetId() const;

        void SetName(std::string name_);
        std::string GetName() const;

        void SetTemplateName(std::string templateName_);
        std::string GetTemplateName() const;

        void Read(std::string objectFilename);
        void ReRead(std::string objectFilename);
        void Write();
        std::unordered_map<CType, Component*> GetComponentList();

        void Clear();
    private:
        std::unordered_map<CType, Component*> components; //!< List of components
        int id; //!< Location of object in object_manager
        std::string name; //!< Name of the object
        std::string templateName;
};

#endif