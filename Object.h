#pragma once
#include<vector>
#include "eigen-3.4.0/Eigen/DENSE"
class Object
{
public:
	//��������
	float x, y, z;
	//��ת��
	float rotatex, rotatey, rotatez;
	Eigen::Vector4f* vertices;
	Eigen::Vector3i* triangles;
	Eigen::Vector3f* normals;
	Eigen::Vector3f position;

	int verticessize;
	int trianglessize;

	Object();
	void RotateX(float x);
	void RotateY(float y);
	void RotateZ(float z);
	void Rotate(float x, float y, float z);
	void Move(float x, float y, float z);
};

