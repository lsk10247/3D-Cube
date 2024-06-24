#pragma once
#include "pch.h"
#include "eigen-3.4.0/Eigen/Dense"
#include "Object.h"
#include "Camera.h"
Eigen::Matrix3f rotateX(float theta);
Eigen::Matrix3f rotateY(float theta);
Eigen::Matrix3f rotateZ(float theta);
bool DrawLine(int x1, int y1, int x2, int y2, CDC* pdc);
bool DrawLine2(int x1, int y1, int x2, int y2, CDC* pdc);
bool DrawLine3(int x1, int y1, int x2, int y2, CDC* pdc);
bool DrawCircle(int x, int y, int r, int delta, CDC* pdc);
bool DrawCircle2(int x, int y, int r, int delta, CDC* pdc);
void DrawObject(Object object, Eigen::Matrix4f worldtoscreen, CDC* pDC);