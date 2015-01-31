#pragma once

#include <vector>

class Scene;
class Object;
class Sprite;

class sceneManager
{
public:
	sceneManager();
	~sceneManager();
	void addScene(Scene* scene); //add Scene to Scene list
	void runScene(); //run current Scene
	void initializeScenes(); //load objects into each scene
	Scene* getScene();  //returns current scene

protected:
	std::vector <Scene*> sceneList; //list of each of the scenes that we are using
	std::vector <Object*> deallocateList; //list of objects need to deallocate later
	std::vector <Sprite*> deallocateList2; //list of sprites need to deallocate later
	int currentScene; //index to inform the scene manager which scene will currently be running

	//1-1 level functions
	void initialize_1_1();
	void initialize_1_1_cointile(int scene); //only call this in initialize_1_1
	void initialize_1_1_basictile(int scene);
};
