#pragma once

class Transform;

class Camera
{
public:
	Camera();
	~Camera();

	// smooth�� ũ�Ⱑ Ŭ���� ī�޶� �ε巯�����ϴ�. ��� �ӵ��� �����մϴ�.
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

