#include "stdafx.h"
#include "PlayerInputComponent.h"
#include "InputComponent.h"
#include "app\app.h"

void PlayerInputComponent::update()
{
	x_ = App::GetController().GetLeftThumbStickX();
	y_ = App::GetController().GetLeftThumbStickY();

	switch (state_)
	{
	case ControllerState::STATE_MOVING:
		// Cannot do anything until you collide with something for now
		// TODO: "A" button to stall movement
		break;
	case ControllerState::STATE_SEEKING:
		// The movement direction will be rendered until the user presses "A", finalizing the target direction and 
		// setting the gameObject on its path.
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true)) {
			state_ = ControllerState::STATE_MOVING;
		}
		break;
	case ControllerState::STATE_LEVEL_OVER:
		if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true)) {
			level_->nextLevel();
		}
		break;
	}
}
