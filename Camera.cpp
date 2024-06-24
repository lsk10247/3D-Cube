#include "pch.h"
#include "Camera.h"

Camera::Camera()
{
	x = y = z = rotatex = rotatey = rotatez = 0;
    //Eigen::Vector4f pos;
    //pos(0) = 0;
    //pos(1) = 50;
    //pos(2) = 0;
    //pos(3) = 1;
    //rotatex = 0.1;
    //Eigen::Matrix4f matrix = WorldToCameraMatrix(0,0,0);
    ////pos = PerspectiveProjection(1, 1, 1, 100)*matrix * pos;
    //matrix = WorldToScreenMatrix(-1, -1, 2, 2, 1, 100);
    //pos = matrix * pos;
    //pos /= pos(3);
    //pos(3) = 1;
}

Camera::Camera(float x, float y, float z)
{
	Camera();
	this->x = x;
	this->y = y;
	this->z = z;
}

Camera::~Camera()
{
}
Eigen::Matrix4f Camera::TranslateMatrix(float x, float y, float z)
{
    Eigen::Matrix4f translate = Eigen::Matrix4f::Identity();

    translate(0, 3) = x;
    translate(1, 3) = y;
    translate(2, 3) = z;

    return translate;
}

Eigen::Vector4f Camera::WorldToCamera(Eigen::Vector3f pos)
{
	Eigen::Matrix4f matrix = WorldToCameraMatrix();
	Eigen::Vector4f pos4(pos(0), pos(1), pos(2), 1.0f); // 将3D点转换为4D点
	return matrix * pos4;
}

Eigen::Vector4f Camera::WorldToCamera(float x, float y, float z)
{
	Eigen::Matrix4f matrix = WorldToCameraMatrix();
	Eigen::Vector4f pos4(x, y, z, 1.0f); // 将3D点转换为4D点
	return matrix * pos4;
}

Eigen::Matrix4f Camera::WorldToCameraMatrix()
{
	Eigen::Matrix4f matrix = Eigen::Matrix4f::Identity();
	Eigen::Matrix3f rotation = rotateZ(rotatez) * rotateY(rotatey) * rotateX(rotatex);
	matrix.block<3, 3>(0, 0) = rotation.transpose();
    Eigen::Matrix4f translation = TranslateMatrix(-x, -y, -z);
	return matrix * translation;
}
Eigen::Matrix4f Camera::PerspectiveProjection(float fov, float aspect, float nearframe, float farframe)
{
    Eigen::Matrix4f projection = Eigen::Matrix4f::Zero();
    float tanHalfFOV = tan(fov / 2.0f);

    //projection(0, 0) = 1.0f / (aspect * tanHalfFOV);
    //projection(2, 2) = 1.0f / tanHalfFOV;
    //projection(1, 1) = -(farframe + nearframe) / (farframe - nearframe);
    //projection(1, 3) = -1.0f;
    //projection(3, 1) = -(2.0f * farframe * nearframe) / (farframe - nearframe);

    projection(0, 0) = nearframe;
    projection(1, 2) = nearframe + farframe;
    projection(1, 3) = -nearframe * farframe;
    projection(2, 2) = nearframe;
    projection(3, 1) = 1;

    return OrthographicProjection(-tanHalfFOV * nearframe, tanHalfFOV * nearframe, -tanHalfFOV * nearframe / aspect, tanHalfFOV * nearframe / aspect, nearframe, farframe) * projection;
}

Eigen::Matrix4f Camera::OrthographicProjection(float left, float right, float bottom, float top, float nearframe, float farframe)
{
    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();

    projection(0, 0) = 2.0f / (right - left);
    projection(2, 2) = 2.0f / (top - bottom);
    projection(1, 1) = -2.0f / (farframe - nearframe);
    projection(0, 3) = -(right + left) / (right - left);
    projection(2, 3) = -(top + bottom) / (top - bottom);
    projection(1, 3) = -(farframe + nearframe) / (farframe - nearframe);

    return projection;
}

Eigen::Matrix4f Camera::ViewportTransform(float x, float y, float width, float height, float nearframe, float farframe)
{
    Eigen::Matrix4f viewport = Eigen::Matrix4f::Identity();

    viewport(0, 0) = width / 2.0f;
    viewport(2, 2) = height / 2.0f;
    viewport(1, 1) = (farframe - nearframe) / 2.0f;

    viewport(0, 3) = x + width / 2.0f;
    viewport(2, 3) = y + height / 2.0f;
    viewport(1, 3) = (farframe + nearframe) / 2.0f;

    return viewport;
}

Eigen::Matrix4f Camera::WorldToScreenMatrix(float viewportX, float viewportY, float viewportWidth, float viewportHeight, float nearframe, float farframe)
{
    Eigen::Matrix4f worldToCamera = WorldToCameraMatrix();
    Eigen::Matrix4f perspective = PerspectiveProjection(1., 1., nearframe, farframe);
    Eigen::Matrix4f viewport = ViewportTransform(viewportX, viewportY, viewportWidth, viewportHeight, nearframe, farframe);

    return viewport * perspective * worldToCamera;
}
