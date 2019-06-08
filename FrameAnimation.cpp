#include "stdafx.h"
#include "FrameAnimation.h"

std::list<FrameAnimation*> FrameAnimation::list;

FrameAnimation::FrameAnimation()
{
	list.push_back(this);

	m_pImageComponent = nullptr;
	m_animationData.clear();
	m_state = 0;
	m_delay = 0.1f;
	m_time = 0;
	m_replay = true;
	m_end = false;
}


FrameAnimation::~FrameAnimation()
{
}


void FrameAnimation::Initialize(GameObject* gameobject)
{
	Component::Initialize(gameobject);
	m_pImageComponent = m_pGameObject->GetComponentHub()->m_pImage;
	if (m_pImageComponent == nullptr)
		MessageBox(
		g_hwnd,
		L"FrameAnimation::Initialize\n지정한 객체에 이미지 컴포넌트가 존재하지 않습니다.",
		L" m_pGameObject->GetComponentHub()->m_pImage",
		MB_ICONERROR
		);
}

void FrameAnimation::Release()
{
	m_animationData.clear();
	for (std::list<FrameAnimation*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if (*it == this)
		{
			list.erase(it);
			break;
		}
	}
	delete this;
}

int FrameAnimation::Start()
{
	return 0;
}


int FrameAnimation::Update()
{
	if (m_end && m_replay == false)
		return 0;
	if (m_enable && !m_animationData.empty())
	{
		if (m_pGameObject->GetComponentHub()->m_pImage)
		{
			if (m_state == 0)
				MessageBox(g_hwnd, L"FrameAnimation::Update()\n 애니메이션 상태 설정안함", L"m_state", MB_ICONERROR);
			
			m_time += Time::GetDeltaTime();
			if (m_time >= m_delay)
			{
				m_time = 0;
				m_pGameObject->GetComponentHub()->m_pImage->SetImage(*m_iterator);
				++m_iterator;
				if (m_iterator == m_animationData[m_state].end() )
				{
					if(m_replay)
						m_iterator = m_animationData[m_state].begin();
					else
						Stop();
				}
				return 0;
			}
		}
	}
	
	return -1;
}


int FrameAnimation::OnEvent(Event& event)
{
	return -1;
}


void FrameAnimation::AddImage(size_t animationState, size_t animationImageId)
{
	m_animationData[animationState].push_back(animationImageId);
	if (BitmapTable::GetBitmap(animationImageId) == nullptr)
	{
		CString errorLog = "Object Name : ";
		errorLog += m_pGameObject->GetName().c_str();
		MessageBox(g_hwnd,
			L"FrameAnimation::AddImage\n잘못된 이미지를 애니메이션에 추가하였습니다.",
			errorLog,
			MB_ICONERROR);
	}
}


void FrameAnimation::SetState(size_t animationState)
{
	m_state = animationState;
	m_iterator = m_animationData[m_state].begin();
}


void FrameAnimation::SetState(std::string animationState)
{
	m_state = g_hasher(animationState);
	m_iterator = m_animationData[m_state].begin();
}



void FrameAnimation::SetReplay(bool replay)
{
	m_replay = replay;
}


bool FrameAnimation::isPlay()const
{
	return !m_end;
}


void FrameAnimation::Play()
{
	m_end = false;
	m_iterator = m_animationData[m_state].begin();
}


void FrameAnimation::Stop()
{
	m_end = true;
}


size_t FrameAnimation::GetState() const
{
	return m_state;
}