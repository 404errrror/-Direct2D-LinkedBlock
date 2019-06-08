#include "stdafx.h"
#include "SceneClass.h"


SceneClass::SceneClass()
{
	m_pRenderTarget = nullptr;
	m_pMaskRender = nullptr;
	m_isStart = false;
	m_isMask = false;

	m_pBitmapRender = nullptr;
	m_pMaskRender = nullptr;
	m_pUiRender = nullptr;
	m_pBitmap = nullptr;
	m_pUiBitmap = nullptr;
	m_bitmapRect = { 0,0,0,0 };

	m_pBitmapBrush = nullptr;
}


SceneClass::~SceneClass()
{
}


void SceneClass::Initialize(ID2D1HwndRenderTarget* pRenderTarget)
{
	m_pRenderTarget = pRenderTarget;
	SetBitmapRender();
}



int SceneClass::OnEvent(Event& event)
{
	switch (event.GetType())
	{
	case Event::Type::SYSTEM_RESIZE:
		Initialize((ID2D1HwndRenderTarget*)event.GetInfo());
		GameObject::SetRenderTarget(m_pBitmapRender);
		GameObject::SetMaskRender(m_pMaskRender);
		GameObject::SetUiRender(m_pUiRender);
		
		for (std::list<GameObject*>::iterator it = GameObject::list.begin(); it != GameObject::list.end(); ++it)
			(*it)->OnEvent(event);
		return 0;
	default:
		return -1;
	}
}


void SceneClass::StartComponent()
{
	// 컴포넌트 Start(); Update()의 컴포넌트 업데이트와는 순서가 달라야함.
	// 게임 오브젝트 Start()는 꼭 맨 마지막에 해야함. 컴포넌트 초기화되기 전에 메서드를 호출하면 안되기 때문.
	for (std::list<BoxCollider*>::iterator it = BoxCollider::list.begin(); it != BoxCollider::list.end(); ++it)
		(*it)->Start();

	for (std::list<Rigidbody*>::iterator it = Rigidbody::list.begin(); it != Rigidbody::list.end(); ++it)
		(*it)->Start();

	for (std::list<FrameAnimation*>::iterator it = FrameAnimation::list.begin(); it != FrameAnimation::list.end(); ++it)
		(*it)->Start();


	for (std::list<Image*>::iterator it = Image::list.begin(); it != Image::list.end(); ++it)
		(*it)->Start();

	for (std::list<Button*>::iterator it = Button::list.begin(); it != Button::list.end(); ++it)
		(*it)->Start();

	for (std::list<RectRender*>::iterator it = RectRender::list.begin(); it != RectRender::list.end(); ++it)
		(*it)->Start();

	for (std::list<CircleRender*>::iterator it = CircleRender::list.begin(); it != CircleRender::list.end(); ++it)
		(*it)->Start();

	for (std::list<ShapeAnimation*>::iterator it = ShapeAnimation::list.begin(); it != ShapeAnimation::list.end(); ++it)
		(*it)->Start();

	for (std::list<MotionAnimation*>::iterator it = MotionAnimation::list.begin(); it != MotionAnimation::list.end(); ++it)
		(*it)->Start();

	for (std::list<Text*>::iterator it = Text::list.begin(); it != Text::list.end(); ++it)
		(*it)->Start();

	for (std::list<GameObject*>::iterator it = GameObject::list.begin(); it != GameObject::list.end(); ++it)
		(*it)->Start();

}


void SceneClass::UpdateComponent()
{
	for (std::list<GameObject*>::iterator it = GameObject::list.begin(); it != GameObject::list.end(); ++it)
		(*it)->Update();

	BoxCollider::list.sort(BoxColliderSort());
	for (std::list<BoxCollider*>::iterator it = BoxCollider::list.begin(); it != BoxCollider::list.end(); ++it)
		(*it)->Update();

	for (std::list<Rigidbody*>::iterator it = Rigidbody::list.begin(); it != Rigidbody::list.end(); ++it)
		(*it)->Update();

	for (std::list<FrameAnimation*>::iterator it = FrameAnimation::list.begin(); it != FrameAnimation::list.end(); ++it)
		(*it)->Update();

	for (std::list<Button*>::iterator it = Button::list.begin(); it != Button::list.end(); ++it)
		(*it)->Update();

	// 각종 Ui를 이미지로 처리했기 때문에 RectRender, CircleRender를 이미지보다 먼저 업뎃해야함.
	for (std::list<RectRender*>::iterator it = RectRender::list.begin(); it != RectRender::list.end(); ++it)
		(*it)->Update();

	for (std::list<CircleRender*>::iterator it = CircleRender::list.begin(); it != CircleRender::list.end(); ++it)
		(*it)->Update();

	Image::list.sort(ImageSort());

	for (std::list<Image*>::iterator it = Image::list.begin(); it != Image::list.end(); ++it)
		(*it)->Update();

	for (std::list<ShapeAnimation*>::iterator it = ShapeAnimation::list.begin(); it != ShapeAnimation::list.end(); ++it)
		(*it)->Update();

	for (std::list<MotionAnimation*>::iterator it = MotionAnimation::list.begin(); it != MotionAnimation::list.end(); ++it)
		(*it)->Update();		// ----------> 위치 체크

	for (std::list<Text*>::iterator it = Text::list.begin(); it != Text::list.end(); ++it)
		(*it)->Update();


	// 지울 오브젝트를 검사한 뒤 지운다.
	// 컴포넌트 업데이트 중간에 지우면 반복자가 null이 되서 다음 리스트로 가지못하고 에러를 띄움.
	for (std::list<GameObject*>::iterator it = GameObject::list.begin(); it != GameObject::list.end();)
	{
		if ((*it)->isRelease())
		{
			GameObject* temp = *it;
			it = GameObject::list.erase(it);
			delete (temp);
			continue;
		}
		++it;
	}
}


