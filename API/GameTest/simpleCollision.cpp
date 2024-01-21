#include "simpleCollision.h"
#include "stdafx.h"



void simpleCollision::getBounds(Body& bdy) {

	Vec2 scale_, pos_, a, b;
	Body::Bounds result;
	scale_.x = bdy.m_sprite.GetWidth();
	scale_.y = bdy.m_sprite.GetHeight();

	pos_.x = bdy.pos.x; pos_.y = bdy.pos.y;

	a.x = (pos_.x - (scale_.x / 2) * bdy.scale);
	a.y = (pos_.y + (scale_.y / 2) * bdy.scale);
	b.x = (pos_.x + (scale_.x / 2) * bdy.scale);
	b.y = (pos_.y - (scale_.y / 2) * bdy.scale);


	result.min = Vec3(a.x, a.y, 0.0f);
	result.max = Vec3(b.x, b.y, 0.0f);

	bdy.setBounds(result);

}

void simpleCollision::drawCollisionQuadMask(Body& bdy) {

	simpleShape shape;

	std::vector<Vec3> quadVertices = {
		{bdy.getBounds().min.x, bdy.getBounds().max.y, 0.0f},
		{bdy.getBounds().min.x, bdy.getBounds().min.y, 0.0f},
		{bdy.getBounds().max.x, bdy.getBounds().min.y, 0.0f},
		{bdy.getBounds().max.x, bdy.getBounds().max.y, 0.0f}
	};

	shape.simpleQuad({ 0.0f, 1.0f, 0.0f }, quadVertices, false);
}

void simpleCollision::drawCollisionCircleMask(Body& bdy) {
	simpleShape shape;

	// Number of vertices to approximate the circle
	int numVertices = 32;

	// Center of the circle
	Vec3 center = Vec3((bdy.getBounds().min.x + bdy.getBounds().max.x) / 2.0f,
		(bdy.getBounds().min.y + bdy.getBounds().max.y) / 2.0f,
		0.0f);

	// Radius of the circle
	float radius = (bdy.getBounds().max.x - bdy.getBounds().min.x) / 2.0f;

	// Calculate vertices for the circle
	std::vector<Vec3> circleVertices;
	for (int i = 0; i < numVertices; ++i) {
		float theta = 2.0f * PI * static_cast<float>(i) / static_cast<float>(numVertices);
		float x = center.x + radius * cosf(theta);
		float y = center.y + radius * sinf(theta);
		circleVertices.push_back(Vec3(x, y, 0.0f));
	}

	// Draw the circle using quad vertices
	for (int i = 0; i < numVertices; ++i) {
		Vec3 vertex1 = circleVertices[i];
		Vec3 vertex2 = circleVertices[(i + 1) % numVertices];
		shape.simpleLine({ 0.0f, 1.0f, 0.0f }, vertex1, vertex2, false);
	}
}

void simpleCollision::setCollisionMask(Body& bdy, CollisionMaskType maskType) {

	getBounds(bdy);

	switch (maskType) {
	case BOUNDING_BOX:
		// Draw bounding box
		drawCollisionQuadMask(bdy);
		break;
	case CIRCLE:
		// Draw circle
		drawCollisionCircleMask(bdy);
		break;
		// Add more cases for additional types
	default:
		// Handle unknown type or provide a default behavior
		break;
	}
	//drawCollisionCircleMask(bdy);
}


bool simpleCollision::CheckCircleCollision(const Body& a, const Body& b, char* result)
{
	const Body::Bounds& A = a.getBounds();
	const Body::Bounds& B = b.getBounds();

	// Calculate the center and radius of each circle
	Vec3 centerA = Vec3((A.min.x + A.max.x) / 2.0f, (A.min.y + A.max.y) / 2.0f, 0.0f);
	Vec3 centerB = Vec3((B.min.x + B.max.x) / 2.0f, (B.min.y + B.max.y) / 2.0f, 0.0f);

	float radiusA = (A.max.x - A.min.x) / 2.0f;
	float radiusB = (B.max.x - B.min.x) / 2.0f;

	// Calculate the distance between the centers of the circles
	float distance = sqrt(pow(centerB.x - centerA.x, 2) + pow(centerB.y - centerA.y, 2));

	// Check if the circles overlap
	return distance <= (radiusA + radiusB);
}

bool simpleCollision::CheckCircleToBoxCollision(const Body& circle, const Body& box, char* result)
{
	const Body::Bounds& circleBounds = circle.getBounds();
	const Body::Bounds& boxBounds = box.getBounds();

	// Calculate the center and radius of the circle
	Vec3 circleCenter = Vec3((circleBounds.min.x + circleBounds.max.x) / 2.0f,
		(circleBounds.min.y + circleBounds.max.y) / 2.0f,
		0.0f);

	float circleRadius = (circleBounds.max.x - circleBounds.min.x) / 2.0f;

	// Calculate the half extents of the box
	float boxHalfWidth = (boxBounds.max.x - boxBounds.min.x) / 2.0f;
	float boxHalfHeight = (boxBounds.max.y - boxBounds.min.y) / 2.0f;

	// Calculate the distance between the circle center and the box center
	float deltaX = abs(circleCenter.x - (boxBounds.min.x + boxHalfWidth));
	float deltaY = abs(circleCenter.y - (boxBounds.min.y + boxHalfHeight));

	// Clamp the distance to stay within the box's half extents
	float clampedX = max(deltaX - boxHalfWidth, 0.0f);
	float clampedY = max(deltaY - boxHalfHeight, 0.0f);

	// Calculate the squared distance between the circle center and the closest point on the box
	float squaredDistance = clampedX * clampedX + clampedY * clampedY;

	// Check if the squared distance is less than the squared radius of the circle
	return squaredDistance <= (circleRadius * circleRadius);
}


bool simpleCollision::CheckBoxCollision(const Body& a, const Body& b, char* result)
{
	// Get the bounds of body a and b
	const Body::Bounds& A = a.getBounds();
	const Body::Bounds& B = b.getBounds();

	// set a offset, 6 pixels seems to work best 
	float offset = 6.0f;

	// check collsions
	bool collisionX = A.min.x <= B.max.x + offset && A.max.x + offset >= B.min.x;
	bool collisionY = A.max.y <= B.min.y + offset && A.min.y + offset >= B.max.y;

	return collisionX && collisionY;

}




std::vector<simpleCollision::axis> simpleCollision::getAxisRect(const Body& bdy)
{
	const Body::Bounds& b = bdy.getBounds();

	simpleCollision::axis a;
	std::vector<simpleCollision::axis> axisVector;

	Vec3 point1(b.min.x, b.max.y, 0.0f); // bottom left
	Vec3 point2(b.max.x, b.max.y, 0.0f); // bottom right
	Vec3 point3(b.max.x, b.min.y, 0.0f); // top right
	Vec3 point4(b.min.x, b.min.y, 0.0f); // top left

	axisVector.push_back({ a.pt1 = point1, a.pt2 = point2 });
	axisVector.push_back({ a.pt1 = point2, a.pt2 = point3 });
	axisVector.push_back({ a.pt1 = point3, a.pt2 = point4 });
	axisVector.push_back({ a.pt1 = point4, a.pt2 = point1 });

	return axisVector;
}

