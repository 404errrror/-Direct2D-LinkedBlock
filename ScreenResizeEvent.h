#pragma once
#include "Event.h"
class ScreenResizeEvent : public Event
{
public:
	ScreenResizeEvent();
	ScreenResizeEvent(ID2D1HwndRenderTarget*&);
	ScreenResizeEvent(ID2D1BitmapRenderTarget*&);
	~ScreenResizeEvent();

	void* GetInfo();
private:
	ID2D1HwndRenderTarget* m_pHwndRender;
	ID2D1BitmapRenderTarget* m_pBitmapRender;
};

