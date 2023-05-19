#include "stdafx.h"
#include "UIGraphicsComponent.h"
#include "app\app.h"

void UIGraphicsComponent::update(float deltaTime)
{
	if (sprite_ != NULL)
	{
		sprite_->Update(deltaTime);
	}
}

void UIGraphicsComponent::render()
{
	if (text_ != NULL)
	{
		App::Print(x_, y_, text_, 1, 1, 1, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}
