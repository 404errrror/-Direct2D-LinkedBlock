#include "stdafx.h"
#include "Camera.h"

Transform* Camera::traceObject = nullptr;
Vector2 Camera::position(0,0);
float Camera::smoothTrace = 10;
bool Camera::isStart = false;
Camera::Camera()
{
}


Camera::~Camera()
{
}


void Camera::SetSmooth(float smooth)
{
	if (smooth < 1)
		smooth = 1;
	smoothTrace = smooth;
}


void Camera::SetObject(Transform* traceObject)
{
	Camera::traceObject = traceObject;
}


void Camera::CameraUpdate()
{
	// 오브젝트를 추적하는 연산을 할 때는 화면 사이즈 position이 들어가면 안되는데
	// 맨 아래에서 연산을 했었으므로 그 값을 그대로 빼서 상쇄.
	if (isStart)
	{
		// 정확한 연산을 위해 윈도우 창틀? 크기도 빼주어야함.
		position.x += ((MAX_SCREEN_WIDTH - g_windowRight) * (g_screenWidthRatio / g_screenRatio) - (MAX_SCREEN_WIDTH - g_windowRight)) / 2;
		position.y -= ((MAX_SCREEN_HEIGHT - g_windowTop) * (g_screenHeightRatio / g_screenRatio) - (MAX_SCREEN_HEIGHT - g_windowTop)) / 2;
	}
	isStart = true;

	if (traceObject)
	{
		position = position + (traceObject->GetPosition() - position) * (1 / smoothTrace);
	}

	position.x -= ((MAX_SCREEN_WIDTH - g_windowRight) * (g_screenWidthRatio / g_screenRatio) - (MAX_SCREEN_WIDTH - g_windowRight)) / 2;
	position.y += ((MAX_SCREEN_HEIGHT - g_windowTop) * (g_screenHeightRatio / g_screenRatio) - (MAX_SCREEN_HEIGHT - g_windowTop)) / 2;

	// * Time::GetDeltaTime() -----------> 나중에 시간 곱해주기.
}


void Camera::Apply(Vector2& position)
{
	position.x -= Camera::position.x;
	position.y -= Camera::position.y;
}


void Camera::Apply(D2D1_POINT_2F& point)
{
	point.x -= position.x;
	point.y += position.y;
}


Vector2 Camera::GetCameraPos()
{
	return position;
}


void Camera::InstantlySetting()
{
	position.x += ((MAX_SCREEN_WIDTH - g_windowRight) * (g_screenWidthRatio / g_screenRatio) - (MAX_SCREEN_WIDTH - g_windowRight)) / 2;
	position.y -= ((MAX_SCREEN_HEIGHT - g_windowTop) * (g_screenHeightRatio / g_screenRatio) - (MAX_SCREEN_HEIGHT - g_windowTop)) / 2;
	if(traceObject)
		position = position + (traceObject->GetPosition() - position);
	else
		position = position + (Vector2(0,0) - position);

	position.x -= ((MAX_SCREEN_WIDTH - g_windowRight) * (g_screenWidthRatio / g_screenRatio) - (MAX_SCREEN_WIDTH - g_windowRight)) / 2;
	position.y += ((MAX_SCREEN_HEIGHT - g_windowTop) * (g_screenHeightRatio / g_screenRatio) - (MAX_SCREEN_HEIGHT - g_windowTop)) / 2;
}