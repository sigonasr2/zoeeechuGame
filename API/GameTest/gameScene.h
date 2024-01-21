#pragma once

#include "stdafx.h"
//--------------------
#include <windows.h> 
#include <math.h>  
#include <vector>
#include <algorithm>
#include <random>
//--------------------
#include "app\app.h"

#include "Scene.h"

class GAME_SCENE : public Scene {
public:
	void init() override;
	void update(float deltaTime) override;
	void render(int WINDOW_W, int WINDOW_H) override;
	void exit() override;
protected:
	std::vector<Body> GameObjects;
};








