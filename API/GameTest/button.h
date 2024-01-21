#include "stdafx.h"
#include "app\app.h"
#include "body.h"
#include <conio.h>

#pragma once

#pragma region summary
// simple boolean function that returns true if given x,y values intersect
// with given rect dimensions  x1,y1, x2,y2
#pragma endregion
bool inGivenBounds(Vec2 pt1, Vec2 pt2, Vec2 givenCords);

bool IsButtonDown(int button);
bool anyKeyPressed();

void UpdateMouseState();

void ButtonCoords(CSimpleSprite m_sprite_, Vec2 pos_, Vec2 pos1_, Vec2 pos2_);