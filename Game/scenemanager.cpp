#include "stdafx.h"
#include "scenemanager.h"
#include "object.h"
#include "sprite.h"
#include "scene.h"

sceneManager::sceneManager()
{
	currentScene = 0;
}

sceneManager:: ~sceneManager() //need to empty sceneList
{
	for (unsigned i = 0; i < sceneList.size(); ++i)
	{
		delete sceneList.at(i);
	}
	for (unsigned i = 0; i < deallocateList.size(); ++i)
	{
		delete deallocateList.at(i);
	}
	for (unsigned i = 0; i < deallocateList2.size(); ++i)
	{
		delete deallocateList2.at(i);
	}
}

void sceneManager::initializeScenes()
{
	if (currentScene == 0)
	{
		initialize_1_1();
	}
}

void sceneManager::initialize_1_1_cointile(int scene)
{
	Sprite *coinTile = new Sprite(384, 0, 16, 16);
	deallocateList2.push_back(coinTile);
	Object *tempTile = new Object(
		"Resources/art/tile.png",
		Vector2(893, 474),
		0.0f,
		Vector2(55.8, 55.8),
		coinTile,
		"coinTile"
		);
	sceneList.at(scene)->addObject(tempTile); //add object to scene 1
}

void sceneManager::initialize_1_1_basictile(int scene)
{
	Sprite *basicTile = new Sprite(0, 0, 16, 16);
	for (int i = 0; i <153; ++i) //create 153 tiles
	{
		Object *tempTile = new Object(
			"Resources/art/tile.png",
			Vector2(i*55.8, 697),
			0.0f,
			Vector2(55.8, 55.8),
			basicTile,
			"tile"
			);
		sceneList.at(scene)->addObject(tempTile);
	}

	for (int i = 155; i <212; ++i) //create more tiles
	{
		Object *tempTile = new Object(
			"Resources/art/tile.png",
			Vector2(i*55.8, 697),
			0.0f,
			Vector2(55.8, 55.8),
			basicTile,
			"tile"
			);
		sceneList.at(scene)->addObject(tempTile);
	}
	deallocateList2.push_back(basicTile);
}

void sceneManager::initialize_1_1()
{
	int scene = sceneList.size(); //this will be at int scene of vector when pushed back
	Scene *scene_1_1 = new Scene("Resources/art/1-1.png", Vector2(11822, 1604),scene); //initializing scene / background / player
	addScene(scene_1_1); //add scene 1-1 to scenelist

	initialize_1_1_cointile(scene);
	initialize_1_1_basictile(scene);
}

void sceneManager::addScene(Scene *scene)
{
	sceneList.push_back(scene);
}

Scene* sceneManager::getScene()
{
	return sceneList.at(currentScene);
}

void sceneManager::runScene()
{
	sceneList.at(currentScene)->run();
}