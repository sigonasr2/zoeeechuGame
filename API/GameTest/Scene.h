#include "stdafx.h"
#pragma once

class Scene {
public:
    virtual void init() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(int WINDOW_W, int WINDOW_H) = 0;
    virtual void exit() = 0;

    virtual ~Scene() {}

};