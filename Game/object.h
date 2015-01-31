#pragma once

#include "globals.h" //includes our global file
#include "vector2.h" //includes vector class that we use
#include <SDL.h>
#include <vector>
#include <string>
#include "sprite.h"

class Scene;

class Object
{
public:
	Object::Object(
		const std::string filepath,
		const Vector2 &position,
		const float rotation,
		const Vector2 &scale,
		Sprite *sprite,
		const std::string ID);
	//this is a static vector
	//is a global vector of objects so we have a list of all objects created
	//constructor
	~Object();
	virtual void draw();
	virtual void run();

	//used to change object values
	void setPosition(const Vector2& v);
	void setRotation(float r);
	void setScale(const Vector2& v);
	void setVelocity(const Vector2& v); 
	void setActualVelocity(const Vector2& v);
	void setGrounded(const bool &ground);
	void setJump();
	void setJumpAnimation(const bool &jump);
	void moveObjectX(double distance);
	void moveObjectY(double distance);
	//get object values
	const Vector2& getPosition() const;
	const float getRotation() const;
	const Vector2& getScale() const;
	const Vector2& getVelocity() const;
	const Vector2& getActualVelocity() const;
	bool getGrounded() const;
	int getJump() const;
	void addSprite(SDL_Rect spriteLoc);
	bool jumpAnimation;
	virtual void updateState();
	virtual int getState();

protected:

	int components;	//stores the component bits
	int animationState;
	int index;
	Scene *scene;
	SDL_Window *window;
	std::string filepath;
	std::vector <SDL_Texture*> texture;  //TODO: make vector, for multiple textures
	std::vector <SDL_Rect> clippingArea; //TODO: make vector, for multiple textures
	SDL_Surface *objectSurface;
	Vector2 position;
	float rotation;
	Vector2 scale;
	Vector2 goalVelocity; //goal velocity of object used for LERP
	Vector2 actualVelocity; //current velocity
	bool isGrounded; //bool value used to get whether object is in air on 
	double lastFrame; //time at lastFrameon ground
	int jumpStart; //timer used to get how long object has been in air
	double deltaTime; //time since LastFrame in milliseconds
	bool facingRight;
	std::string ID;
	void renderObject(SDL_Rect renderLocation);
	void updateTime(); //updates deltaTime and then lastFrame
	void updateVelocity(); //update actual velocity relative to current velocity with the help of LERP
	void updateDirection();
};
