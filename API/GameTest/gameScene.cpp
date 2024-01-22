//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include <map>
#include <algorithm>
#include <stdlib.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include <array>

CSimpleSprite* game_background;
CSimpleSprite* playerSprite;
CSimpleSprite* ballSprite;
CSimpleSprite* groundSprite;
CSimpleSprite* holeSprite;

CSimpleSprite* nullSprite;

Body player;
Body ground;
Body hole;
Body ball;


bool isPaused;
bool mouseDown_game;
bool ballIntersect;
bool drag;
bool hasBeenDragged = false;

bool hasWon = false;

SimpleCamera2D GameScene_camera;


char text[64];


Vec2 PlayerDimensions;
Vec2 playerpt1; 
Vec2 playerpt2;

std::vector<int> collided;

simpleCollision c;
simpleShape shape;
float temp = 0;

Vec2 ScreenBounds = Vec2(APP_VIRTUAL_WIDTH, APP_VIRTUAL_HEIGHT);


Vec2 MousePos_Game;

Vec2 diffrence;

enum CollisionSide {
	None,
	Left,
	Right,
	Top,
	Bottom
};

struct Bounds {
	Vec3 max;
	Vec3 min;
};


Vec2 tempPos;

std::map<int, std::pair<int, int>> buttonActions = {
	{APP_PAD_EMUL_LEFT_THUMB_UP, {0, 1}},
	{APP_PAD_EMUL_LEFT_THUMB_DOWN, {0, -1}},
	{APP_PAD_EMUL_LEFT_THUMB_LEFT, {-1, 0}},
	{APP_PAD_EMUL_LEFT_THUMB_RIGHT, {1, 0}},
};


void GAME_SCENE::init()
{
	nullSprite = App::CreateSprite(".\\TestData\\blank_sprite", 1, 1);

	game_background = App::CreateSprite(".\\TestData\\space.jpg", 1, 1);
	game_background->SetPosition(400.0f, 400.0f);
	game_background->SetScale(1.4f);

	ballSprite = App::CreateSprite(".\\TestData\\golf_ball.png", 1, 1);
	ball = Body(Vec2(400.0f, 200.0f), Vec2(0.0f, 0.0f), Vec2(0.0, 0.0), 200.0f, 0.0f, *ballSprite, 0.05f, true, GameScene_camera);
	GameObjects.push_back(ball);

	//holes position is relative to screen
	holeSprite = App::CreateSprite(".\\TestData\\hole.png", 1, 1);
	hole = Body(Vec2(APP_VIRTUAL_WIDTH - 100.0f, APP_VIRTUAL_HEIGHT - 100.0f), Vec2(0.0f, 0.0f), Vec2(0.0, 0.0), 200.0f, 0.0f, *holeSprite, 0.05f, true, GameScene_camera);
	GameObjects.push_back(hole);


	groundSprite = App::CreateSprite(".\\TestData\\red-brick-wall.png", 1, 1);
	ground = Body(Vec2(500.0f, 800.0f), Vec2(0.0f, 0.0f), Vec2(0.0, 0.0), 200.0f, 0.0f, *groundSprite, 0.10f, true, GameScene_camera);
	GameObjects.push_back(ground);

	for(Body&b:GameObjects){
		c.setCollisionMask(b);
	}

	//
	//playerSprite = App::CreateSprite(".\\TestData\\blob.png", 1, 1);
	//player = Body(Vec2(400.0f, 200.0f), Vec2(10.0f, 10.0f), Vec2(0.0, 0.0), 200.0f, 9.8f, *playerSprite, 0.20f, true, GameScene_camera);
	//GameObjects.push_back(player);

	isPaused = false;

}



