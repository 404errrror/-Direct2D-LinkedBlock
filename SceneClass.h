#pragma once
#include "InputClass.h"
class SceneClass
{
public:
	SceneClass();
	~SceneClass();

	void Initialize(ID2D1HwndRenderTarget* );
	virtual void	Release			() = 0;
	virtual int		Start			() = 0;
	virtual int		Update			() = 0;
	virtual int		OnEvent			(Event&);

protected:
	void		StartComponent	();
	void		UpdateComponent	();
	void		SwapBuffer		();
	void		SetBitmapRender	();

	ID2D1BitmapRenderTarget*	m_pBitmapRender;
	ID2D1BitmapRenderTarget*	m_pMaskRender;
	// Ui를 그리는 타겟. 이 비트맵타겟은 마스크에 영향을 받지 않음.
	ID2D1BitmapRenderTarget*	m_pUiRender;
	bool m_isStart;
	bool m_isMask;

private:
	ID2D1HwndRenderTarget*		m_pRenderTarget;
	ID2D1Bitmap*				m_pBitmap;
	D2D1_RECT_F					m_bitmapRect;

	// Clipping Mask 관련
	ID2D1BitmapBrush*			m_pBitmapBrush;
	ID2D1Bitmap*				m_pMaskBitmap;

	// Ui관련.
	ID2D1Bitmap*				m_pUiBitmap;

};

