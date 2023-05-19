#ifndef _ENEMYPHYSICSCOMPONENT_H
#define _ENEMYPHYSICSCOMPONENT_H

#include "Level.h"
#include "PhysicsComponent.h"

#include <vector>

//---------------------------------------------------------------------------------
// Implementation of PhysicsComponent for the enemy type GameObject

class EnemyPhysicsComponent : public PhysicsComponent
{
public:
	EnemyPhysicsComponent(float speed, float width = 0, float height = 0, float x = 0, float y = 0, InputComponent* input = nullptr)
		:PhysicsComponent(width, height, x, y, input)
	{
		tag_ = 1;
		velocityX_ = speed;
	}

	void update(float deltaTime);

	void onCollision(PhysicsComponent* other) {};
	void collisionCallBack() {};
};
#endif

