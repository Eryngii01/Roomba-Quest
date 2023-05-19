#include "stdafx.h"
#include "TilePhysicsComponent.h"

void TilePhysicsComponent::onCollision(PhysicsComponent* other)
{
	// The other object is guaranteed to be the player, so clean this tile
	// if it hasn't been already and report back to the player.
	if (isDirty_)
	{
		isDirty_ = false;
		other->collisionCallBack();
	}
	

}

