/**
 * @file component.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Engine includes //
#include "component.hpp"

/**
 * @brief Creates a new component of given type
 * 
 * @param type_ Type of component
 */
Component::Component(CType type_) : type(type_) {}

/**
 * @brief Sets the parent of the component
 * 
 * @param object The object that is the parent
 */
void Component::SetParent(Object* object) { parent = object; }

/**
 * @brief Gets the parent of the component
 * 
 * @return Object* The parent
 */
Object* Component::GetParent() const { return parent; }

/**
 * @brief Gets the type of the component
 * 
 * @return CType Type of the component
 */
CType Component::GetCType() const { return type; }