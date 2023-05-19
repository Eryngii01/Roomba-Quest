#ifndef _PLAYERGRAPHICSCOMPONENT_H
#define _PLAYERGRAPHICSCOMPONENT_H

#define X_SPRITE_OFFSET            14     // Offset of the player sprite to successfully fit to the physics collider
#define Y_SPRITE_OFFSET            14    // Offset of the player sprite to successfully fit to the physics collider

#include "GraphicsComponent.h"

//---------------------------------------------------------------------------------
// Implementation of GraphicsComponent for the player GameObject

class PlayerGraphicsComponent : public GraphicsComponent
{
public:
    PlayerGraphicsComponent(InputComponent* input, PhysicsComponent* physics) : GraphicsComponent(input, physics)
    {
		std::tuple<float, float> coordinates = physics_->getPosition();
		float x = std::get<0>(coordinates);
		float y = std::get<1>(coordinates);

		// Example Sprite Code....
		sprite_ = App::CreateSprite(".\\TestData\\GooglyRoomba.bmp", 1, 1);
		sprite_->SetPosition(x - X_SPRITE_OFFSET, y + Y_SPRITE_OFFSET);
		float speed = 1.0f / 15.0f;
		sprite_->SetScale(1.7f);
		//------------------------------------------------------------------------

		angle_ = 0;
    }

    void render();
	void update(float deltaTime);

private:
	float angle_;
};
#endif
