#include "stdafx.h"
#include "PlayerGraphicsComponent.h"
#include "app\app.h"

#include<string>
#include<cmath>
#include<math.h>

void PlayerGraphicsComponent::update(float deltaTime)
{
	sprite_->Update(deltaTime);

	std::tuple<float, float> coordinates = physics_->getPosition();
	float x = std::get<0>(coordinates);
	float y = std::get<1>(coordinates);

	ControllerState state = input_->getState();

	switch (state)
	{
	case ControllerState::STATE_MOVING:
		sprite_->SetPosition(x - X_SPRITE_OFFSET, y + Y_SPRITE_OFFSET);

		break;
	case ControllerState::STATE_SEEKING:
		sprite_->SetPosition(x - X_SPRITE_OFFSET, y + Y_SPRITE_OFFSET);
		// sprite_->SetAnimation(ANIM_IDLE);

		// Fetch the current player position
		std::tuple<float, float> coordinates = physics_->getPosition();
		float inputX = std::get<0>(coordinates) - X_SPRITE_OFFSET;
		float inputY = std::get<1>(coordinates) + Y_SPRITE_OFFSET;

		// Full angle revolution is achieved at 6.28f

		// Calculate the angle that the player should be facing 
		float angleDegrees = std::acos(inputY / sqrt((inputX * inputX) + (inputY * inputY)));
		float angleRadian = angleDegrees * (PI / 180);

		// Full angle revolution is achieved at 6.28f
		// float finalAngle = fmod((angle / 360.0), 6.28f);
		
		sprite_->SetAngle(angleDegrees * (PI / 180));
		break;
	}
}

void PlayerGraphicsComponent::render()
{
	sprite_->Draw();

	//// Draw the physics colliders

	//// Fetch the current player position
	//std::tuple<float, float> coordinates = physics_->getPosition();
	//float x = std::get<0>(coordinates) - physics_->width_;
	//float y = std::get<1>(coordinates) + physics_->height_;

	//// Fetch the width and height
	//float x2 = x + physics_->width_;
	//float y2 = y - physics_->height_;

	//// Draw the top
	//App::DrawLine(x, y, x2, y, 1.0f, 1.0f, 1.0f);
	//// Draw the left
	//App::DrawLine(x, y, x, y2, 1.0f, 1.0f, 1.0f);
	//// Draw the right
	//App::DrawLine(x2, y, x2, y2, 1.0f, 1.0f, 1.0f);
	//// Draw the bottom
	//App::DrawLine(x, y2, x2, y2, 1.0f, 1.0f, 1.0f);

	ControllerState state = input_->getState();

	// Draw the sprite, then the line over it
	/*sprite_->Draw();*/

	if (state == ControllerState::STATE_SEEKING)
	{
		// Fetch the current player position
		std::tuple<float, float> coordinates = physics_->getPosition();
		float x = std::get<0>(coordinates) - X_SPRITE_OFFSET;
		float y = std::get<1>(coordinates) + Y_SPRITE_OFFSET;

		// Fetch the player input to calculate the second set of coordinates
		std::tuple<float, float> inputCoord = input_->getInput();
		float inputX = std::get<0>(inputCoord);
		float inputY = std::get<1>(inputCoord);

		float x2 = x + (100 * inputX);
		float y2 = y + (100 * inputY);

		App::DrawLine(x, y, x2, y2, 0.6f, 0.2f, 1.0f);
	}
}
