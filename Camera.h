#pragma once

class Transform;

class Camera
{
public:
	Camera();
	~Camera();

	// smooth의 크기가 클수록 카메라가 부드러워집니다. 대신 속도가 감소합니다.
	static void SetSmooth(float smooth);
	static void SetObject(Transform* traceObject);
	static void CameraUpdate();

	static void Apply(Vector2& position);
	static void Apply(D2D1_POINT_2F& point);

	static Vector2 GetCameraPos();
	static void InstantlySetting();


private:
	static Transform* traceObject;
	static Vector2 position;
	static float smoothTrace;
	static bool isStart;
};

