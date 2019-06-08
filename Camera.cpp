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
	// ������Ʈ�� �����ϴ� ������ �� ���� ȭ�� ������ position�� ���� �ȵǴµ�
	// �� �Ʒ����� ������ �߾����Ƿ� �� ���� �״�� ���� ���.
	if (isStart)
	{
		// ��Ȯ�� ������ ���� ������ âƲ? ũ�⵵ ���־����.
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

	// * Time::GetDeltaTime() -----------> ���߿� �ð� �����ֱ�.
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