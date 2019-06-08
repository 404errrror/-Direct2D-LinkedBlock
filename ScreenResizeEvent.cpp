#include "stdafx.h"
#include "ScreenResizeEvent.h"


ScreenResizeEvent::ScreenResizeEvent()
{
	m_pHwndRender = nullptr;
	m_pBitmapRender = nullptr;

	m_type = Type::SYSTEM_RESIZE;
}


ScreenResizeEvent::ScreenResizeEvent(ID2D1HwndRenderTarget*& pHwndRender)
{
	m_pHwndRender = nullptr;
	m_pBitmapRender = nullptr;

	m_type = Type::SYSTEM_RESIZE;
	m_pHwndRender = pHwndRender;
}

ScreenResizeEvent::ScreenResizeEvent(ID2D1BitmapRenderTarget*& pBitmapRender)
{
	m_pHwndRender = nullptr;
	m_pBitmapRender = nullptr;

	m_type = Type::SYSTEM_RESIZE;
	m_pBitmapRender = pBitmapRender;
}


ScreenResizeEvent::~ScreenResizeEvent()
{
}

void* ScreenResizeEvent::GetInfo()
{
	if (m_pBitmapRender == nullptr)
		return m_pHwndRender;
	else if (m_pHwndRender == nullptr)
		return m_pBitmapRender;
	else
		return nullptr;
}