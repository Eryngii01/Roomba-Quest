#ifndef _UIGRAPHICSCOMPONENT_H
#define _UIGRAPHICSCOMPONENT_H

#include <string>
#include "GraphicsComponent.h"

//---------------------------------------------------------------------------------
// Implementation of GraphicsComponent for the player GameObject

class UIGraphicsComponent : public GraphicsComponent
{
public:
	UIGraphicsComponent(float x, float y, const char* printText = "", const char* graphic = "") :
		GraphicsComponent(nullptr, nullptr)
	{
		x_ = x;
		y_ = y;

		text_ = printText;

		if (graphic != NULL)
		{
			sprite_ = App::CreateSprite(graphic, 1, 1);
			sprite_->SetPosition(x_, y_);
			sprite_->SetScale(2.0f);
		}
	}

	void render();
	void update(float deltaTime);

private:
	float x_, y_;
	const char* text_;
	CSimpleSprite* sprite_;
};
#endif
