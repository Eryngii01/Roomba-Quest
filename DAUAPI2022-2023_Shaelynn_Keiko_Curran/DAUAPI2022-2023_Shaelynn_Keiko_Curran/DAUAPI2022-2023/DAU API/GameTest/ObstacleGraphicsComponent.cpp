#include "stdafx.h"
#include "ObstacleGraphicsComponent.h"
#include "app\app.h"

void ObstacleGraphicsComponent::render()
{
	sprite_->Draw();
	sprite2_->Draw();
}

void ObstacleGraphicsComponent::update(float deltaTime)
{
	sprite_->Update(deltaTime);
	sprite2_->Update(deltaTime);
}
