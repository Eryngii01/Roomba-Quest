#ifndef _TIMERGRAPHICSCOMPONENT_H
#define _TIMERGRAPHICSCOMPONENT_H

#include "Level.h"
#include "GraphicsComponent.h"

//---------------------------------------------------------------------------------
// Implementation of GraphicsComponent for the player GameObject

class TimerGraphicsComponent : public GraphicsComponent
{
public:
	TimerGraphicsComponent(Level* level, float x, float y, int speed, int seconds, InputComponent* input = nullptr, 
		PhysicsComponent* physics = nullptr) : GraphicsComponent(input, physics)
	{
		level_ = level;
		timeOut_ = false;
		x_ = x;
		y_ = y;
		speed_ = speed;
		seconds_ = seconds;

		counter_ = 0;
	}

	void render();
	void update(float deltaTime);

private:
	// Kept for notifying level when the time is up
	Level* level_;
	bool timeOut_;
	float x_, y_;
	float counter_;
	int speed_, seconds_;
};
#endif
