#pragma once
#include "stdafx.h"
#include "app\app.h"

using namespace ZOE;

class simpleShape {

public:
    void simplePoint(Vec3 rgb, Vec3 pt);
    void simpleLine(Vec3 rgb, Vec3 startPt, Vec3 endPt, bool fill = true);
    void simpleLineStrip(Vec3 rgb, const std::vector<Vec3>& points, bool fill = true);
    void simpleLineLoop(Vec3 rgb, const std::vector<Vec3>& points, bool fill = true);
    void simpleTriangle(Vec3 rgb, Vec3 pt1, Vec3 pt2, Vec3 pt3, bool fill = true);
    void simpleTriangleStrip(Vec3 rgb, const std::vector<Vec3>& points, bool fill = true);
    void simpleTriangleFan(Vec3 rgb, const std::vector<Vec3>& points, bool fill = true);
    void simpleQuad(Vec3 rgb, const std::vector<Vec3>& points, bool fill = true);
    void simpleQuadStrip(Vec3 rgb, const std::vector<Vec3>& points, bool fill = true);
    void simplePolygon(Vec3 rgb, const std::vector<Vec3>& points, bool fill = true);
    void simpleCircle(Vec3 rgb, Vec3 center, float radius, int segments, bool fill);
};
