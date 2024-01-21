#include "stdafx.h"


void SimpleCamera2D::MoveCam(Vec2 pos_, int w_, int h_)
{

	glViewport(pos_.x, pos_.y, w_, h_);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
	glutPostRedisplay();


}
