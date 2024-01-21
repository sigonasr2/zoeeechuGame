#include "stdafx.h"

Scene* currentScene = nullptr;

void changeScene(Scene* newScene) {
	if (currentScene != nullptr) {
		//currentScene->exit(); /// crashes program
		delete currentScene;
	}

	currentScene = newScene;
	currentScene->init();

}