void checkScreenCollision(Body& object)
{
	// Get the bounding box of the object
	Body::Bounds bounds = object.getBounds();


	// Calculate dynamic top and bottom limits based on a proportion of the window height
	float topLimit = 0.05f * APP_VIRTUAL_HEIGHT;  // Adjust as needed (e.g., 10% of the window height)
	float bottomLimit = 0.95f * APP_VIRTUAL_HEIGHT;  // Adjust as needed (e.g., 90% of the window height)


	// Check for collisions with the left and right screen boundaries
	if (bounds.max.x < 0.0f)
	{
		// Adjust the position to prevent going beyond the left boundary
		object.pos.x -= bounds.max.x;
		// Reflect the velocity of the object horizontally
		object.vel.x = std::abs(object.vel.x);
	}
	else if (bounds.min.x > APP_VIRTUAL_WIDTH)
	{
		// Adjust the position to prevent going beyond the right boundary
		object.pos.x -= (bounds.min.x - APP_VIRTUAL_WIDTH);
		// Reflect the velocity of the object horizontally
		object.vel.x = -std::abs(object.vel.x);
	}

	// Check for collisions with the top and bottom screen boundaries
	if (bounds.min.y < topLimit)
	{
		// Adjust the position to prevent going beyond the top boundary
		object.pos.y -= (bounds.min.y - topLimit);
		// Reflect the velocity of the object vertically
		object.vel.y = std::abs(object.vel.y);
	}
	else if (bounds.max.y > bottomLimit)
	{
		// Adjust the position to prevent going beyond the bottom boundary
		object.pos.y -= (bounds.max.y - bottomLimit);
		// Reflect the velocity of the object vertically
		object.vel.y = -std::abs(object.vel.y);
	}
}




float dotProduct(Vec2 v1, Vec2 v2) {
	return v1.x * v2.x + v1.y * v2.y;
}


CollisionSide getCollisionSide(const Body& ball, const Body& ground) {
	Body::Bounds ballBounds = ball.getBounds();
	Body::Bounds groundBounds = ground.getBounds();

	if (ballBounds.min.x > groundBounds.min.x && ballBounds.max.x < groundBounds.max.x) {
		// Ball is within the x range of the ground
		if (ballBounds.max.y < groundBounds.max.y) {
			// Ball is above the ground
			return CollisionSide::Top;
		}
		else {
			// Ball is below the ground
			return CollisionSide::Bottom;
		}
	}
	else if (ballBounds.min.y > groundBounds.min.y && ballBounds.max.y < groundBounds.max.y) {
		// Ball is within the y range of the ground
		if (ballBounds.max.x < groundBounds.max.x) {
			// Ball is to the left of the ground
			return CollisionSide::Left;
		}
		else {
			// Ball is to the right of the ground
			return CollisionSide::Right;
		}
	}

	return CollisionSide::None;
}

