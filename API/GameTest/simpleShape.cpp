#include "simpleShape.h"
#include "stdafx.h"


void simpleShape::simplePoint(Vec3 rgb, Vec3 pt)
{
    glBegin(GL_POINTS);
    glColor3f(rgb.x, rgb.y, rgb.z);
    APP_VIRTUAL_TO_NATIVE_COORDS(pt.x, pt.y);
    glVertex3f(pt.x, pt.y, pt.z);
    glEnd();
}

void simpleShape::simpleLine(Vec3 rgb, Vec3 startPt, Vec3 endPt, bool fill)
{


    glBegin(fill ? GL_LINES : GL_LINE_LOOP);
    glColor3f(rgb.x, rgb.y, rgb.z);
    APP_VIRTUAL_TO_NATIVE_COORDS(startPt.x, startPt.y);
    APP_VIRTUAL_TO_NATIVE_COORDS(endPt.x, endPt.y);
    glVertex3f(startPt.x, startPt.y, startPt.z);
    glVertex3f(endPt.x, endPt.y, endPt.z);
    glEnd();

    
}

void simpleShape::simpleLineStrip(Vec3 rgb, const std::vector<Vec3>& points, bool fill)
{
    if (fill) {
        glBegin(GL_LINE_STRIP);
        glColor3f(rgb.x, rgb.y, rgb.z);
        for (const auto& pt : points) {
            float x = pt.x; float y = pt.y;
            APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
            glVertex3f(x, y, pt.z);
        }
        glEnd();

        return;
    }

    glBegin(GL_LINE_STRIP);
    glColor3f(rgb.x, rgb.y, rgb.z);
    for (const auto& pt : points) {
        float x = pt.x; float y = pt.y;
        APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
        glVertex3f(x, y, pt.z);
    }
    glEnd();
    
}

void simpleShape::simpleLineLoop(Vec3 rgb, const std::vector<Vec3>& points, bool fill)
{
    if (fill) {
        glBegin(GL_LINE_LOOP);
        glColor3f(rgb.x, rgb.y, rgb.z);
        for (const auto& pt : points) {
            float x = pt.x; float y = pt.y;
            APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
            glVertex3f(x, y, pt.z);
        }
        glEnd();

        return;
    }

    glBegin(GL_LINE_LOOP);
    glColor3f(rgb.x, rgb.y, rgb.z);
    for (const auto& pt : points) {
        float x = pt.x; float y = pt.y;
        APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
        glVertex3f(x, y, pt.z);
    }
    glEnd();
    
}

void simpleShape::simpleTriangle(Vec3 rgb, Vec3 pt1, Vec3 pt2, Vec3 pt3, bool fill)
{

    glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
    glColor3f(rgb.x, rgb.y, rgb.z);
    APP_VIRTUAL_TO_NATIVE_COORDS(pt1.x, pt1.y);
    APP_VIRTUAL_TO_NATIVE_COORDS(pt2.x, pt2.y);
    APP_VIRTUAL_TO_NATIVE_COORDS(pt3.x, pt3.y);
    glVertex3f(pt1.x, pt1.y, pt1.z);
    glVertex3f(pt2.x, pt2.y, pt2.z);
    glVertex3f(pt3.x, pt3.y, pt3.z);
    glEnd();
}

void simpleShape::simpleTriangleStrip(Vec3 rgb, const std::vector<Vec3>& points, bool fill)
{
    //TODO
}

void simpleShape::simpleTriangleFan(Vec3 rgb, const std::vector<Vec3>& points, bool fill)
{
    //TODO
}

void simpleShape::simpleQuad(Vec3 rgb, const std::vector<Vec3>& points, bool fill)
{

    glBegin(fill ? GL_QUADS : GL_LINE_LOOP );
    glColor3f(rgb.x, rgb.y, rgb.z);
    for (const auto& pt : points) {
        float x = pt.x; float y = pt.y;
        APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
        glVertex3f(x, y, pt.z);
    }
    glEnd();
}

void simpleShape::simpleQuadStrip(Vec3 rgb, const std::vector<Vec3>& points, bool fill)
{
    if (fill) {
        glBegin(GL_QUAD_STRIP);
        glColor3f(rgb.x, rgb.y, rgb.z);
        for (const auto& pt : points) {
            float x = pt.x; float y = pt.y;
            APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
            glVertex3f(x, y, pt.z);
        }
        glEnd();

        return;
    }
   
}

void simpleShape::simplePolygon(Vec3 rgb, const std::vector<Vec3>& points, bool fill)
{
    if (fill) {
        glBegin(GL_POLYGON);
        glColor3f(rgb.x, rgb.y, rgb.z);
        for (const auto& pt : points) {
            float x = pt.x; float y = pt.y;
            APP_VIRTUAL_TO_NATIVE_COORDS(x, y);
            glVertex3f(x, y, pt.z);
        }
        glEnd();

        return; 
    }

}

void simpleShape::simpleCircle(Vec3 rgb, Vec3 center, float radius, int segments, bool fill)
{
    glBegin(fill ? GL_POLYGON : GL_LINE_LOOP);


    glColor3f(rgb.x, rgb.y, rgb.z);


    for (int i = 0; i < segments; ++i) {
        float theta = 2.0f * PI * static_cast<float>(i) / static_cast<float>(segments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);

        float newX = center.x + x;
        float newY = center.y + y;

        APP_VIRTUAL_TO_NATIVE_COORDS(newX, newY);

        glVertex3f(newX, newY, center.z);
    }

    glEnd();
}

