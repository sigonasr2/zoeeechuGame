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


class MENU_SCENE : public Scene {
public:
	void init() override;
	void update(float deltaTime) override;
	void render(int WINDOW_W, int WINDOW_H) override;
	void exit() override;

	float lerp(float a, float b, float t) {
		return a + t * (b - a);
	}
};