void GAME_SCENE::update(float deltaTime)
{

	if (isPaused) {
		return;
	}



	////player.Update(deltaTime);
	////ground.Update(deltaTime);

	for (Body& b : GameObjects) {
		if (b.isActive) {
			b.Update(deltaTime);
			c.setCollisionMask(b);
		}
	}


	//for (int i = 0; i < GameObjects.size(); i++) {
	//	for (const auto& entry : buttonActions) {
	//		if (IsButtonDown(entry.first)) {
	//			 
	//			GameObjects[1].vel.x = entry.second.first * 100; // left & right
	//			GameObjects[1].vel.y = entry.second.second * 100; // up & down
	//		}
	//	}
	//}





	if (hasWon) {
		App::PlaySoundW(".\\TestData\\hole.wav", false);
		Sleep(200);
		changeScene(new COLLISION_SCENE());
	}

	for (int i = 0; i < GameObjects.size(); i++) {


		if (c.CheckCircleCollision(GameObjects[0], GameObjects[1])) {

			GameObjects[0].m_sprite = *nullSprite;

			hasWon = true;


		}

	//	if (c.CheckBoxCollision(GameObjects[0], GameObjects[2])) {
	//
	//		/*
	//		object.pos.y -= bounds.max.y;
	//		//
	//		object.vel.y = std::abs(object.vel.y);*/
	//		//Body::Bounds groundBounds = ground.setBodyBounds();
	//		//GameObjects[0].pos.x -= groundBounds.max.x;
	//		//GameObjects[0].pos.y -= groundBounds.max.y;
	//		//GameObjects[0].vel.x = std::abs(GameObjects[0].vel.x);
	//		//GameObjects[0].vel.y = std::abs(GameObjects[0].vel.y);
	//		Body::Bounds ballBounds = ball.setBodyBounds();
	//		Body::Bounds groundBounds = ground.setBodyBounds();
	//
	//		// Calculate the overlap (how much the ball has penetrated into the block)
	//		float overlapX = ballBounds.min.x - groundBounds.max.x;
	//		float overlapY = ballBounds.min.y - groundBounds.max.y;
	//
	//		bool Top = ballBounds.min.y <= groundBounds.max.y && ballBounds.max.y >= groundBounds.min.y;
	//		bool Bottom = ballBounds.max.y >= groundBounds.min.y && ballBounds.min.y <= groundBounds.max.y;
	//
	//		// Ensure the overlap is positive
	//		overlapX = overlapX < 0 ? -overlapX : 0;
	//		overlapY = overlapY < 0 ? -overlapY : 0;
	//		///makes top work but not bottom
	//		if (Top) {
	//			GameObjects[0].pos.y -= overlapY;
	//			GameObjects[0].vel.y = std::abs(GameObjects[0].vel.y);
	//		}
	//		else if (Bottom) {
	//			GameObjects[0].pos.y += overlapY;
	//			GameObjects[0].vel.y = -std::abs(GameObjects[0].vel.y);
	//		}
	//
	//		///makes bottom work but not top 
	//				// Move the ball out of the block
	//				//if (overlapX < overlapY) {
	//				//    GameObjects[0].pos.x += overlapX;
	//				//    GameObjects[0].vel.x = -std::abs(GameObjects[0].vel.x);
	//				//}
	//				//else {
	//				//    GameObjects[0].pos.y += overlapY;
	//				//    GameObjects[0].vel.y = -std::abs(GameObjects[0].vel.y);
	//				//}
	//	}
	//}

		auto lineIntersection=[](const Vec2&l1p1,const Vec2&l1p2,const Vec2&l2p1,const Vec2&l2p2)->const Vec2{
			Vec2 vec=l1p2-l1p1;
			Vec2 vec2=l2p2-l2p1;
			float crossP=vec.x*vec2.y-vec.y*vec2.x;

			float rd = crossP;
			if (rd == 0) return Vec2{}; // Parallel or Colinear TODO: Return two points

			//Inverse rd product
			rd = 1.f / rd;

			//Cross products: 
			//rn = (b1b2 x b1a1)
			float rn = ((l2p2.x - l2p1.x) * (l1p1.y - l2p1.y) - (l2p2.y - l2p1.y) * (l1p1.x - l2p1.x)) * rd;
			//sn = (a1a2 x b1a1)
			float sn = ((l1p2.x - l1p1.x) * (l1p1.y - l2p1.y) - (l1p2.y - l1p1.y) * (l1p1.x - l2p1.x)) * rd;

			//Return the intersection depth
			//if (d) *d = rn;

			if (rn < 0.f || rn > 1.f || sn < 0.f || sn > 1.f)
				return Vec2{}; // Intersection not within line segment

			return Vec2{l1p1.x+rn*vec.x,l1p1.y+rn*vec.y};
		};

		Body&dynamicBody=GameObjects[0]; //Dynamic body
		Body&staticBody=GameObjects[2]; //Static body
		if (c.CheckBoxCollision(dynamicBody, staticBody)) {
			Body::Bounds sBounds=staticBody.getBounds(); //Static body bounds.
			Body::Bounds dBounds=dynamicBody.getBounds(); //Dynamic body bounds.

			bool Bottom=false,Top=false,Left=false,Right=false;

			float TLcornerAngle=sinf(((sBounds.min.x-sBounds.max.x)/2.f)/((Vec2{sBounds.max.x,sBounds.max.y}).getMag())); //We use this angle to determine the grade on which the top side versus the sides intersect.

			std::array<Vec2,8>dRectLines={
				Vec2{dBounds.max.x,dBounds.max.y}, //Top Line
				Vec2{dBounds.min.x,dBounds.max.y},
				Vec2{dBounds.min.x,dBounds.max.y}, //Right Line
				Vec2{dBounds.min.x,dBounds.min.y},
				Vec2{dBounds.max.x,dBounds.min.y}, //Bottom Line
				Vec2{dBounds.min.x,dBounds.min.y},
				Vec2{dBounds.max.x,dBounds.max.y}, //Left Line
				Vec2{dBounds.max.x,dBounds.min.y},
			};
			std::array<Vec2,8>sRectLines={
				Vec2{sBounds.max.x,sBounds.max.y}, //Top Line
				Vec2{sBounds.min.x,sBounds.max.y},
				Vec2{sBounds.min.x,sBounds.max.y}, //Right Line
				Vec2{sBounds.min.x,sBounds.min.y},
				Vec2{sBounds.max.x,sBounds.min.y}, //Bottom Line
				Vec2{sBounds.min.x,sBounds.min.y},
				Vec2{sBounds.max.x,sBounds.max.y}, //Left Line
				Vec2{sBounds.max.x,sBounds.min.y},
			};

			std::vector<Vec2>intersections;
			for(size_t i=0;i<dRectLines.size();i+=2){
				for(size_t j=0;j<sRectLines.size();j+=2){
					Vec2 intersection=lineIntersection(dRectLines[i],dRectLines[i+1],sRectLines[j],sRectLines[j+1]);
					if(intersection.x!=0.f&&intersection.y!=0.f)intersections.push_back(intersection);
				}
			}

			if(intersections.size()<2)throw;
			Vec2&pt1=intersections[0];
			Vec2&pt2=intersections[1];
			Vec2 midpoint={(pt1.x+pt2.x)/2.f,(pt1.y+pt2.y)/2.f};
		
			float incidenceAngle=atan2f(midpoint.y-staticBody.getPos().y,midpoint.x-staticBody.getPos().x);

			if(fabs(incidenceAngle)<TLcornerAngle){Right=true;}
			else if(incidenceAngle<PI-TLcornerAngle&&incidenceAngle>TLcornerAngle){Top=true;}
			else if(incidenceAngle>-PI+TLcornerAngle&&incidenceAngle<-TLcornerAngle){Bottom=true;}
			else Left=true;

			#pragma region Movement
			if (Top) {
				float overlapY=sBounds.max.y - dBounds.min.y;
				if(overlapY<0)throw;

				dynamicBody.pos.y += overlapY;
				dynamicBody.vel.y = std::abs(dynamicBody.vel.y);
			}
			else if (Bottom) {
				float overlapY=dBounds.max.y - sBounds.min.y;
				if(overlapY<0)throw;

				dynamicBody.pos.y -= overlapY;
				dynamicBody.vel.y = -std::abs(dynamicBody.vel.y);
			}

			if(Left){
				float overlapX=dBounds.min.x - sBounds.max.x;
				if(overlapX<0)throw;

				dynamicBody.pos.x -= overlapX;
				dynamicBody.vel.x = -std::abs(dynamicBody.vel.x);
			}else if(Right){
				float overlapX=sBounds.min.x - dBounds.max.x;
				if(overlapX<0)throw;

				dynamicBody.pos.x += overlapX;
				dynamicBody.vel.x = std::abs(dynamicBody.vel.x);
			}
			#pragma endregion
			
			c.setCollisionMask(dynamicBody);
		}

	}
	
	for (int i = 0; i < GameObjects.size(); i++) {

		App::GetMousePos(MousePos_Game.x, MousePos_Game.y);
		c.setBodyBounds(GameObjects[1]);

		mouseDown_game = (IsButtonDown(VK_LBUTTON));


		//some of the grossest code I wrote, When trying to optimize however it would break?
		if (mouseDown_game) {
		
			if (ballIntersect = inGivenBounds(Vec2(GameObjects[0].getBounds().max.x, GameObjects[0].getBounds().max.y),
				Vec2(GameObjects[0].getBounds().min.x, GameObjects[0].getBounds().min.y),
				MousePos_Game)) {

				drag = true; 
			}
		
		} else {
			drag = false;
		
			if (hasBeenDragged) {
				GameObjects[0].vel = (GameObjects[0].vel + diffrence) * 4;
				hasBeenDragged = false;
			}
		}
		
		if (drag) {
		
			GameObjects[0].vel = Vec2(0, 0);
			GameObjects[0].acc = Vec2(0, 0);
		
			hasBeenDragged = true;
	
			diffrence = MousePos_Game - GameObjects[0].pos;
			return;
		}

	

		checkScreenCollision(GameObjects[0]);




		//for (int j = i + 1; j < GameObjects.size(); j++) {
		//	if (c.CheckCollision(GameObjects[i], GameObjects[j], text)) {
		//		// Handle collision, e.g., set velocities to zero
		//		if (IsButtonDown(APP_PAD_EMUL_BUTTON_ALT_A)) {
		//			//GameObjects[i].vel.y += 1.0f;
		//			GameObjects[j].vel.y = 1.0f;
		//		}
		//		else {
		//			GameObjects[i].vel.y = 0.0f;
		//			GameObjects[j].vel.y = 0.0f;
		//		}
		//		GameObjects[i].acc = Vec2(0.0f, 0.0f);
		//		
		//		GameObjects[j].acc = Vec2(0.0f, 0.0f);
		//		
		//
		//		//Vec3 pt1 = Vec3(GameObjects[j].setBodyBounds().max.x, GameObjects[j].setBodyBounds().min.y, 0.0f);
		//		//Vec3 pt2 = Vec3(GameObjects[j].setBodyBounds().max.x, GameObjects[j].setBodyBounds().max.y, 0.0f);
		//		//float height = pt1.y - pt2.y;
		//		//GameObjects[j].pos.y = GameObjects[i].pos.y - height;
		//		//GameObjects[j].m_sprite.SetPosition(GameObjects[j].pos.x, GameObjects[i].pos.y - height);
		//
		//		//[j].ApplyForce(Vec2(0, GameObjects[j].mass * -GameObjects[j].gravity));
		//	}
		//}
	}

	//for (int i = 0; i < GameObjects.size(); i++) {
	//	for (int j = i + 1; j < GameObjects.size(); j++) {
	//		CollisionSide side;
	//		if (CheckCollision(GameObjects[i], GameObjects[j], side)) {
	//			// Handle collision based on side
	//			switch (side) {
	//			case Left:
	//				// Handle collision from the left side
	//				GameObjects[i].vel.x = 0.0f;
	//				GameObjects[i].acc.x = 0.0f;
	//				break;
	//			case Right:
	//				// Handle collision from the right side
	//				GameObjects[i].vel.x = 0.0f;
	//				GameObjects[i].acc.x = 0.0f;
	//				break;
	//			case Top:
	//				// Handle collision from the top side
	//				GameObjects[i].vel.y = 0.0f;
	//				GameObjects[i].acc.y = 0.0f;
	//				break;
	//			case Bottom:
	//				// Handle collision from the bottom side
	//				GameObjects[i].vel.y = 0.0f;
	//				GameObjects[i].acc.y = 0.0f;
	//				break;
	//			default:
	//				break;
	//			}
	//		}
	//	}
	//}

	
	///////////// controls  ///////////////////
	// 

	//for (const auto& entry : buttonActions) {
	//	if (IsButtonDown(entry.first)) {
	//		player.pos.x += entry.second.first * 100; // left & right
	//		player.pos.y += entry.second.second * 100; // up & down
	//	}
	//}

	if (App::IsKeyPressed('J'))
		tempPos.x -= 1;
	if (App::IsKeyPressed('L'))
		tempPos.x += 1;
	if (App::IsKeyPressed('I'))
		tempPos.y += 1;
	if (App::IsKeyPressed('K'))
		tempPos.y -= 1;



}

