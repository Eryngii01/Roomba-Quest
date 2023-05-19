#include "stdafx.h"
#include "TileGraphicsComponent.h"
#include "app\app.h"

#include<string>

void TileGraphicsComponent::update(float deltaTime)
{
	if (!physics_->getStatus() && isDirty_)
	{
		sprite_->SetColor(1, 1, 1);
		isDirty_ = false;
	}
}

void TileGraphicsComponent::render()
{
	sprite_->Draw();

	// Draw the physics colliders for better visibility

	// Fetch the current player position
	std::tuple<float, float> coordinates = physics_->getPosition();
	float x = std::get<0>(coordinates) - physics_->width_;
	float y = std::get<1>(coordinates) + physics_->height_;

	// Fetch the width and height
	float x2 = x + physics_->width_;
	float y2 = y - physics_->height_;

	// Draw the top
	App::DrawLine(x, y, x2, y, 0, 0, 0);
	// Draw the left
	App::DrawLine(x, y, x, y2, 0, 0, 0);
	// Draw the right
	App::DrawLine(x2, y, x2, y2, 0, 0, 0);
	// Draw the bottom
	App::DrawLine(x, y2, x2, y2, 0, 0, 0);
}
