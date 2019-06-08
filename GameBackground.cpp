#include "stdafx.h"
#include "GameBackground.h"


GameBackground::GameBackground()
{
	m_pRock = nullptr;
	m_pTree = nullptr;
	m_pHalfTree = nullptr;
	m_pFire = nullptr;
}


GameBackground::~GameBackground()
{
}


void GameBackground::Initialize()
{
	GameObject::Initialize();
	ObjectSetting(m_pRock);

	ObjectSetting(m_pTree);
	ObjectSetting(m_pHalfTree);
	ObjectSetting(m_pFire);

	m_pRock->SetId("Rock");
	m_pTree->SetId("Tree");
	m_pHalfTree->SetId("HalfTree");
	m_pFire->SetId("Fire");

	m_pRock->GetComponentHub()->m_pImage->SetImage(g_hasher("Rock"));
	m_pTree->GetComponentHub()->m_pImage->SetImage(g_hasher("Tree"));
	m_pHalfTree->GetComponentHub()->m_pImage->SetImage(g_hasher("HalfTree"));
	m_pFire->GetComponentHub()->m_pImage->SetImage(g_hasher("Fire@1"));

	m_pRock->GetComponentHub()->m_pTransform->SetPosition(Vector2(100, 250));
	m_pTree->GetComponentHub()->m_pTransform->SetPosition(Vector2(550, 280));
	m_pHalfTree->GetComponentHub()->m_pTransform->SetPosition(Vector2(-500, 250));
	m_pFire->GetComponentHub()->m_pTransform->SetPosition(Vector2(0, -160));

	m_pFire->GetComponentHub()->AddComponent(ComponentHub::FRAME_ANIMATION);
	m_pFire->GetComponentHub()->m_pFrameAnimation->AddImage(g_hasher("Idle"), g_hasher("Fire@1"));
	m_pFire->GetComponentHub()->m_pFrameAnimation->AddImage(g_hasher("Idle"), g_hasher("Fire@2"));
	m_pFire->GetComponentHub()->m_pFrameAnimation->AddImage(g_hasher("Idle"), g_hasher("Fire@3"));
	m_pFire->GetComponentHub()->m_pFrameAnimation->AddImage(g_hasher("Idle"), g_hasher("Fire@4"));
	m_pFire->GetComponentHub()->m_pFrameAnimation->AddImage(g_hasher("Idle"), g_hasher("Fire@5"));
	m_pFire->GetComponentHub()->m_pFrameAnimation->AddImage(g_hasher("Idle"), g_hasher("Fire@6"));
}

void GameBackground::Release()
{
	GameObject::Release();
	m_pRock->Release();
	m_pTree->Release();
	m_pHalfTree->Release();
	m_pFire->Release();

	delete m_pRock;
	delete m_pTree;
	delete m_pHalfTree;
	delete m_pFire;

	delete this;
}


int GameBackground::Start()
{
	m_pFire->GetComponentHub()->m_pFrameAnimation->SetState("Idle");

	return 0;
}


int GameBackground::Update()
{
	return 0;
}


int GameBackground::OnEvent(Event& event)
{
	return GameObject::OnEvent(event);
}


void GameBackground::ObjectSetting(GameObject*& gameobject)
{
	gameobject = new GameObject();
	gameobject->Initialize();
	gameobject->GetComponentHub()->AddComponent(ComponentHub::IMAGE);
}