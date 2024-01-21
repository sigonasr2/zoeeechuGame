//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <cmath>
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------

CSimpleSprite* menu_background;
CSimpleSprite* title;
CSimpleSprite* press_start;

float pressStartAlpha = 0.0f;
float fadeSpeed = 0.5f;
float fadeInOutDuration = 300.0f;

static float lerp(float a, float b, float t);

Vec2 MousePos_menu;
Vec2 WindowTopLeft;
Vec2 WindowBottomRight;




float mX2, mY2;
//bool isanybuttondown;
bool mouseDown2;


void MENU_SCENE::init()
{
	menu_background = App::CreateSprite(".\\TestData\\space.jpg", 1, 1);
	menu_background->SetPosition(400.0f, 400.0f);
	menu_background->SetScale(1.4f);

	title = App::CreateSprite(".\\TestData\\sample_title.png", 1, 1);
	title->SetPosition(500.0f, 800.0f);
	title->SetScale(1.0f);

	press_start = App::CreateSprite(".\\TestData\\press_start.png", 1, 1);
	press_start->SetPosition(500.0f, 100.0f);
	press_start->SetScale(1.0f);

	WindowBottomRight = Vec2(APP_VIRTUAL_WIDTH, 0);
	WindowTopLeft = Vec2(0, APP_VIRTUAL_HEIGHT);
	//press_start->SetAlpha(0.0f);
}



void MENU_SCENE::update(float deltaTime)
{
	
	App::GetMousePos(mX2, mY2);
	App::GetMousePos(MousePos_menu.x, MousePos_menu.y);

	pressStartAlpha += (fadeSpeed / fadeInOutDuration) * deltaTime;
	pressStartAlpha = fmaxf(0.0f, fminf(pressStartAlpha, 1.0f)); // range between 0.0f-1.0f
	press_start->SetAlpha(lerp(0.0f, 1.0f, pressStartAlpha));

	if (pressStartAlpha >= 1.0f || pressStartAlpha <= 0.0f) {
		fadeSpeed = -fadeSpeed;
	}

	mouseDown2 = (IsButtonDown(VK_LBUTTON));

	if (inGivenBounds(WindowTopLeft, WindowBottomRight, MousePos_menu)) {
		if (mouseDown2) {
			//changeScene(new GAME_SCENE());
			changeScene(new GAME_SCENE());
		}
	}


}


float lerp(float a, float b, float t) // add this to a seprate class later <3
{
	return a + t * (b - a);
}


// renders in layers!!!!!!!!!!!!!

void MENU_SCENE::render(int WINDOW_W, int WINDOW_H)
{
	menu_background->Draw();
	title->Draw();
	press_start->Draw();

	char bffr[64];
	sprintf(bffr, "mX: %f mY: %f", mX2, mY2);
	App::Print(10, 60, bffr);

	//char Text[64];
	//sprintf(Text, "button is being pressed %f", a);
	//App::Print(500, 500, Text);


	



}

void MENU_SCENE::exit()
{
	delete menu_background;
	delete title;
	delete press_start; 
}
