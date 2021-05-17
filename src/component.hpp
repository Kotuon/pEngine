
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class Object;

class Component {
    public:
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
        CType type;
        Object* parent;
};

typedef Component::CType CType;

#endif