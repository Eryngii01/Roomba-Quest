#ifndef _TILEPHYSICSCOMPONENT_H
#define _TILEPHYSICSCOMPONENT_H
#include "PhysicsComponent.h"

//---------------------------------------------------------------------------------
// Implementation of GraphicsComponent for the player GameObject

class TilePhysicsComponent : public PhysicsComponent
{
public:
    TilePhysicsComponent(float width = 0, float height = 0, float x = 0, float y = 0, InputComponent* input = nullptr): 
        PhysicsComponent(width, height, x, y, input)
    {
        tag_ = 0;
    }
    void update(float deltaTime) {};

    bool getStatus()
    {
        return isDirty_;
    }

    void onCollision(PhysicsComponent* other);
    void collisionCallBack() {};

protected:
    void invokeCollisions() {};
    bool isDirty_ = true;
};
#endif

