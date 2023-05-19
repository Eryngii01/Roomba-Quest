#ifndef _PLAYERINPUTCOMPONENT_H
#define _PLAYERINPUTCOMPONENT_H

#include "Level.h"
#include "InputComponent.h"

//---------------------------------------------------------------------------------
// Implementation of InputComponent for player GameObject

class PlayerInputComponent : public InputComponent
{
public:
    PlayerInputComponent(Level* level) : InputComponent()
    {
        level_ = level;
        state_ = ControllerState::STATE_SEEKING;
    }
    void update();

private:
    Level* level_;
};
#endif