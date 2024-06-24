#include"pch.h"
#include "Tool.h"
#include <iostream>
#include "eigen-3.4.0/Eigen/Dense"

const float pi = acos(-1);

//选转为右手系，顺时针

// 绕x轴旋转的旋转矩阵函数
Eigen::Matrix3f rotateX(float theta) {
	Eigen::Matrix3f Rx;
	Rx << 1, 0, 0,
		0, cos(theta), -sin(theta),
		0, sin(theta), cos(theta);
	return Rx;
}

// 绕y轴旋转的旋转矩阵函数
Eigen::Matrix3f rotateY(float theta) {
	Eigen::Matrix3f Ry;
	Ry << cos(theta), 0, sin(theta),
		0, 1, 0,
		-sin(theta), 0, cos(theta);
	return Ry;
}

// 绕z轴旋转的旋转矩阵函数
Eigen::Matrix3f rotateZ(float theta) {
	Eigen::Matrix3f Rz;
	Rz << cos(theta), -sin(theta), 0,
		sin(theta), cos(theta), 0,
		0, 0, 1;
	return Rz;
}

bool DrawLine(int x1, int y1, int x2, int y2, CDC* pdc)
{
	// 数值微分算法
	float k = (float)(y2 - y1) / (x2 - x1);
	COLORREF color = pdc->GetDCPenColor();

	if (k<1 && k>-1)
	{
		if (x2 < x1) {
			// 交换
			std::swap(x1, x2);
			std::swap(y1, y2);
		}
		float y = y1;
		POINT point = { x1, y1 };
		for (int i = x1; i <= x2; i++) {
			pdc->SetPixel(point, color);  
			point.x += 1;
			y += k;
			point.y = round(y);
		}
	}
	else {
		if (y2 < y1) {
			// 交换
			std::swap(x1, x2);
			std::swap(y1, y2);
		}
		k = 1 / k;
		float x = x1;
		POINT point = { x1, y1 };
		for (int i = y1; i <= y2; i++) {
			pdc->SetPixel(point, color);  
			point.y += 1;
			x += k;
			point.x = round(x);
		}
	}
	return true;
}

bool DrawLine2(int x1, int y1, int x2, int y2, CDC* pdc)
{
	if (x2 < x1) {
		// 交换
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	float k = (float)(y2 - y1) / (x2 - x1);
	COLORREF color = pdc->GetDCPenColor(); 

	int a, b, c, d0, dt1, dt2;
	POINT point = { x1, y1 };

	if (k <= 1 && k > 0) {
		// 正负法,第一象限下
		a = y1 - y2;
		b = x2 - x1;
		c = x1 * y2 - x2 * y1;
		d0 = 2 * a + b;
		dt1 = 2 * a;
		dt2 = 2 * (a + b);

		for (int i = x1; i <= x2; i++) {
			pdc->SetPixel(point, color); 
			if (d0 < 0) {
				point.x += 1;
				point.y += 1;
				d0 += dt2;
			}
			else {
				point.x += 1;
				d0 += dt1;
			}
		}
	}
	else if (k > 1) {
		// 正负法，,第一象限上
		a = x1 - x2;
		b = y2 - y1;
		c = y1 * x2 - y2 * x1;
		d0 = 2 * a + b;
		dt1 = 2 * a;
		dt2 = 2 * (a + b);

		for (int i = y1; i <= y2; i++) {
			pdc->SetPixel(point, color); 
			if (d0 < 0) {
				point.x += 1;
				point.y += 1;
				d0 += dt2;
			}
			else {
				point.y += 1;
				d0 += dt1;
			}
		}
	}
	else if (k >= -1) {
		// 正负法,第四象限上
		a = y1 - y2;
		b = x2 - x1;
		c = x1 * y2 - x2 * y1;
		d0 = 2 * a - b;
		dt1 = 2 * a;
		dt2 = 2 * (a - b);

		for (int i = x1; i <= x2; i++) {
			pdc->SetPixel(point, color);  
			if (d0 < 0) {
				point.x += 1;
				d0 += dt1;
			}
			else {
				point.x += 1;
				point.y -= 1;
				d0 += dt2;
			}
		}
	}
	else {
		// 正负法,第四象限下
		a = x1 - x2;
		b = y2 - y1;
		c = y1 * x2 - y2 * x1;
		d0 = 2 * a - b;
		dt1 = 2 * a;
		dt2 = 2 * (a - b);

		for (int i = y2; i <= y1; i++) {
			pdc->SetPixel(point, color);  
			if (d0 < 0) {
				point.y -= 1;
				point.x += 1;
				d0 += dt2;
			}
			else {
				point.y -= 1;
				d0 += dt1;
			}
		}
	}
	return true;
}


bool DrawLine3(int x1, int y1, int x2, int y2, CDC* pdc)
{
	int dx = abs(x2 - x1), dy = abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1, sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy, e2;

	while (true)
	{
		pdc->SetPixel(x1, y1, RGB(0, 0, 0));

		if (x1 == x2 && y1 == y2) break;

		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}
	}
	return true;
}


