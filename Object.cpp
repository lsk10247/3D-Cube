#include "pch.h"
#include "Object.h"

Object::Object()
{
	vertices = nullptr;
	triangles = nullptr;
	normals = nullptr;

	position[0] = 0;
	position[1] = 0;
	position[2] = 0;
	verticessize = trianglessize = 12;
	vertices = new Eigen::Vector4f[verticessize];
	// 为顶点赋值
	vertices[0] = Eigen::Vector4f(-1.0, -1.0, -1.0, 1.0);
	vertices[1] = Eigen::Vector4f(1.0, -1.0, -1.0, 1.0);
	vertices[2] = Eigen::Vector4f(1.0, 1.0, -1.0, 1.0);
	vertices[3] = Eigen::Vector4f(-1.0, 1.0, -1.0, 1.0);
	vertices[4] = Eigen::Vector4f(-1.0, -1.0, 1.0, 1.0);
	vertices[5] = Eigen::Vector4f(1.0, -1.0, 1.0, 1.0);
	vertices[6] = Eigen::Vector4f(1.0, 1.0, 1.0, 1.0);
	vertices[7] = Eigen::Vector4f(-1.0, 1.0, 1.0, 1.0);

	// 为三角形赋值
	triangles = new Eigen::Vector3i[trianglessize];
	triangles[0] = Eigen::Vector3i(0, 1, 2);
	triangles[1] = Eigen::Vector3i(2, 3, 0);
	triangles[2] = Eigen::Vector3i(4, 5, 6);
	triangles[3] = Eigen::Vector3i(6, 7, 4);
	triangles[4] = Eigen::Vector3i(0, 1, 5);
	triangles[5] = Eigen::Vector3i(5, 4, 0);
	triangles[6] = Eigen::Vector3i(1, 2, 6);
	triangles[7] = Eigen::Vector3i(6, 5, 1);
	triangles[8] = Eigen::Vector3i(2, 3, 7);
	triangles[9] = Eigen::Vector3i(7, 6, 2);
	triangles[10] = Eigen::Vector3i(3, 0, 4);
	triangles[11] = Eigen::Vector3i(4, 7, 3);
}

void Object::RotateX(float x)
{
}

void Object::RotateY(float y)
{
}

void Object::RotateZ(float z)
{
}

void Object::Rotate(float x, float y, float z)
{
}

void Object::Move(float x, float y, float z)
{
	position[0] += x;
	position[1] += y;
	position[2] += z;
}