void SceneClass::SwapBuffer()
{
	// 비트맵 가져오기
	m_pBitmapRender->GetBitmap(&m_pBitmap);
	m_pUiRender->GetBitmap(&m_pUiBitmap);
	// 어디까지 그릴건지.
	m_bitmapRect.right = m_pBitmapRender->GetSize().width * g_screenRatioInv;
	m_bitmapRect.bottom = m_pBitmapRender->GetSize().height * g_screenRatioInv;

	if (m_isMask == false)
	{

		m_pRenderTarget->BeginDraw();
		m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
		m_pRenderTarget->DrawBitmap(
			m_pBitmap,
			m_bitmapRect
			);
		m_pRenderTarget->DrawBitmap(
			m_pUiBitmap,
			m_bitmapRect
			);

		m_pRenderTarget->EndDraw();
	}
	else
	{
		// 마스크 비트맵 생성
		m_pMaskRender->GetBitmap(&m_pMaskBitmap);
		// 비트맵 브러쉬 생성
		m_pRenderTarget->CreateBitmapBrush(m_pBitmap, &m_pBitmapBrush);
		// test
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(
			D2D1::SizeF(1, 1),
			D2D1::Point2F(0, 0))
			);
		////
		m_pRenderTarget->BeginDraw();

		if (SceneManager::GetScene() == SceneManager::SCENE_GAME)
			m_pRenderTarget->Clear(D2D1::ColorF(0.07, 0.067, 0.14));
		else
			m_pRenderTarget->Clear(D2D1::ColorF(0.3, 0.3, 0.3));

		//클리핑 적용.
		m_pRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
		m_pRenderTarget->FillOpacityMask(
			m_pMaskBitmap,
			m_pBitmapBrush,
			D2D1_OPACITY_MASK_CONTENT_GRAPHICS
			);
		m_pRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

		// UI 그리기전에 화면 비율 맞춰주기.
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(
			D2D1::SizeF(g_screenRatio, g_screenRatio),
			D2D1::Point2F(0, 0))
			);

		// UI 그리기
		m_pRenderTarget->DrawBitmap(
			m_pUiBitmap,
			m_bitmapRect
			);

		m_pRenderTarget->EndDraw();

	}

	//RELEASE(m_pBitmap);		-----------> 왜 메모리 누수가 안날까, 메모리 테스트 해보기.
}


void SceneClass::SetBitmapRender()
{
	RELEASE(m_pBitmapRender);
	RELEASE(m_pMaskRender);
	RELEASE(m_pUiRender);

	m_pRenderTarget->CreateCompatibleRenderTarget(&m_pBitmapRender);
	m_pRenderTarget->CreateCompatibleRenderTarget(&m_pMaskRender);
	m_pRenderTarget->CreateCompatibleRenderTarget(&m_pUiRender);

	// 좌표를 맞춤. 안맞추면 마우스 포인트가 안맞아짐.
	m_pBitmapRender->SetTransform(
		D2D1::Matrix3x2F::Scale(
			D2D1::SizeF(g_screenRatio, g_screenRatio),
			D2D1::Point2F(0, 0)
			)
		);
	m_pMaskRender->SetTransform(
		D2D1::Matrix3x2F::Scale(
			D2D1::SizeF(g_screenRatio, g_screenRatio),
			D2D1::Point2F(0, 0)
			)
		);
	m_pUiRender->SetTransform(
		D2D1::Matrix3x2F::Scale(
			D2D1::SizeF(g_screenRatio / g_screenMag, g_screenRatio / g_screenMag),
			D2D1::Point2F(0, 0)
			)
		);

}