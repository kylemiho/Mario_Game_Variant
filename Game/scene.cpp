#include "stdafx.h"
#include "scene.h"
#include "globals.h"
#include "player.h"

Scene::Scene(const std::string backgroundFilePath, Vector2 backgroundSize,int sceneNumber)
:
sceneNumber(sceneNumber)
{
	//testing ground
	background = new Object(
		backgroundFilePath,
		Vector2(0, 0),
		0.0f,
		backgroundSize,
		NULL
		, "background"
		);
	addObject(background);
	mario = new Sprite(80, 32, 15, 16);
	maxMarioDistance = 580; //distance Mario has to pass on the x-axis before the camera will adjust

	//mario jump animation
	SDL_Rect marioJump;
	marioJump.x = 161;
	marioJump.y = 32;
	marioJump.w = 15;
	marioJump.h = 16;
	SDL_Rect marioWalk1;
	marioWalk1.x = 95;
	marioWalk1.y = 32;
	marioWalk1.w = 15;
	marioWalk1.h = 16;
	SDL_Rect marioWalk2;
	marioWalk2.x = 112;
	marioWalk2.y = 32;
	marioWalk2.w = 15;
	marioWalk2.h = 16;
	SDL_Rect marioWalk3;
	marioWalk3.x = 128;
	marioWalk3.y = 32;
	marioWalk3.w = 15;
	marioWalk3.h = 16;
	player = new Player(
		"Resources/art/mario_sprite.png",
		Vector2(0, 400),
		0.0f,
		Vector2(50, 50),
		mario,
		"player"
		);
	player->addSprite(marioJump);
	player->addSprite(marioWalk1);
	player->addSprite(marioWalk2);
	player->addSprite(marioWalk3);
	player->setVelocity(Vector2(0, 1)); //apply gravity
	addObject(player);

	playerWalkSpeed = 0.6;	//default walk speed
}

Scene::~Scene()
{
	delete background;
	background = NULL;
	delete player;
	player = NULL;

}

int Scene::getSceneNumber()
{
	return sceneNumber;
}

void Scene::setPlayerSpeed(double speed)
{
	playerWalkSpeed = speed;
}

void Scene::addObject(Object* object)
{
	objectList.push_back(object);
}

std::vector <Object*> Scene::returnObjectList()
{
	return objectList;
}

void Scene::adjustCamera()
{
	//check condition to see if we wont exceed max background distance , 1295 is our window creation size
	if (background->getPosition().x + background->getScale().x > 1295)
	{
		if ((player->getPosition().x > maxMarioDistance) && player->getVelocity().x > 0)//if mario passes a certain distance, we need to adjust camera && if hes going left
		{
			for (unsigned i = 0; i < objectList.size(); ++i)
			{
				Vector2 tempVector = objectList.at(i)->getPosition(); //get current position of object
				tempVector.x -= player->getVelocity().x;                    //then subtract it by mario's velocity to get a camera effect
				objectList.at(i)->setPosition(tempVector);          //and then update the adjusted object's position
			}
		}
	}
}

void Scene::movement(Object *currentObject)
{
	//freeze player's x position if he goes offscreen, otherwise perform normal movement
	if (currentObject != objectList[1]) //perform normally if player, otherwise check to see we dont move offscreen via x value
	{
		currentObject->moveObjectX(currentObject->getActualVelocity().x);
	}
	else
	{
		if ((currentObject->getPosition().x > 0) && (currentObject->getPosition().x < 1250)) //prevent offscreen
		{
			currentObject->moveObjectX(currentObject->getActualVelocity().x);
		}
		else
		{
			if (currentObject->getPosition().x <= 0)
			{
				currentObject->moveObjectX(abs(currentObject->getActualVelocity().x));
			}
			else
			{
				currentObject->moveObjectX(-abs(currentObject->getActualVelocity().x));
			}
		}
	}
	currentObject->moveObjectY(currentObject->getActualVelocity().y);
}

