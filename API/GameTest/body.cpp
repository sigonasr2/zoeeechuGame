#include "stdafx.h"
#include "Body.h"



Body::Body(Vec2 pos_, Vec2 vel_, Vec2 acc_, float mass_, float gravity_, CSimpleSprite m_sprite_, float scale_, bool _active, SimpleCamera2D _cam) {

	cam = _cam;
	pos = pos_;
	vel = vel_;
	acc = acc_;
	mass = mass_;
	gravity = gravity_;
	m_sprite = m_sprite_;
	scale = scale_;
	isActive = _active;
	m_sprite.SetScale(scale);
	m_sprite.SetPosition(pos.x, pos.y);

	//pos = cam.camPos - pos;
}

void Body::ApplyForce(Vec2 force)
{

	// Update acceleration using
	// F = ma

	acc = force / mass + acc;
	//acc.x = force.x / mass;
	//acc.y = force.y / mass;


}

void Body::Update(float deltaTime) {

	// we divide by 1000 becuase deltaTime = 16 and not 0.016

	float dt = deltaTime / 1000.0f;

	prevPos=pos;
	pos.y += vel.y * dt + 0.5f * acc.y * powf(dt, 2);
	pos.x += vel.x * dt + 0.5f * acc.x * powf(dt, 2);
	vel.y += acc.y * dt ;
	vel.x += acc.x * dt;

	ApplyForce(Vec2(0, -mass * gravity));

	m_sprite.SetPosition(pos.x,pos.y);
}

Vec2 Body::CalculateGravForceBy(float bigG, Body& other)
{
	Vec2 displacment = other.pos - pos;
	float magnitude = (bigG * mass * other.mass) / powf(displacment.getMag(), 2.0f);
	Vec2 gravForce = displacment.normeyes() * magnitude;
	return gravForce;
}

Body::~Body() {
}

