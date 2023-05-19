#include "stdafx.h"
#include "PlayerPhysicsComponent.h"
#include "app\app.h"

#include <limits>

void PlayerPhysicsComponent::update(float deltaTime)
{
	ControllerState state = input_->getState();

	switch (state)
	{
	case ControllerState::STATE_MOVING:
		// First update the position of the object
		x_ += velocityX_ * deltaTime;
		y_ += velocityY_ * deltaTime;

		// TODO: Fix the rubberbanding effect that occurs when the player collides with the boundaries
		correctPosition();

		this->invokeCollisions();
		break;
	case ControllerState::STATE_SEEKING:
		// Wait an allotted amount of time for Roomba reconfiguration
		correctPosition();

		// First fetch the player input
		std::tuple<float, float> inputCoord = input_->getInput();
		float x = std::get<0>(inputCoord);
		float y = std::get<1>(inputCoord);

		// Set the x, y coordinate velocities normalized by the max velocity
		velocityX_ = x * MAX_VELOCITY;
		velocityY_ = y * MAX_VELOCITY;

		break;
	}
}

void PlayerPhysicsComponent::correctPosition()
{
	int minX = x_ - width_;
	int maxY = y_ + height_;

	// Check if the object has gone outside the screen boundaries, acting as a collision
	if (x_ >= APP_VIRTUAL_WIDTH)
	{
		// Correct the player position
		x_ = APP_VIRTUAL_WIDTH - 1.0f;
		input_->setState(ControllerState::STATE_SEEKING);
	}
	else if (minX <= 0.0f)
	{
		x_ = width_ + 1.0f;
		input_->setState(ControllerState::STATE_SEEKING);
	}
	else if (maxY >= APP_VIRTUAL_HEIGHT)
	{
		y_ = APP_VIRTUAL_HEIGHT - (height_ + 1.0f);
		input_->setState(ControllerState::STATE_SEEKING);
	}
	else if (y_ <= 0.0f)
	{
		y_ = 1.0f;
		input_->setState(ControllerState::STATE_SEEKING);
	}
}

void PlayerPhysicsComponent::onCollision(PhysicsComponent* other)
{
	// Obstacles act as physical boundaries against the player, thus causing the spatial recalculation
	if (other->tag_ == 1)
	{
		input_->setState(ControllerState::STATE_SEEKING);
	}
}

void PlayerPhysicsComponent::collisionCallBack()
{
	level_->cleanTerrain(input_);
}

// AABB - AABB and AABB - Circle Collision detection
void PlayerPhysicsComponent::invokeCollisions()
{
	for (int i = 0; i < colliders_.size(); i++)
	{
		PhysicsComponent* other = colliders_[i];

		bool result = false;

		switch (other->tag_)
		{
		case 0:
			// Regular terrain
			result = checkInternalCollision(other);
			break;
		case 1:
			result = checkAABBCollision(other);
			// Obstacle
			break;
		}

		if (result)
		{
			other->onCollision(this);
			this->onCollision(other);
		}
	}
}


bool PlayerPhysicsComponent::checkInternalCollision(PhysicsComponent* other)
{
	int width = other->width_, height = other->height_;

	// Get top left point
	int x1 = other->x_, y1 = other->y_;
	int x2 = x1 - width, y2 = y1 + height;

	// Check that all vertices are within the other's boundaries
	bool vertices1 = (x_ >= x2) && (x_ <= x1) && (y_ >= y1) && (y_ <= y2);
	bool vertices2 = (x_ - width_ >= x2) && (x_ - width_ <= x1) && (y_ + height_ <= y2) && (y_ + height_ >= y1);

	// collision x-axis?
	//bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
	//	two.Position.x + two.Size.x >= one.Position.x;
	//// collision y-axis?
	//bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
	//	two.Position.y + two.Size.y >= one.Position.y;
	// collision only if on both axes

	return (vertices1 && vertices2);
}

bool PlayerPhysicsComponent::checkAABBCollision(PhysicsComponent* other)
{
	int width = other->width_, height = other->height_;

	// Get top left point
	int x1 = other->x_, y1 = other->y_;

	// Search for x-axis collision
	bool collisionX = x1 + width >= x_ && x_ + width_ >= x1;

	// Search for y-axis collision
	bool collisionY = y1 + height >= y_ && y_ + height_ >= y1;

	// collision only if on both axes
	return collisionX && collisionY;

	// If both axes overlap, notify the GameObject of the collision and act accordingly
	return (collisionX && collisionY);
}

