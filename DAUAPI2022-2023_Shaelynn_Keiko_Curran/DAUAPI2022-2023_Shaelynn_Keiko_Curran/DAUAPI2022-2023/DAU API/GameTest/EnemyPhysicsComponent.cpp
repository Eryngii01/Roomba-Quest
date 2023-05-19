#include "stdafx.h"
#include "EnemyPhysicsComponent.h"

void EnemyPhysicsComponent::update(float deltaTime)
{
	// First update the position of the object
	x_ += velocityX_ * deltaTime;

	// If the enemy collides with the walls, it will switch directions
	int minX = x_ - width_;
	int maxY = y_ + height_;

	// Check if the object has gone outside the screen boundaries, acting as a collision
	if (x_ >= APP_VIRTUAL_WIDTH)
	{
		x_ = APP_VIRTUAL_WIDTH - 1.0f;
		input_->setState(ControllerState::STATE_SEEKING);
	}
	else if (minX <= 0.0f)
	{
		x_ = width_ + 1.0f;
		input_->setState(ControllerState::STATE_SEEKING);
	}
}
