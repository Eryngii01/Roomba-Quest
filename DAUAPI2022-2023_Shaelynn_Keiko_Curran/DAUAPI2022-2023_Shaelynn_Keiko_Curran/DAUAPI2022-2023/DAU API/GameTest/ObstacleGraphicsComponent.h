#ifndef _OBSTACLEGRAPHICSCOMPONENT_H
#define _OBSTACLEGRAPHICSCOMPONENT_H

#define X_TILE_OFFSET            32     // Offset of the tiles to successfully fit in the screen
#define Y_TILE_OFFSET            24     // Offset of the tiles to successfully fit in the screen

#include "GraphicsComponent.h"

//enum
//{
//	ANIM_DIRTY,
//	ANIM_CLEANING,
//	ANIM_CLEANED
//};

//---------------------------------------------------------------------------------
// Implementation of GraphicsComponent for the player GameObject

class ObstacleGraphicsComponent : public GraphicsComponent
{
public:
	ObstacleGraphicsComponent(InputComponent* input, PhysicsComponent* physics) : GraphicsComponent(input, physics)
	{
		std::tuple<int, int> coordinates = physics->getPosition();
		x_ = std::get<0>(coordinates);
		y_ = std::get<1>(coordinates);

		// First create the sprite beneath the obstacle object
		sprite_ = App::CreateSprite(".\\TestData\\Floor.bmp", 1, 1);
		sprite_->SetPosition(x_ - X_TILE_OFFSET, y_ + Y_TILE_OFFSET);
		sprite_->SetScale(2.0f);

		// Create a random obstacle to  lay on top
		int type = rand() % 2;

		switch (type)
		{
		case 0:
			sprite2_ = App::CreateSprite(".\\TestData\\HugeStackOfBooks.bmp", 1, 1);
			break;
		case 1:
			sprite2_ = App::CreateSprite(".\\TestData\\StackOfBooks.bmp", 1, 1);
			break;
		}
		sprite2_->SetPosition(x_ - X_TILE_OFFSET, y_ + Y_TILE_OFFSET);
		sprite2_->SetScale(2.0f);
	}

	void render();
	void update(float deltaTime);

private:
	// An obstacle is a static GameObject, so position data from the physics component will only need to be fetched once
	int x_, y_;
	CSimpleSprite* sprite2_;
};
#endif

