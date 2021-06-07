/**
 * @file component.hpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-06-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

// Defining object class
class Object;

/*! Component class */
class Component {
    public:
        /*! Types of components */
        enum CType {
            CModel,
            CPhysics,
            CTransform,
        };

        Component(CType type_);

        void SetParent(Object* object);
        Object* GetParent() const;

        CType GetCType() const;
    private:
        CType type;     //!< Type of component
        Object* parent; //!< Object that this component is attached to
};

typedef Component::CType CType; //!< Typedef for CType (used in other files)

#endif