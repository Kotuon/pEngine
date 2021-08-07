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

/*! Object class */
class Object {
    public:
        Object();
        Object(const Object& other);

        Object* Clone() const;
    
        void Update();

        void AddComponent(Component* component);

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

        /**
         * @brief Removes component from object
         * 
         * @tparam T 
         */
        template <typename T>
        void RemoveComponent() {
              // Searching for component using the type (enum as int)
            auto found = components.find(T::GetCType());
            if (found == components.end()) return;
              // Delete component
            delete found->second;
            found->second = nullptr;
              // Remove pointer from map
            components.erase(found->first);
        }

        void SetId(int id_);
        int GetId() const;

        void SetName(std::string name_);
        std::string GetName() const;
        std::string& GetNameRef();

        void SetTemplateName(std::string templateName_);
        std::string GetTemplateName() const;

        bool Read(std::string objectFilename);
        bool ReRead(std::string objectFilename);
        void Write(std::string filePath);
        std::unordered_map<CType, Component*> GetComponentList();

        void Clear();
    private:
            /**
         * @brief Get a component of the object (const)
         * 
         * @tparam T Component class to return
         * @param type Type of component
         * @return T* Pointer to the component
         */
        template <typename T>
        T* GetComponentConst() const {
              // Searching for component using the type (enum as int)
            auto found = components.find(T::GetCType());
            if (found == components.end()) {
                return nullptr;
            }
              // Cast found component into correct type
            return (T*)found->second;
        }
    private:
        std::unordered_map<CType, Component*> components; //!< List of components
        std::string name;                                 //!< Name of the object
        std::string templateName;                         //!< Name  of the template file used
        int id;                                           //!< Location of object in object_manager
};

#endif