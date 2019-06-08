#include "stdafx.h"
#include "Image.h"
#include "D2DClass.h"

std::list<Image*> Image::list;

Image::Image()
{
	list.push_back(this);

	m_pWicFactory = nullptr;
	m_pBitmap = nullptr;

	m_enable = true;
	m_depth = 0;
	m_bottom = 0;
	m_opacity = 1;
	m_imageSizeRect = { 0,0,0,0 };
	m_imageScreenPos = { 0, 0, 0, 0 };
	m_pivot = { 0.5, 0.5 };
	m_imageId = 0;
	m_matrix = { 1, 0, 0, 1, 0, 0 };
}


Image::~Image()
{
}


void Image::Initialize(GameObject* gameObject)
{
	Component::Initialize(gameObject);
	HRESULT hr;
	
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL, 
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&m_pWicFactory)
		);
	if(FAILED(hr))
	{
		MessageBox(
			g_hwnd,
			L"Image::Initialize()\nWicFactory 생성에 실패했습니다.",
			L"CoCreateInstance()",
			MB_ICONERROR
			);
	}
	//	----------------------------> 나중에 D2DClass로 이동시키면 될듯.

	m_pTransform = m_pGameObject->GetComponentHub()->m_pTransform;
	Start();
}


void Image::Release()
{
	Component::Release();
	for (std::list<Image*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		if ((*it) == this)
		{
			list.erase(it);
			break;
		}
	}

	delete this;
}


int Image::Start()
{
	//ImageRectRefresh();

	if (m_pBitmap != nullptr)
		m_bottom = -m_pBitmap->GetSize().height * 0.5;
	return 0;
}


int Image::Update()
{
	if (m_enable == false || m_pGameObject->isActive() == false)
		return 0;

	ID2D1Bitmap* tempBitmap;
	ImageRectRefresh();					// ------------> 행렬로 이동, 회전 하면서 필요 없어졌지만, 나중에 Pivot을 만들때 필요할 수도 있음.
//	RefreshBitmapBrush();				/////////////////// ------------> WindowResize때문에. 나중에 수정하기.
	D2D1_MATRIX_3X2_F brushMatrix = m_pTransform->GetMatrix(m_imageSizeRect.right, m_imageSizeRect.bottom);
	brushMatrix = brushMatrix *
		D2D1::Matrix3x2F::Translation(D2D1::SizeF(-Camera::GetCameraPos().x, Camera::GetCameraPos().y));
		
	m_pBitmapBrush->SetTransform(brushMatrix);

	if (m_pGameObject->IsUi())	// 현재 오브젝트가 Ui라면.
	{
		m_pGameObject->GetUiRenderTarget()->FillRectangle(
			D2D1::RectF(
				0,
				// Ui는 배율이 작아져도 화면 출력마스크의 크기가 그대로여야함.
				MAX_SCREEN_HEIGHT * (g_screenHeightRatio / g_screenRatio) * g_screenMag,
				MAX_SCREEN_WIDTH * (g_screenWidthRatio / g_screenRatio)* g_screenMag,
				0
				),
			//	m_imageScreenPos,
			m_pBitmapBrush
			);
	}

	else						// 일반적인 상황.
	{
		// 클리핑 마스크 개념임. 회전 때문에 그냥 화면 전체로 설정해놓음. 겁나 커도 딱히 성능차이 없는듯.
		m_pGameObject->GetRenderTarget()->FillRectangle(
			D2D1::RectF(
				0,
				MAX_SCREEN_HEIGHT * (g_screenHeightRatio / g_screenRatio),
				MAX_SCREEN_WIDTH * (g_screenWidthRatio / g_screenRatio),
				0
				),
			//	m_imageScreenPos,
			m_pBitmapBrush
			);
	}

	if (g_debugMode)
		Debug();

	// 깊이 설정
	m_depth = m_pTransform->GetPosition().y + m_bottom;

	return 0;
}


int Image::OnEvent(Event& event)
{
	switch (event.GetType())
	{
	case Event::Type::SYSTEM_RESIZE:
		RefreshBitmapBrush();
		return 0;

	case Event::Type::GAMEOBJECT_TRANSFORM_CHANGE:
		ImageRectRefresh();
		return 0;
	default:
		return -1;
	}
}


