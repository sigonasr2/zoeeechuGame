#include "stdafx.h"
//#include "button.h"

#pragma region visual	
/*
   y
	 returns false ----------+
   ^
   |        x1,y1---> +------------------.
   |                  |                  |
   |                  |          +-------|------------- returns true
   |    y < y1        |                  |
   |              ^   .------------------+ <---x2,y2
   |              |
   | x < x2  - - -|_ _ _ >   x > x1
   |              '
   |              '
   |    y > y2
   +------------------------------------> x
*/
#pragma endregion
bool inGivenBounds(Vec2 pt1, Vec2 pt2, Vec2 cords)
{
	if (cords.x > pt1.x && cords.x < pt2.x && cords.y < pt1.y && cords.y > pt2.y) {
		return true;
	}
	return false;
}

void UpdateMouseState()
{
	//
}


bool IsButtonDown(int button)
{
	return (GetAsyncKeyState(button) & 0x8001) != 0;
}





