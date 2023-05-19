#ifndef _PHYSICSCOMPONENT_H
#define _PHYSICSCOMPONENT_H

#include<tuple>
#include "InputComponent.h"


#define MAX_VELOCITY        0.2f

class World;
class InputComponent;

//*******************************************************************************************
// PhysicsComponent
//*******************************************************************************************
// Interface of a component for managing the physics of a GameObject. This includes data on the position in
// the world, the veolcity of objects, collision detection,and collision detection

class PhysicsComponent
{
public:
    PhysicsComponent(float width = 0, float height = 0, float x = 0, float y = 0, InputComponent* input = nullptr, int tag = -1)
        : tag_(tag), input_(input), x_(x), y_(y), width_(width), height_(height), velocityX_(0.2), velocityY_(0.2), colliderX1_(0),
        colliderY1_(0) {}
    ~PhysicsComponent() {}
    virtual void update(float deltaTime) = 0;
    virtual void onCollision(PhysicsComponent* other) = 0;
    virtual void collisionCallBack() = 0;

    std::tuple<float, float> getPosition()
    {
        std::tuple<float, float> coordinates(x_, y_);
        return coordinates;
    }

    virtual bool getStatus() = 0;

    // -1 for unset tag, 0 for terrain, 1 for obstacle
    int tag_;
    float x_, y_;
    float width_, height_;
    float velocityX_, velocityY_;
    float colliderX1_, colliderY1_;

protected:
    InputComponent* input_;
    virtual void invokeCollisions() = 0;
};
#endif

