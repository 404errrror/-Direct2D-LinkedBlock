#include "stdafx.h"
#include "BackgroundParticle.h"


BackgroundParticle::BackgroundParticle()
{
	m_particleArr = nullptr;
	m_posArr = nullptr;
	m_zArr = nullptr;
	m_pCameraTarget = nullptr;
	m_amount = 0;
	m_generated = false;
}


BackgroundParticle::~BackgroundParticle()
{
}


void BackgroundParticle::Initialize()
{
	GameObject::Initialize();

	SetId("BackgroundParticle");

}


void BackgroundParticle::Release()
{
	GameObject::Release();
	for (int i = 0; i < m_amount; ++i)
		m_particleArr[i].Release();
	delete[] m_particleArr;
	delete[] m_posArr;
	delete this;
}


int BackgroundParticle::Start()
{
	return 0;
}


int BackgroundParticle::Update()
{
	if(m_pCameraTarget != nullptr)
		for (int i = 0; i < m_amount; ++i)
		{
			Vector2 temp = m_posArr[i] +
				(m_pCameraTarget->GetPosition()) * m_zArr[i];
			m_particleArr[i].GetComponentHub()->m_pTransform->SetPosition(temp);
		}
	return 0;
}


int BackgroundParticle::OnEvent(Event& event)
{
	return GameObject::OnEvent(event);
}


void BackgroundParticle::SetAmount(int num)
{
	m_amount = num;
}


void BackgroundParticle::SetCamera(Transform* cam)
{
	m_pCameraTarget = cam;
}


void BackgroundParticle::Generate()
{
	m_generated = true;

	m_particleArr = new GameObject[m_amount];
	m_posArr = new Vector2[m_amount];
	m_zArr = new float[m_amount];
	for (int i = 0; i < m_amount; ++i)
	{
		float scale = CRandom::Range(3.0, 8.0);
		m_particleArr[i].Initialize();
		m_particleArr[i].SetId("BackgroundParticleObject");
		m_particleArr[i].GetComponentHub()->AddComponent(ComponentHub::RECT_RENDER);
		m_particleArr[i].GetComponentHub()->m_pRectRender->SetColor(D2D1::ColorF(0.98, 0.98, 0.98));
		m_particleArr[i].GetComponentHub()->m_pRectRender->SetFill(true);
		m_particleArr[i].GetComponentHub()->m_pTransform->SetScale(Vector2(
			scale, scale
			));
		m_posArr[i] = Vector2(
			CRandom::Range(-5000, 5000), CRandom::Range(-5000, 5000)
			);
		m_zArr[i] = CRandom::Range(0.5, 1.0);
	}
}