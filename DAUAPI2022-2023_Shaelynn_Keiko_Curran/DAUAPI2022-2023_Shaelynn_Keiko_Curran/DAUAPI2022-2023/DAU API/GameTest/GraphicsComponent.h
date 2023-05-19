#ifndef _GRAPHICSCOMPONENT_H
#define _GRAPHICSCOMPONENT_H

#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "app\app.h"

//*******************************************************************************************
// GraphicsComponent
//*******************************************************************************************
// Interface of a component for managing graphics for a GameObject.

class GraphicsComponent
{
public:
    GraphicsComponent(InputComponent *input = nullptr, PhysicsComponent *physics = nullptr) : input_(input), physics_(physics), sprite_() {};
    ~GraphicsComponent() {};

    // Render and update functions to be called every frame
    virtual void render() = 0;
    virtual void update(float deltaTime) = 0;

protected:
    // The components were designed with coupling for now, but as the project gets larger, less coupling would be easier
    // to manage and reason code correctness.
    InputComponent* input_; // Graphics needs to check character state to set the correct animation
    PhysicsComponent* physics_; // Graphics needs to check physics to see what animation to play

    // The graphics components are mainly centered around rendering sprites
    CSimpleSprite* sprite_;
};
#endif
