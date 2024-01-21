#pragma once
#include "stdafx.h"
#include "app\app.h"
#include "Body.h"

using namespace ZOE;


class simpleCollision {

public:

	enum CollisionMaskType {
		BOUNDING_BOX,
		CIRCLE,
	};


	void getBounds(Body& bdy);
	void drawCollisionQuadMask(Body& bdy);
	void drawCollisionCircleMask(Body& bdy);
	void setCollisionMask(Body& bdy, CollisionMaskType maskType);
	bool CheckBoxCollision(const Body& a, const Body& b,char* result = nullptr);
	bool CheckCircleCollision(const Body& a, const Body& b, char* result = nullptr);
	bool CheckCircleToBoxCollision(const Body& circle, const Body& box, char* result = nullptr);



	struct axis {
		Vec3 pt1;
		Vec3 pt2;
	};

	std::vector<axis> getAxisRect(const Body& bdy);

	//std::vector<axis> axisVector;


private:
};