bool DrawCircle(int x, int y, int r, int delta, CDC* pdc)
{
	for (int i = 0; i < delta; i++) {
		float d = pi / 2 / delta;
		DrawLine3(round(x + r * cos(d * i)), round(y + r * sin(d * i)), round(x + r * cos(d * (i + 1))), round(y + r * sin(d * (i + 1))), pdc);
		DrawLine3(round(x + r * cos(d * i)), round(y - r * sin(d * i)), round(x + r * cos(d * (i + 1))), round(y - r * sin(d * (i + 1))), pdc);
		DrawLine3(round(x - r * cos(d * i)), round(y + r * sin(d * i)), round(x - r * cos(d * (i + 1))), round(y + r * sin(d * (i + 1))), pdc);
		DrawLine3(round(x - r * cos(d * i)), round(y - r * sin(d * i)), round(x - r * cos(d * (i + 1))), round(y - r * sin(d * (i + 1))), pdc);
	}
	return true;
}


bool DrawCircle2(int x0, int y0, int r, int delta, CDC* pdc)
{
	POINT point;
	int x, y, d;
	x = 0; y = r; d = 3 - 2 * r;
	point.x = x0;
	point.y = y0 + r;
	while (x < y) {
		//x,y
		pdc->SetPixel(point, pdc->GetDCPenColor());
		point.x = x0 - x;
		//-x,y
		pdc->SetPixel(point, pdc->GetDCPenColor());
		point.y = y0 - y;
		//-x,-y
		pdc->SetPixel(point, pdc->GetDCPenColor());
		point.x = x0 + x;
		//x,-y
		pdc->SetPixel(point, pdc->GetDCPenColor());
		point.x = x0 + y;
		point.y = y0 + x;
		//y,x
		pdc->SetPixel(point, pdc->GetDCPenColor());
		point.y = y0 - x;
		//y,-x
		pdc->SetPixel(point, pdc->GetDCPenColor());
		point.x = x0 - y;
		//-y,-x
		pdc->SetPixel(point, pdc->GetDCPenColor());
		point.y = y0 + x;
		//-y,x
		pdc->SetPixel(point, pdc->GetDCPenColor());
		point.x = x0 + x;
		point.y = y0 + y;

		if (d < 0) {
			d = d + 4 * x + 6;
		}
		else {
			d = d + 4 * (x - y) + 10;
			point.y -= 1;
			y -= 1;
		}
		point.x += 1;
		x += 1;
		if (x == y) {
			//x,y
			pdc->SetPixel(point, pdc->GetDCPenColor());
			point.x = x0 - x;
			//-x,y
			pdc->SetPixel(point, pdc->GetDCPenColor());
			point.y = y0 - y;
			//-x,-y
			pdc->SetPixel(point, pdc->GetDCPenColor());
			point.x = x0 + x;
			//x,-y
			pdc->SetPixel(point, pdc->GetDCPenColor());
			point.x = x0 + y;
			point.y = y0 + x;
			//y,x
			pdc->SetPixel(point, pdc->GetDCPenColor());
			point.y = y0 - x;
			//y,-x
			pdc->SetPixel(point, pdc->GetDCPenColor());
			point.x = x0 - y;
			//-y,-x
			pdc->SetPixel(point, pdc->GetDCPenColor());
			point.y = y0 + x;
			//-y,x
			pdc->SetPixel(point, pdc->GetDCPenColor());
			point.x = x0 + x;
			point.y = y0 + y;
		}
	}
	return false;
}

void DrawObject(Object object, Eigen::Matrix4f worldtoscreen,CDC* pDC)
{
	Eigen::Vector4f* vertices = new Eigen::Vector4f[object.verticessize];
	for (int i = 0; i < object.verticessize; i++) {
		vertices[i] = worldtoscreen * (object.vertices[i] + Eigen::Vector4f(object.position[0], object.position[1], object.position[2], 1));
		vertices[i] /= vertices[i][3];
	}
	for (int i = 0; i < object.trianglessize; i++) {
		DrawLine(vertices[object.triangles[i][0]][0], 1000 - vertices[object.triangles[i][0]][2], vertices[object.triangles[i][1]][0], 1000 - vertices[object.triangles[i][1]][2], pDC);
		DrawLine(vertices[object.triangles[i][0]][0], 1000 - vertices[object.triangles[i][0]][2], vertices[object.triangles[i][2]][0], 1000 - vertices[object.triangles[i][2]][2], pDC);
		DrawLine(vertices[object.triangles[i][1]][0], 1000 - vertices[object.triangles[i][1]][2], vertices[object.triangles[i][2]][0], 1000 - vertices[object.triangles[i][2]][2], pDC);
	}
}