// renders in layers!!!!!!!!!!!!!

void GAME_SCENE::render(int WINDOW_W, int WINDOW_H)
{

	GameScene_camera.MoveCam(tempPos, WINDOW_W, WINDOW_H);


	game_background->Draw();

	//ground.m_sprite.Draw();
	//player.m_sprite.Draw();


	for (int i = 0; i < GameObjects.size(); i++) {

		GameObjects[i].m_sprite.Draw();

		if (drag) {
			shape.simpleLine({ 1,0,0 }, Vec3(GameObjects[0].pos.x, GameObjects[0].pos.y, 0), Vec3(MousePos_Game.x, MousePos_Game.y, 0));
		}

		switch (GameObjects[i].collisionMaskType) {
			case BOUNDING_BOX:
				// Draw bounding box
				c.drawCollisionQuadMask(GameObjects[i]);
				break;
			case CIRCLE:
				// Draw circle
				c.drawCollisionCircleMask(GameObjects[i]);
				break;
				// Add more cases for additional types
			default:
				// Handle unknown type or provide a default behavior
				break;
		}
		
	}

	//for (Body& b : GameObjects) {
	//	if (b.isActive) {
	//		b.m_sprite.Draw();
	//		//drawCollisionMask(b);
	//
	//		c.setCollisionMask(b, simpleCollision::CIRCLE);
	//	}
	//}


	

		//for (int i = 0; i < GameObjects.size(); i++) {
		//
		//	shape.simpleLine({ 1,0,0 }, Vec3(GameObjects[0].pos.x, GameObjects[0].pos.y, 0), Vec3(MousePos_Game.x, MousePos_Game.y, 0));
		//
		//}


	


	App::Print(500, 500, text);


	//simpleShape shp;
	//shp.simpleTriangle({ 1.0f, 0.0f, 0.0f }, Vec3(200.0f, 200.0f, 0.0f), Vec3(600.0f, 0.0f, 0.0f), Vec3(0.0f, 600.0f, 0.0f));
	//shp.simpleLine(Vec3 (0.0f, 1.0f, 0.0f) , Vec3(300.0, 200.0, 0.0), Vec3(700.0, 200.0, 0.0));

	glMatrixMode(GL_MODELVIEW);

}

void GAME_SCENE::exit()
{

	delete game_background;

	//for (Body& b : GameObjects) {
	//	delete& b;
	//}
	//delete& player;

}
