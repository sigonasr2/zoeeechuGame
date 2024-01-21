// zoe - 2024
//------------------------------------------------------------------------
// GameLoop.cpp                        
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------

#include "menuScene.h"

void Init()
{
	changeScene(new MENU_SCENE()); // change this to which ever scene you want first TODO:								
	glutMainLoop();               //just load scene 0 which points to whatever scene is set to 0
	currentScene->init();
}

void Update(float deltaTime) { currentScene->update(deltaTime); }

void Render(int WINDOW_W, int WINDOW_H) { currentScene->render(WINDOW_W, WINDOW_H); }

void Shutdown() { currentScene->exit(); }