void Scene::collision(Object *currentObject)
{
	for (unsigned i = 0; i < objectList.size(); ++i)
	{
		if ((currentObject != objectList[i]) && (i != 0)) //to prevent self-collision and background collision
		{
			if (objectList[i]->getPosition().x < currentObject->getPosition().x + currentObject->getScale().x &&
				objectList[i]->getPosition().x + objectList[i]->getScale().x > currentObject->getPosition().x &&
				objectList[i]->getPosition().y < currentObject->getPosition().y + currentObject->getScale().y &&
				objectList[i]->getPosition().y + objectList[i]->getScale().y > currentObject->getPosition().y)
			{
				//check whether to push back x coordinates or y coordinates to prevent units getting stuck on walls/ground
				if ((objectList[i]->getPosition().x + currentObject->getActualVelocity().x < currentObject->getPosition().x 
					+ currentObject->getScale().x && objectList[i]->getPosition().x + objectList[i]->getScale().x 
					+ currentObject->getActualVelocity().x >  currentObject->getPosition().x)) //vertical collision
				{
					if (currentObject->getGrounded() && currentObject->getActualVelocity().y > 0) //if colliding with ground downwards
					{
						Vector2 tempVector2 = currentObject->getPosition();
						tempVector2.y -= currentObject->getActualVelocity().y;
						currentObject->setPosition(tempVector2);
						//cancel movement done this frame

						currentObject->setGrounded(true);
						currentObject->setJumpAnimation(false);
					}

					if (!(currentObject->getGrounded()) && currentObject->getActualVelocity().y > 0) //landing on ground
					{
						Vector2 tempVector2 = currentObject->getPosition();
						tempVector2.y -= currentObject->getActualVelocity().y;
						currentObject->setPosition(tempVector2);
						//cancel movement done this frame

						currentObject->setGrounded(true);
						currentObject->setJumpAnimation(false);
					}
					if (!(currentObject->getGrounded()) && currentObject->getActualVelocity().y < 0) //updwards collision
					{
						Vector2 tempVector2 = currentObject->getPosition();
						tempVector2.y -= currentObject->getActualVelocity().y;
						currentObject->setPosition(tempVector2);
						//cancel movement done this frame

						Vector2 tempVelocity6 = currentObject->getVelocity();
						tempVelocity6.y = 1;
						currentObject->setVelocity(tempVelocity6);
						currentObject->setGrounded(false);
					}

				}
				if (objectList[i]->getPosition().y + 1.1 < currentObject->getPosition().y + currentObject->getScale().y &&
					objectList[i]->getPosition().y + objectList[i]->getScale().y > 1.1 +currentObject->getPosition().y) //horizontal collision
				{
					if (currentObject->getGrounded()) //collides with an object horizontally on ground
					{
						Vector2 tempVector2 = currentObject->getPosition();
						tempVector2.x -= currentObject->getActualVelocity().x;
						currentObject->setPosition(tempVector2);
					}
					else //collides with an object horizontal in air
					{
						Vector2 tempVector2 = currentObject->getPosition();
						tempVector2.x -= currentObject->getActualVelocity().x;
						currentObject->setPosition(tempVector2);
						//cancelmovement this frame

						Vector2 tempVector3 = currentObject->getPosition();
						tempVector3.y += currentObject->getActualVelocity().y;
						currentObject->setPosition(tempVector3); //renable falling
					}
				}

			}
		}
	}
}

bool Scene::marioGrounded()
{
	if (objectList.at(1)) //if mario exists
	{
		return (objectList.at(1))->getGrounded();
	}
	else
	{
		return false;
	}
}

void Scene::run()
{

	if (globals::handler->isKeyDown(SDLK_a) && !globals::handler->isKeyDown(SDLK_d))
	{
		//game stuff goes here
		Vector2 newVelocity = player->getVelocity();
		newVelocity.x = -playerWalkSpeed;
		player->setVelocity(newVelocity);

		//set animation state to next if not grounded
	}

	if (globals::handler->isKeyDown(SDLK_d) && !globals::handler->isKeyDown(SDLK_a)) 
	{
		//game stuff goes here
		Vector2 newVelocity = player->getVelocity();
		newVelocity.x = playerWalkSpeed;
		player->setVelocity(newVelocity);

		//set animation state to next if not grounded
	}
	if (!globals::handler->isKeyDown(SDLK_a) && !globals::handler->isKeyDown(SDLK_d))
	{
		Vector2 newVelocity = player->getVelocity();
		newVelocity.x = 0;
		player->setVelocity(newVelocity);

		//reset animation state

	}
	if ((globals::handler->isKeyDown(SDLK_SPACE)) && player->getGrounded()) //jump if player on floor
	{
		//reset animation state

		player->setGrounded(false);
		player->setJump(); //start air timer
		player->jumpAnimation = true;
		Vector2 newVelocity = player->getVelocity();
		newVelocity.y = -1; //fly in air
		player->setVelocity(newVelocity);
		globals::musicPlayer->jumpSound();//fixthis
	}
	//350 is max jump height, 200 is min  jump height
	if (((SDL_GetTicks() - player->getJump()) > 450) || 
		((SDL_GetTicks() - player->getJump()) > 200) && !globals::handler->isKeyDown(SDLK_SPACE))
		//if player has been in air for 0.3 sec , min jump time of 0.2
	{
		Vector2 tempVelocity = player->getVelocity(); //get velocity, so we can change players velocity to hit -1 (gravity portion)
		tempVelocity.y = 1;
		player->setVelocity(tempVelocity);
	}

	for (unsigned i = 0; i < objectList.size(); i++)
	{
		(objectList.at(i))->run();
	}
	for (unsigned i = 0; i < objectList.size(); i++)
	{
		movement((objectList.at(i)));
	}
	for (unsigned i = 0; i < objectList.size(); i++)
	{
		collision((objectList.at(i)));
	}
	for (unsigned i = 0; i < objectList.size(); i++)
	{
		(objectList.at(i))->draw();
	}

	adjustCamera();
}