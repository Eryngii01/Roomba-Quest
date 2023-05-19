#ifndef _TILEGRAPHICSCOMPONENT_H
#define _TILEGRAPHICSCOMPONENT_H

#define X_TILE_OFFSET            32     // Offset of the tiles to successfully fit in the screen
#define Y_TILE_OFFSET            24     // Offset of the tiles to successfully fit in the screen

#include "GraphicsComponent.h"

//---------------------------------------------------------------------------------
// Implementation of GraphicsComponent for the player GameObject

class TileGraphicsComponent : public GraphicsComponent
{
public:
	TileGraphicsComponent(InputComponent* input, PhysicsComponent* physics) : GraphicsComponent(input, physics)
	{
		std::tuple<int, int> coordinates = physics->getPosition();
		x_ = std::get<0>(coordinates);
		y_ = std::get<1>(coordinates);

		// Example Sprite Code....
		sprite_ = App::CreateSprite(".\\TestData\\Floor.bmp", 1, 1);
		sprite_->SetPosition(x_ - X_TILE_OFFSET, y_ + Y_TILE_OFFSET);
		float speed = 1.0f / 15.0f;
		/*sprite_->CreateAnimation(ANIM_DIRTY, speed, { 0,1,2,3,4,5,6,7 });
		sprite_->CreateAnimation(ANIM_CLEANING, speed, { 8,9,10,11,12,13,14,15 });
		sprite_->CreateAnimation(ANIM_CLEANED, speed, { 16,17,18,19,20,21,22,23 });*/
		sprite_->SetColor(0.4f, 0.2f, 0.0f);
		sprite_->SetScale(2.0f);
		//------------------------------------------------------------------------
	}

	void render();
	void update(float deltaTime);

private:
	// A tile is a static GameObject, so position data from the physics component will only need to be fetched once
	int x_, y_;
	bool isDirty_ = true;
};
#endif

