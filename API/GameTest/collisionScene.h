#pragma once

#include "stdafx.h"
//--------------------
#include <windows.h> 
#include <iostream>
#include <string>
//--------------------
#include "app\app.h"

#include "Scene.h"

class COLLISION_SCENE : public Scene {
public:
	void init() override;
	void update(float deltaTime) override;
	void render(int WINDOW_W, int WINDOW_H) override;
	void exit() override;

	void setLevel(int w_, int h_) {
		LevelWidth = w_;
		LevelHeight = h_;
	}
	
private: 
	std::wstring Level;
	int LevelWidth;
	int LevelHeight;
};








