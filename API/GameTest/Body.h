#ifndef _BODY_H_
#define _BODY_H_


#pragma once
#include "stdafx.h"
#include "app\app.h"
#include "CollisionType.h"

using namespace ZOE;

class Body {

public:

#pragma region defaults
	// Vectors set to [0,0,0] by their default constructor
	Vec2 pos; 
	Vec2 prevPos;
	Vec2 vel;
	Vec2 acc;

	CollisionMaskType collisionMaskType=BOUNDING_BOX;

	CSimpleSprite m_sprite;



	SimpleCamera2D cam;


	// A mass of 1 kg seems like a good default value
	float mass = 1.0f;
	// default gravity 9.8
	float gravity = 9.8f;
	float scale;

	const char* textureFile = "";

	float width = 1.0f, height = 1.0f;

	bool isActive;

	struct Bounds {
		Vec3 max;
		Vec3 min;
	};

	// Default Constructor //
	Body() {};

	//  body class for objects which takes in a: pos, vel, acc, mass, and texture file
	Body(Vec2 pos_, Vec2 vel_, Vec2 acc_,
		float mass_, float gravity_, CSimpleSprite m_sprite_, float scale_, bool _active, SimpleCamera2D _cam);


	void setWidth(float w_) {
		width = w_;
	}

	void setHeight(float h_) {
		height = h_;
	}

	float getWidth() {
		return width;
	}

	float getHeight() {
		return height;
	}

	void setBounds(const Bounds& newBounds) {
		bounds = newBounds;
	}


	// Getter for bounds
	Bounds getBounds() const {
		return bounds;
	}


#pragma endregion

#pragma region ApplyForce
	void ApplyForce(Vec2 force);
#pragma endregion

#pragma region update


	///  Update the location of this body based on the given detla time
	///  "deltaTime" Change in time from the previous frame
	void Update(float deltaTime);

	/// returns The current position of this body
	Vec2 getPos() {
		return pos;
	}

	Vec2 CalculateGravForceBy(float bigG, Body& other);
#pragma endregion 


#pragma region destructors
	// destructor //
	~Body();
#pragma endregion

private:

	Bounds bounds;
};


#endif