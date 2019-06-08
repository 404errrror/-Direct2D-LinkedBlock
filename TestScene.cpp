#include "stdafx.h"
#include "TestScene.h"


TestScene::TestScene()
{
	m_pSolidBrush = nullptr;
}


TestScene::~TestScene()
{
}


void TestScene::Release()
{
	myCharacter->Release();
	myCharacter2->Release();
	testButton->Release();
	testRock->Release();

}


int TestScene::Start()
{
	m_isStart = true;
	GameObject::SetRenderTarget(m_pBitmapRender);
	m_pBitmapRender->CreateSolidColorBrush(D2D1::ColorF(1, 0, 0, 0.7f), &m_pSolidBrush);

	myCharacter = new TestCharacter();
	myCharacter->Initialize();

	myCharacter2 = new TestCharacter();
	myCharacter2->Initialize();

	testButton = new TestButton();
	testButton->Initialize();

	testRock = new TestRock();
	testRock->Initialize();

	// ������Ʈ Start(); Update()�� ������Ʈ ������Ʈ�ʹ� ������ �޶����.
	// ���� ������Ʈ Start()�� �� �� �������� �ؾ���. ������Ʈ �ʱ�ȭ�Ǳ� ���� �޼��带 ȣ���ϸ� �ȵǱ� ����.
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

	for (std::list<GameObject*>::iterator it = GameObject::list.begin(); it != GameObject::list.end(); ++it)
		(*it)->Start();



	myCharacter2->GetComponentHub()->m_pTransform->SetPosition(Vector2(200, 200));
	myCharacter2->GetComponentHub()->m_pRectRender->AlignCollider();
	myCharacter2->GetComponentHub()->m_pRectRender->SetColor(D2D1::ColorF(1, 1, 0));
	myCharacter2->GetComponentHub()->m_pTransform->SetScale(Vector2(0.5, 0.5));
	myCharacter2->key = 0;
	myCharacter->GetComponentHub()->m_pRigidbody->SetMass(-1);


	testRock->GetComponentHub()->m_pTransform->SetPosition(Vector2(-200, 200));


	testRock->GetComponentHub()->m_pTransform->SetParent(myCharacter->GetComponentHub()->m_pTransform);
	//myCharacter->Release();

	Camera::SetObject(myCharacter->GetComponentHub()->m_pTransform);



	return 0;
}


int TestScene::Update()
{
	Camera::CameraUpdate();

	if (g_pInput->isKeyDown('R'))
	{
		Release();
		Start();
	}

	if(!m_isStart)
		Start();
	m_pBitmapRender->BeginDraw();
	m_pBitmapRender->Clear(D2D1::ColorF(0, 0.5, 1));



	for (std::list<GameObject*>::iterator it = GameObject::list.begin(); it != GameObject::list.end(); ++it)
		(*it)->Update();

	for (std::list<BoxCollider*>::iterator it = BoxCollider::list.begin(); it != BoxCollider::list.end(); ++it)
		(*it)->Update();

	for (std::list<Rigidbody*>::iterator it = Rigidbody::list.begin(); it != Rigidbody::list.end(); ++it)
		(*it)->Update();

	for (std::list<FrameAnimation*>::iterator it = FrameAnimation::list.begin(); it != FrameAnimation::list.end(); ++it)
		(*it)->Update();

	for (std::list<Image*>::iterator it = Image::list.begin(); it != Image::list.end(); ++it)
		(*it)->Update();
	
	for (std::list<Button*>::iterator it = Button::list.begin(); it != Button::list.end(); ++it)
		(*it)->Update();

	for (std::list<RectRender*>::iterator it = RectRender::list.begin(); it != RectRender::list.end(); ++it)
		(*it)->Update();

	for (std::list<CircleRender*>::iterator it = CircleRender::list.begin(); it != CircleRender::list.end(); ++it)
		(*it)->Update();

	for (std::list<ShapeAnimation*>::iterator it = ShapeAnimation::list.begin(); it != ShapeAnimation::list.end(); ++it)
		(*it)->Update();

	
	Vector2 zeroVector(0,0);
	zeroVector = zeroVector * 0.5;
	D2D1_POINT_2F screenVector = zeroVector.GetScreenVector();
	myCharacter2->GetComponentHub()->m_pImage->Update();
	m_pBitmapRender->DrawLine(
		D2D1::Point2F(0, 0),
		D2D1::Point2F((1920 - g_windowRight) * 0.5,(1080 - g_windowTop) * 0.5),
	//	screenVector,
		m_pSolidBrush,5
		);

	DrawMouse();
	m_pBitmapRender->EndDraw();
	SwapBuffer();


	return 0;
}


int TestScene::OnEvent(Event& event)
{
	switch (event.GetType())
	{
	case Event::Type::SYSTEM_RESIZE:
	{
		if (m_isStart)
		{
			SceneClass::OnEvent(event);
			RELEASE(m_pSolidBrush);
			m_pBitmapRender->CreateSolidColorBrush(D2D1::ColorF(1, 0, 0), &m_pSolidBrush);
			return 0;
		}
	}
	default:
		return -1;
	}
}


void TestScene::DrawMouse()
{
	{
		static D2D1_POINT_2F drawPoint = { 0,0 };
		if (g_leftDown)
		{
			m_prevMousePos = drawPoint;
			drawPoint = g_mousePos;
		}

		m_pBitmapRender->DrawLine(m_prevMousePos, drawPoint, m_pSolidBrush, 1);


	}
}