#ifndef _INPUTCOMPONENT_H
#define _INPUTCOMPONENT_H

#include<tuple>

enum class ControllerState
{
	STATE_MOVING,
	STATE_SEEKING,
	STATE_LEVEL_OVER
};

//*******************************************************************************************
// InputComponent
//*******************************************************************************************
// Interface of a component for managing player input

class InputComponent
{
public:
	InputComponent() : state_(ControllerState::STATE_SEEKING), x_(0), y_(0) {};
    ~InputComponent() {};
    virtual void update() = 0;

	ControllerState getState()
	{
		return state_;
	}

	void setState(ControllerState state)
	{
		state_ = state;
	}

	std::tuple<float, float> getInput()
	{
		std::tuple<float, float> coordinates(x_, y_);
		return coordinates;
	}

protected:
	//*******************************************************************************************
	// State & Input
	//*******************************************************************************************
	ControllerState state_;
	float x_, y_;
};
#endif

