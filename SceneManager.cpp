#include "stdafx.h"
#include "SceneManager.h"

SceneClass* SceneManager::p_nowScene;
TestScene SceneManager::testScene;
GameTestScene SceneManager::gameScene;
StartScene SceneManager::startScene;
SelectScene SceneManager::selectScene;
GameScene SceneManager::gameScene2;
SceneManager::SCENE_TYPE SceneManager::m_nowScene;

SceneManager::SceneManager()
{
	p_nowScene = nullptr;
	m_nowScene = SCENE_NONE;
}


SceneManager::~SceneManager()
{
}


void SceneManager::Initialize(ID2D1HwndRenderTarget* hwndRenderTarget)
{
	testScene.Initialize(hwndRenderTarget);
	gameScene.Initialize(hwndRenderTarget);
	startScene.Initialize(hwndRenderTarget);
	selectScene.Initialize(hwndRenderTarget);
	gameScene2.Initialize(hwndRenderTarget);
}


int SceneManager::Update()
{
	if (p_nowScene == nullptr)
	{
		MessageBox(g_hwnd, L"SceneManager::Update()\nSceneManager::SetScene으로 씬을 설정해주세요.", L"Update()", MB_ICONERROR);
		return -1;
	}

	return p_nowScene->Update();
}


int SceneManager::OnEvent(Event& event)
{
	if (p_nowScene == nullptr)
		return -1;
	switch (event.GetType())
	{
	case Event::SYSTEM_RESIZE:
		//testScene.OnEvent(event);
		//startScene.OnEvent(event);
		//gameScene.OnEvent(event);
		p_nowScene->OnEvent(event);
		return 0;
	}
	return p_nowScene->OnEvent(event);
}


void SceneManager::SetScene(SCENE_TYPE type)
{
	m_nowScene = type;
	switch (type)
	{
	case SceneManager::SCENE_NONE:			p_nowScene = nullptr;			break;
	case SceneManager::SCENE_TEST:			p_nowScene = &testScene;		break;
	case SceneManager::SCENE_START:			p_nowScene = &startScene;		break;
	case SceneManager::SCENE_SELECT:		p_nowScene = &selectScene;		break;
	case SceneManager::SCENE_GAME_TEST:		p_nowScene = &gameScene;		break;
	case SceneManager::SCENE_GAME:			p_nowScene = &gameScene2;		break;
	}
}


SceneManager::SCENE_TYPE SceneManager::GetScene()
{
	return m_nowScene;
}