#include "stdafx.h"
#include "ExplosionEffect.h"


ExplosionEffect::ExplosionEffect()
{
	_CrtDumpMemoryLeaks();
	particleList.clear();
	directArr = nullptr;
	m_amount = 0;
	m_speed = 1;
	m_active = false;
}


ExplosionEffect::~ExplosionEffect()
{
}


void ExplosionEffect::Initialize()
{
	GameObject::Initialize();
	SetId("ExplosionEffect");
}


void ExplosionEffect::Release()
{
	GameObject::Release();

	for (std::list<GameObject*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
	{
		(*it)->Release();
		delete (*it);
	}
	particleList.clear();

	delete[] directArr;
	delete this;
}


int ExplosionEffect::Start()
{
	
	return 0;
}


int ExplosionEffect::Update()
{
	if (m_active == false)
		return 0;

	int index = 0;
	for (std::list<GameObject*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
	{
		(*it)->GetComponentHub()->m_pTransform->Translate(directArr[index] * m_speed);
		index++;
	}

	return 0;
}


void ExplosionEffect::SetParent(Transform* parent)
{
	m_pComponentHub->m_pTransform->SetParent(parent);
}


void ExplosionEffect::SetAmount(int amount)
{
	m_amount = amount;
	
	//// --------------> 중복해서 set할 것을 대비해서 반복자로 리스트 지우기.
	//// --------------> 나중에 list가아니라 동적arr로 바꾸기
	for (int i = 0; i < m_amount; ++i)
	{
		particleList.push_back(new GameObject());
		particleList.back()->Initialize();
		particleList.back()->SetId("ExplosionEffectChild");
		particleList.back()->GetComponentHub()->m_pTransform->SetScale(Vector2(0.1, 0.1));
		particleList.back()->GetComponentHub()->m_pTransform->SetParent(m_pComponentHub->m_pTransform);
		particleList.back()->GetComponentHub()->AddComponent(ComponentHub::RECT_RENDER);
		particleList.back()->GetComponentHub()->m_pRectRender->SetFill(true);
		particleList.back()->GetComponentHub()->m_pRectRender->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
		particleList.back()->GetComponentHub()->m_pGameObject->SetActive(false);
	}
	directArr = new Vector2[m_amount];
	for (int i = 0; i < m_amount; ++i)
	{
		directArr[i].x = CRandom::Range(-1.0, 1.0);
		directArr[i].y = CRandom::Range(-1.0, 1.0);
	}
}


void ExplosionEffect::SetSpeed(float speed)
{
	m_speed = speed;
}


void ExplosionEffect::SetColor(D2D1_COLOR_F& color)
{
	for (std::list<GameObject*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
	{
		(*it)->GetComponentHub()->m_pRectRender->SetColor(color);
	}
}


void ExplosionEffect::Play()
{

	m_active = true;
	for (std::list<GameObject*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
	{
		(*it)->GetComponentHub()->m_pGameObject->SetActive(true);
	}

}


void ExplosionEffect::Stop()
{
	m_active = false;
	for (std::list<GameObject*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
	{
		(*it)->GetComponentHub()->m_pGameObject->SetActive(false);
	}
}