void Image::Debug()
{
	ID2D1BitmapRenderTarget* bitmapRender = GameObject::GetRenderTarget();
	D2D1_POINT_2F screenVector = m_pTransform->GetScreenPosition();
	Camera::Apply(screenVector);

	//bitmapRender->DrawRectangle(
	//	D2D1::RectF(
	//		screenVector.x - m_imageSizeRect.right,
	//		screenVector.y - m_imageSizeRect.bottom,
	//		screenVector.x + m_imageSizeRect.right,
	//		screenVector.y + m_imageSizeRect.bottom),
	//	D2DClass::GetSolidBrush(D2D1::ColorF(0, 0, 1))
	//	);

	bitmapRender->DrawLine(
		D2D1::Point2(screenVector.x - 10, screenVector.y - m_bottom),
		D2D1::Point2(screenVector.x + 10, screenVector.y - m_bottom),
		D2DClass::GetSolidBrush(D2D1::ColorF(1, 0, 0))
		);
}




int Image::SetImage(const size_t& imageId)
{

	if (BitmapTable::GetBitmap(imageId) == nullptr)
	{
		CString errorLog = "Object Name : ";
		errorLog += m_pGameObject->GetName().c_str();
		MessageBox(g_hwnd,
			L"Image::SetImage\n잘못된 이미지를 이미지 컴포넌트에 추가하였습니다..",
			errorLog,
			MB_ICONERROR);
	}

	m_imageId = imageId;
	m_pBitmap = BitmapTable::GetBitmap(imageId);

	//-----------------------> 나중에 pivot 설정하기.
	m_imageSizeRect.right = m_pBitmap->GetSize().width;
	m_imageSizeRect.bottom = m_pBitmap->GetSize().height;

	//////////////////////////////
	///// BitmapBrush로 수정
	/////////////////////////////
	RefreshBitmapBrush();

	return 0;
}


void Image::SetOpacity(float opacity)
{
	m_opacity = opacity;
	if (m_pBitmapBrush)
		m_pBitmapBrush->SetOpacity(m_opacity);
}


void Image::SetBottom(float bottom)
{
	m_bottom = bottom;
}


void Image::RefreshBitmapBrush()
{
	RELEASE(m_pBitmapBrush);
	GameObject::GetRenderTarget()->CreateBitmapBrush(BitmapTable::GetBitmap(m_imageId), &m_pBitmapBrush);
	m_pBitmapBrush->SetOpacity(m_opacity);
}


void Image::ImageRectRefresh()
{
	D2D1_POINT_2F m_gameobjectPos = m_pTransform->GetScreenPosition();
	Vector2 m_gameobjectScale = m_pTransform->GetScale();

	m_pBitmap = BitmapTable::GetBitmap(m_imageId);

	m_imageScreenPos = D2D1::RectF(
		m_gameobjectPos.x - m_imageSizeRect.right * 0.5 * m_gameobjectScale.x,
		m_gameobjectPos.y - m_imageSizeRect.bottom * 0.5 * m_gameobjectScale.y,
		m_gameobjectPos.x + m_imageSizeRect.right * 0.5 * m_gameobjectScale.x,
		m_gameobjectPos.y + m_imageSizeRect.bottom * 0.5 * m_gameobjectScale.y
		);

	// Pivot Setting
	m_imageScreenPos = D2D1::RectF(
		m_imageScreenPos.left + (m_pBitmap->GetSize().width * (0.5 - m_pivot.x)),
		m_imageScreenPos.top + (m_pBitmap->GetSize().height * (0.5 - m_pivot.y)),
		m_imageScreenPos.left + m_pBitmap->GetSize().width,
		m_imageScreenPos.top + m_pBitmap->GetSize().height
		);
}

size_t Image::GetImageId() const
{
	return m_imageId;
}


int Image::GetImageWidth() const
{
	return m_pBitmap->GetSize().width;
}


int Image::GetImageHeight() const
{
	return m_pBitmap->GetSize().height;
}


float Image::GetOpacity() const
{
	if (m_pBitmapBrush)
		return m_pBitmapBrush->GetOpacity();
	else
		return -1;
}


float Image::GetDepth() const
{
	return m_depth;
}