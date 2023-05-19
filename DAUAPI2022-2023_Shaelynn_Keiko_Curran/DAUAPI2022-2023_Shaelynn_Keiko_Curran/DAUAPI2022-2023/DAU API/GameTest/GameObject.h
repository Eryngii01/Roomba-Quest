#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"

//*******************************************************************************************
// GameObject
//*******************************************************************************************
// A blank gameObject class meant to link components to make a very customizable entity, containing getters
// for the various component types that define it.

class GameObject
{
// TODO: Make bitmasks and layers to do raycasting???
// TODO: Give tags to GameObjects?
public:
    GameObject(InputComponent *input = nullptr, PhysicsComponent *physics = nullptr, GraphicsComponent *graphics = nullptr)
        : input_(input), physics_(physics), graphics_(graphics) {}

    InputComponent* getInputComponent()
    {
        return input_;
    };

    PhysicsComponent* getPhysicsComponent()
    {
        return physics_;
    };

    GraphicsComponent* getGraphicsComponent()
    {
        return graphics_;
    };

private:
    InputComponent *input_;
    PhysicsComponent *physics_;
    GraphicsComponent *graphics_;
};
#endif

