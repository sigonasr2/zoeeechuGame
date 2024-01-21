//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <vector>
#include <algorithm>
#include <random>
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------

CSimpleSprite* background;
CSimpleSprite* button;
CSimpleSprite* planet;
CSimpleSprite* star;
CSimpleSprite* star2;


SimpleCamera2D PlanetScene_camera;


std::vector<Body> planets;
std::vector<Vec2> initPos;
std::vector<Vec2> initVel;

//-------------------------
Vec2 Star1Force, Star2Force;
Vec2 Star1Disp, Star2Disp;
Vec2 totalForce;

Body planetBody;
Body starBody1;
Body starBody2;

const float G = 1.0f;
//-------------------------

bool isTextVisible = false;
bool mouseOverButton = false;
float MB;

Vec2 Mouse;
Vec2 buttonPOS;
Vec2 buttonC1, buttonC2;
float mX, mY;
float Mag1;
float Mag2;
float factor;

float buttonWidth;
float buttonHeight;

bool mouseDown = false;

float buttonX1;
float buttonY1;
float buttonX2;
float buttonY2;

int numPlanets = 10000;
int activePlanetsCount;


void PLANET_SCENE::init()
{
	float pSpeed = 5.0f;
	initPos.resize(numPlanets);
	initVel.resize(numPlanets);

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> pdist(-10.0f, 10.0f);
	std::uniform_real_distribution<float> vdist(-10.0f, 10.0f);

	planet = App::CreateSprite(".\\TestData\\planet.png", 1, 1);
	for (int i = 0; i < numPlanets; i++) {
		Vec2 initp = Vec2(410.0f + pdist(mt), 545.0f + pdist(mt));
		Vec2 inita = Vec2(-91 + vdist(mt), 1 + vdist(mt));

		initPos[i] = initp; initVel[i] = inita;
		planets.push_back(Body(Vec2(initp.x, initp.y), Vec2(inita.x, inita.y), Vec2(), 2.0f, 9.8f, *planet, 0.05f, true, PlanetScene_camera));
	

	}

	background = App::CreateSprite(".\\TestData\\space.jpg", 1, 1);
	background->SetPosition(400.0f, 400.0f);
	background->SetScale(1.4f);



	button = App::CreateSprite(".\\TestData\\button.png", 1, 1);
	button->SetPosition(400.0f, 400.0f);
	button->SetScale(0.5f);

	ButtonCoords(*button, buttonPOS, buttonC1, buttonC2);

	buttonWidth = button->GetWidth();
	buttonHeight = button->GetHeight();

	button->GetPosition(buttonPOS.x, buttonPOS.y);

	buttonC1.x = buttonPOS.x - (buttonWidth / 2);
	buttonC1.y = buttonPOS.y + (buttonHeight / 2);
	buttonC2.x = buttonPOS.x + (buttonWidth / 2);
	buttonC2.y = buttonPOS.y - (buttonHeight / 2);

	star = App::CreateSprite(".\\TestData\\star.png", 1, 1);
	starBody1 = Body(Vec2(400.0f, 200.0f), Vec2(), Vec2(), 1000000.0f, 0.0, *star, 0.08f, true, PlanetScene_camera);

	star2 = App::CreateSprite(".\\TestData\\star.png", 1, 1);
	starBody2 = Body(Vec2(800.0f, 800.0f), Vec2(), Vec2(), 1000000.0f, 0.0, *star2, 0.08f, true, PlanetScene_camera);

}

void ButtonCoords(CSimpleSprite s, Vec2 v, Vec2 a, Vec2 b) {
	Vec2 scale;
	scale.x = s.GetWidth();
	scale.y = s.GetHeight();
	s.GetPosition(v.x, v.y);

	a.x = v.x - (scale.x / 2);
	a.y = v.y + (scale.y / 2);
	b.x = v.x + (scale.x / 2);
	b.x = v.y - (scale.x / 2);


	buttonC1 = a;
	buttonC2 = b;
}

