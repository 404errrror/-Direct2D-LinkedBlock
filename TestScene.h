#pragma once
#include "TestCharacter.h"
#include "TestRock.h"
#include "TestButton.h"


class TestScene : public SceneClass
{
public:
	TestScene();
	~TestScene();

	void Release();
	int Start();
	int Update();
	int OnEvent(_In_ Event&);
	
	void DrawMouse();
private:
	ID2D1SolidColorBrush* m_pSolidBrush;

	D2D1_POINT_2F m_prevMousePos;


	TestCharacter* myCharacter;
	TestCharacter* myCharacter2;
	TestRock* testRock;
	TestButton* testButton;
};

