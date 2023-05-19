#include "stdafx.h"
#include "TimerGraphicsComponent.h"
#include "app\app.h"

#include<string>

void TimerGraphicsComponent::update(float deltaTime)
{
	// A very broken/imprecise way of simulating time at the mercy of deltaTime
	// Other options would relinquish control to the OS, but these could not be explored in time.
	LevelState state = level_->getState();

	if (seconds_ > 0 && state == LevelState::LEVEL_ACTIVE)
	{
		counter_ += deltaTime;

		if (counter_ >= speed_)
		{
			counter_ = 0;
			seconds_--;
		}
	} 
	else if (!timeOut_ && state == LevelState::LEVEL_ACTIVE)
	{
		// Notify the level that the time has run out
		level_->loseLevel();
		timeOut_ = true;
	}
}

void TimerGraphicsComponent::render()
{
	std::string s = std::to_string(seconds_) + "s Remaining";
	App::Print(x_, y_, s.c_str(), 1, 1, 1, GLUT_BITMAP_TIMES_ROMAN_24);
}
