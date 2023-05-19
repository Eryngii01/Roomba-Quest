#ifndef _OBSTACLEPHYSICSCOMPONENT_H
#define _OBSTACLEPHYSICSCOMPONENT_H
#include "PhysicsComponent.h"

//---------------------------------------------------------------------------------
// Implementation of GraphicsComponent for the player GameObject

class ObstaclePhysicsComponent : public PhysicsComponent
{
public:
    ObstaclePhysicsComponent(float width = 0, float height = 0, float x = 0, float y = 0, InputComponent* input = nullptr)
        :PhysicsComponent(width, height, x, y, input)
    {
        tag_ = 1;
    }

    void update(float deltaTime);

    // TODO: Redundant, but a shortcut. Polish this later
    bool getStatus() 
    {
        return false;
    };

    void onCollision(PhysicsComponent* other);
    void collisionCallBack() {};

protected:
    void invokeCollisions() {};
};
#endif

