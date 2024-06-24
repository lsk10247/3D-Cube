#pragma once
#include "eigen-3.4.0/Eigen/DENSE"
#include "Tool.h"
#include "Object.h"
class Camera
{
public:
	//坐标
	float x, y, z;
	//旋转角
	float rotatex, rotatey, rotatez;

	Camera();
	Camera(float x,float y,float z);
	~Camera();
	Eigen::Matrix4f TranslateMatrix(float x, float y, float z);
	Eigen::Vector4f WorldToCamera(Eigen::Vector3f pos);
	Eigen::Vector4f WorldToCamera(float x,float y,float z);
	Eigen::Matrix4f WorldToCameraMatrix();
	//aspect:宽高比
	Eigen::Matrix4f PerspectiveProjection(float fov, float aspect, float nearframe, float farframe);
	Eigen::Matrix4f OrthographicProjection(float left, float right, float bottom, float top, float nearframe, float farframe);
	Eigen::Matrix4f ViewportTransform(float x, float y, float width, float height, float nearframe, float farframe);
	Eigen::Matrix4f WorldToScreenMatrix(float viewportX, float viewportY, float viewportWidth, float viewportHeight, float nearframe, float farframe);
};

