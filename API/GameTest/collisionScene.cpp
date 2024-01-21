
//------------------------------------------------------------------------
// CollisionTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <map>
#include <algorithm>
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------

CSimpleSprite* collision_background;


SimpleCamera2D CollisionScene_camera;

Body BackgroundBody; 



void COLLISION_SCENE::init()
{
	collision_background = App::CreateSprite(".\\TestData\\space.jpg", 1, 1);
	//collision_background->SetPosition(400.0f, 400.0f);
	//collision_background->SetScale(1.4f);

	BackgroundBody = Body(Vec2(400.0f, 400.0f), Vec2(), Vec2(), 0.0f, 0.0f, *collision_background, 1.4f, true, CollisionScene_camera);

	setLevel(64, 16);

	Level += L"••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••";
	Level += L"••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••";
	Level += L"••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••";
	Level += L"••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••";
	Level += L"•••••••••••••••••••••••############•••••••••••••••••••••••••••••";
	Level += L"•••••••••••••••••••••###•••••••••••••••••••##•••••••••••••••••••";
	Level += L"•••••••••••••••••••###•••••••••••••••••••••##•••••••••••••••••••";
	Level += L"••••••••••••••••••###•••••••••••••••••••••••••••••••••••••••••••";
	Level += L"########################################•################••••####";
	Level += L"•••••••••••••••••••••••••••••••••••••••#•#•••••••••••••••••###••";
	Level += L"•••••••••••••••••••••••••###############•#••••••••••••••###•••••";
	Level += L"•••••••••••••••••••••••••#•••••••••••••••#•••••••••••###••••••••";
	Level += L"•••••••••••••••••••••••••#•###############••••••••###•••••••••••";
	Level += L"•••••••••••••••••••••••••#•••••••••••••••••••••###••••••••••••••";
	Level += L"•••••••••••••••••••••••••######################•••••••••••••••••";
	Level += L"••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••";

	
}

void COLLISION_SCENE::update(float deltaTime)
{
	int TileWidth = 16;
	int TileHeight = 16;

	int VisableTilesX = APP_VIRTUAL_WIDTH / TileWidth;
	int VisableTilesY = APP_VIRTUAL_HEIGHT / TileHeight;

	
	//float fOffsetX = camera

}

void COLLISION_SCENE::render(int WINDOW_W, int WINDOW_H)
{

	collision_background->Draw();

	//gluLookAt()



}

void COLLISION_SCENE::exit()
{
	delete collision_background;
}
