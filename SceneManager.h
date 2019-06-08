#pragma once
#include "TestScene.h"
#include "GameTestScene.h"
#include "StartScene.h"
#include "SelectScene.h"
#include "GameScene.h"

class SceneManager
{
public:
	enum SCENE_TYPE
	{
		SCENE_NONE,
		SCENE_TEST,
		SCENE_START,
		SCENE_SELECT,
		SCENE_GAME_TEST,
		SCENE_GAME
	};
	SceneManager();
	~SceneManager();

	static void Initialize(ID2D1HwndRenderTarget* hwndRenderTarget);
	static int Update();
	static int OnEvent(Event&);

	static void SetScene(SCENE_TYPE);
	static SCENE_TYPE GetScene();
private:
	static SceneClass* p_nowScene;

	static TestScene testScene;
	static GameTestScene gameScene;
	static StartScene startScene;
	static SelectScene selectScene;
	static GameScene gameScene2;

	static SCENE_TYPE m_nowScene;
};

