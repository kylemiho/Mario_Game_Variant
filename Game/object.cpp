#include "stdafx.h" //helps manage compiling, similar to "makefile"
#include "object.h" //includes our object header file
#include "scene.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#pragma comment(lib, "SDL2.lib")   //used to get the SDL2 library
#pragma comment (lib, "SDL2main.lib") //need to LINK 3 libraries
#pragma comment(lib, "SDL2test.lib") //libraries contain the actual functions we use, header files contain the function info

//std::vector<Object*> Object::allObjects; //constructor for static global in h file
Object::~Object()
{

}

Object::Object(
	const std::string filepath,
	const Vector2 &position,
	const float rotation,
	const Vector2 &scale,
	Sprite *sprite,
	const std::string ID)
	:
	window(window),
	filepath(filepath),
	position(position),
	rotation(rotation),
	scale(scale),
	ID(ID),
	scene(scene)
{
	//variable initializations
	goalVelocity = Vector2(0, 0);
	actualVelocity = Vector2(0, 0);
	isGrounded = true;
	jumpStart = 0;
	deltaTime = 0;
	lastFrame = SDL_GetTicks();
	jumpAnimation = false;
	facingRight = true;
	animationState = 0;

	SDL_Rect tempClippingArea;
	if (sprite) //NULL clipping area means sprite sheet N/A, so use entire sheet
	{
		tempClippingArea.x = sprite->x;
		tempClippingArea.y = sprite->y;
		tempClippingArea.w = sprite->w;
		tempClippingArea.h = sprite->h;
	}
	else //clip entire png file
	{
		tempClippingArea.x = 0;
		tempClippingArea.y = 0;
		tempClippingArea.w = 0;
		tempClippingArea.h = 0;
	}

	clippingArea.push_back(tempClippingArea);
	//Initialize PNG loading
	SDL_Surface *s = IMG_Load(filepath.c_str());

	SDL_Texture *tempTexture = SDL_CreateTextureFromSurface(globals::renderer, s); //texture needed to render to screen
	texture.push_back(tempTexture);

	if (s == NULL)
	{
		std::cout << "Failed to load image " << filepath << "\n";
		return;
	}
}

void Object::draw()
{

	//using default animation
	if (ID != "player")
	{
		renderObject(clippingArea.at(0));
	}
	else //object to be drawn is player located in .at(1)
	{
		updateState();
		animationState = getState();
		renderObject(clippingArea.at(animationState));
	}
}

void Object::renderObject(SDL_Rect renderLocation)
{
	SDL_Rect rect; //used for any scaling changes or position changes
	rect.x = position.x;
	rect.y = position.y;
	rect.w = scale.x;
	rect.h = scale.y;

	if ((renderLocation.w == 0) && (renderLocation.h == 0)) //no sprite sheet
	{
		if (facingRight && texture.at(0)) //render based off of direction object is facing
		{
			SDL_RenderCopy(globals::renderer, texture.at(0), NULL, &rect);
		}
		else if (texture.at(0))
		{
			SDL_RenderCopyEx(globals::renderer, texture.at(0), NULL, &rect, 0.0, NULL, SDL_FLIP_HORIZONTAL);
		}
	}
	else //sprite sheet
	{
		if (facingRight && texture.at(0)) //render based off of direction object is facing
		{
			SDL_RenderCopy(globals::renderer, texture.at(0), &renderLocation, &rect);
		}
		else if (texture.at(0))
		{
			SDL_RenderCopyEx(globals::renderer, texture.at(0), &renderLocation, &rect, 0.0, NULL, SDL_FLIP_HORIZONTAL);
		}
	}
}

void Object::run()
{
	updateTime();
	updateVelocity();
	updateDirection();
}

void Object::updateVelocity() //used to graduate increase velocity, to prevent sudden velocity changes
{
	double xtimeMul = 0.008;
	double ytimeMul = 0.01;
	Vector2 differenceVelocity = goalVelocity - actualVelocity; //differnce between target velocity and current


	bool xLerp = false;
	bool yLerp = false;

	//x value change
	if (differenceVelocity.x > (xtimeMul*deltaTime))
	{
		actualVelocity.x = actualVelocity.x + (xtimeMul *deltaTime);
		xLerp = true;
	}
	if (differenceVelocity.x < -(xtimeMul*deltaTime))
	{
		actualVelocity.x = actualVelocity.x - (xtimeMul* deltaTime);
		xLerp = true;
	}

	//y value change
	if (differenceVelocity.y > (ytimeMul*deltaTime))
	{
		actualVelocity.y = actualVelocity.y + (ytimeMul *deltaTime);
		yLerp = true;
	}
	if (differenceVelocity.y < -(ytimeMul*deltaTime))
	{
		actualVelocity.y = actualVelocity.y - (ytimeMul* deltaTime);
		yLerp = true;
		return;
	}

	// requires no LERP if actual already close to goal
	if (!xLerp)
	{
		actualVelocity.x = goalVelocity.x;
	}
	if (!yLerp)
	{
		actualVelocity.y = goalVelocity.y;
	}
}

void Object::setPosition(const Vector2& v)
{
	position = v;
}

void Object::setGrounded(const bool &ground)
{
	isGrounded = ground;
}

void Object::setJump()
{
	jumpStart = SDL_GetTicks();
}

void Object::setRotation(const float r)
{
	rotation = r;
}

void Object::setScale(const Vector2& v)
{
	scale = v;
}

void Object::setVelocity(const Vector2& v)
{
	goalVelocity = v;
}

void Object::setActualVelocity(const Vector2& v)
{
	actualVelocity = v;
}

void Object::setJumpAnimation(const bool &jump)
{
	jumpAnimation = jump;
}

const Vector2& Object::getPosition() const
{
	return position;
}

const float Object::getRotation() const
{
	return rotation;
}

const Vector2& Object::getScale() const
{
	return scale;
}

const Vector2& Object::getVelocity() const
{
	return goalVelocity;
}

const Vector2& Object::getActualVelocity() const
{
	return actualVelocity;
}

bool Object::getGrounded() const
{
	return isGrounded;
}

int Object::getJump() const
{
	return jumpStart;
}

void Object::addSprite(SDL_Rect spriteLoc) 
{
	clippingArea.push_back(spriteLoc);
}

void Object::updateState()
{}

int Object::getState()
{
	return 0;
}

void Object::moveObjectX(double distance)
{
	position.x += distance;
}

void Object::moveObjectY(double distance)
{
	position.y += distance;
}

void Object::updateTime()
{
	double currentTime = SDL_GetTicks();
	deltaTime = currentTime - lastFrame;
	lastFrame = currentTime;
}

void Object::updateDirection()
{
	if (goalVelocity.x > 0)
	{
		facingRight = true;
	}
	if (goalVelocity.x < 0)
	{
		facingRight = false;
	}
}