void PLANET_SCENE::update(float deltaTime)
{
	App::GetMousePos(mX, mY);
	App::GetMousePos(Mouse.x, Mouse.y);
	mouseOverButton = inGivenBounds(buttonC1, buttonC2, Mouse);

	for (Body& p : planets) {
		if (p.isActive) {
			totalForce = p.CalculateGravForceBy(G, starBody1) + p.CalculateGravForceBy(G, starBody2);  //fg = G m1 * m2 / r^2
			p.ApplyForce(totalForce);
			p.Update(deltaTime);

		}
	}

	float borderThresh = 2000;
	starBody1.m_sprite.SetAngle(starBody1.m_sprite.GetAngle() + 0.01f);
	starBody2.m_sprite.SetAngle(starBody2.m_sprite.GetAngle() + 0.01f);

	for (Body& planet : planets) {
		bool removeCondition = planet.pos.x < (0 - borderThresh) || planet.pos.x >(APP_VIRTUAL_WIDTH + borderThresh) ||
			planet.pos.y < (0 - borderThresh) || planet.pos.y >(APP_VIRTUAL_HEIGHT + borderThresh) ||
			abs((planet.pos - starBody1.pos).getMag()) < 20 || abs((planet.pos - starBody2.pos).getMag()) < 20;

		if (removeCondition) {
			planet.isActive = false;
		}
	}

	activePlanetsCount = std::count_if(planets.begin(), planets.end(), [&](Body& planet) {
		return planet.isActive;
		});



	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	{
		isTextVisible = !isTextVisible;
	}

	//planets.erase(std::remove_if(planets.begin(), planets.end(),
	//	[&](Body& planet) {
	//		return planet.pos.x < 0 || planet.pos.x > APP_VIRTUAL_WIDTH || planet.pos.y < 0 || planet.pos.y > APP_VIRTUAL_HEIGHT ||
	//			abs((planet.pos - starBody1.pos).getMag()) < 20 || abs((planet.pos - starBody2.pos).getMag()) < 20;
	//	}), planets.end());

	//planetBody.pos.y++;
}

// renders in layers!!!!!!!!!!!!!

void PLANET_SCENE::render(int WINDOW_W, int WINDOW_H)
{

	background->Draw();
	button->Draw();


	mouseDown = (IsButtonDown(VK_LBUTTON));
	//

	if (mouseOverButton && mouseDown) MB = 1.0f;
	else MB = 0.0f;

	if (mouseOverButton && mouseDown) {
		changeScene(new GAME_SCENE());
	}


	for (auto p : planets) {
		if (p.isActive) {
			p.m_sprite.Draw();
		}
	}



	starBody1.m_sprite.Draw();
	starBody2.m_sprite.Draw();


	char bffr[64];
	sprintf(bffr, "mX: %f mY: %f", mX, mY);

	char bffr2[64];
	sprintf(bffr2, "Planets Left: %i", static_cast<int>(activePlanetsCount));

	char btnbffr[64];
	sprintf(btnbffr, "mouseover button: %f", MB);
	App::Print(10, 10, btnbffr);
	//App::Print(10, 10, btnbffr, 1.0f, 1.0f, 1.0f, ".\\TestData\\your-gone.bmp");




	char namebffr[64];
	char posbffr[64];
	char accbffr[64];

	App::Print(100, 100, bffr);
	App::Print(100, 160, bffr2);

	if (!isTextVisible) {
		return;
	}
	for (int i = 0; i < planets.size(); ++i) {

		if (i < initPos.size() && i < initVel.size()) {

			Body& p = planets[i];
			if (p.isActive) {
				sprintf(namebffr, "plnt: %i", i);
				sprintf(posbffr, "pos: %.f, %.f", initPos[i].x, initPos[i].y);
				sprintf(accbffr, "vel: %.f, %.f", initVel[i].x, initVel[i].y);

				App::Print(p.pos.x - 14, p.pos.y + 46, namebffr);
				App::Print(p.pos.x - 14, p.pos.y + 30, posbffr);
				App::Print(p.pos.x - 14, p.pos.y + 14, accbffr);
			}
		}
	}
}

void PLANET_SCENE::exit()
{

	delete background;
	delete star;
	delete star2;
	delete planet;

	delete& Star1Force;
	delete& Star2Force;
	delete& Star1Disp;
	delete& Star2Disp;
	delete& totalForce;
	delete& planetBody;
	delete& starBody1;
	delete& starBody2;

	planets.clear();
	initPos.clear();
	initVel.clear();

}
