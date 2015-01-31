#include "stdafx.h"
#include "player.h"


Player::Player(
	const std::string filepath,
	const Vector2 &position,
	const float rotation,
	const Vector2 &scale,
	Sprite *sprite,
	const std::string ID
	)
	:
	Object(filepath,position,rotation,scale,sprite,ID)
{
	std::cout << "Player Created\n";
	animationState = 0;
	startAnimationTime = -1; //timer not yet started
	animationDuration = 100; //default animation duration
}


Player::~Player()
{

}

void Player::updateState()
{
	//state 0 = stand
	//state 1 = jump
	//state 2 = walk1
	//state 3 = walk2
	//state 4 = walk3
	if (getActualVelocity().x == 0 && isGrounded)
	{
		animationState = 0;
		startAnimationTime = 0;//timer reset
	}
	else if (!isGrounded)
	{
		animationState = 1;
		startAnimationTime = 0;//timer reset
	}
	else if ((startAnimationTime > 0) && ((SDL_GetTicks() - startAnimationTime) > animationDuration) && animationState == 2)  //if timer has been started, check for walk2
	{
		animationState = 3;

	}
	else if ((startAnimationTime > 0) && ((SDL_GetTicks() - startAnimationTime) > (animationDuration * 2)) && animationState == 3)  //if timer has been started, check for walk2
	{
		animationState = 4;
	}
	else
	{
		if ((SDL_GetTicks() - startAnimationTime) > (animationDuration * 3) && startAnimationTime > 0)
		{
			//reset animation
			startAnimationTime = 0;
		}
		if (startAnimationTime == 0) //set timer if has not been set yet
		{
			animationState = 2;
			startAnimationTime = SDL_GetTicks();
		}
	}
}

int Player::getState()
{
	return animationState;
}