#pragma once

#include "globals.h"
#include "vector2.h"

class Object; //foward declaration needed to prevent header errors
class Sprite;
class Player;

class Scene
{
public:
	Scene(const std::string backgroundFilePath, Vector2 backgroundSize,int sceneNumber);
	~Scene();

	void run();
	void setPlayerSpeed(double speed);
	void adjustCamera();
	void addObject(Object* object);
	void removeObject(Object* object);
	std::vector <Object*> returnObjectList();
	virtual void movement(Object *currentObject);
	virtual void collision(Object *currentObject);
	bool marioGrounded();
	int getSceneNumber();
	void marioCollision(unsigned &index);

protected:
	Player *player;
	Object *background;
	Sprite *mario;
	Sprite *basicTile;
	Object *test;
	std::vector <Object*> objectList;
	int sceneNumber;
	double playerWalkSpeed;
	int maxMarioDistance;
};
