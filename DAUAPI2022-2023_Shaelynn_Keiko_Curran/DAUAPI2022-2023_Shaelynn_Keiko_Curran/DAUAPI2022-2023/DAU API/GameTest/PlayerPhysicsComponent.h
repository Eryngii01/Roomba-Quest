#ifndef _PLAYERPHYSICSCOMPONENT_H
#define _PLAYERPHYSICSCOMPONENT_H

#include "Level.h"
#include "PhysicsComponent.h"

#include <vector>

//*******************************************************************************************
// PlayerPhysicsComponent
//*******************************************************************************************
// Implementation of PhysicsComponent for the player GameObject, handling all collisions that occur
// between the player gameObject and others.

class PlayerPhysicsComponent : public PhysicsComponent
{
public:
	PlayerPhysicsComponent(Level* level, float width, float height, float x, float y, InputComponent* input, 
		std::vector<PhysicsComponent*> colliders) : PhysicsComponent(width, height, x, y, input)
	{
		level_ = level;
		colliders_ = colliders;
	}
    void update(float deltaTime);

	// TODO: Redundant, but a shortcut. Fix this later
	bool getStatus()
	{
		return false;
	};

	void correctPosition();

	void onCollision(PhysicsComponent* other);
	void collisionCallBack();

protected:
	void invokeCollisions();
	bool checkInternalCollision(PhysicsComponent* collider);
	bool checkAABBCollision(PhysicsComponent* collider);

private:
	std::vector<PhysicsComponent*> colliders_;
	Level* level_;
};
#endif
