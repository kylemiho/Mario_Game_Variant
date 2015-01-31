#pragma once

#include "globals.h"
#include "object.h"

class Sprite;
class Object;

class Player : public Object
{
	public:
		Player(
			const std::string filepath,
			const Vector2 &position,
			const float rotation,
			const Vector2 &scale,
			Sprite *sprite,
			const std::string ID
			);
			~Player();
			void updateState();
			int getState();
	protected:
		int animationState;
		unsigned startAnimationTime;
		unsigned animationDuration; //time in milliseconds
};
