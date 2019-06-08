#pragma once
#include "GameObject.h"
class ClearSelectButton :
	public GameObject
{
public:
	ClearSelectButton();
	~ClearSelectButton();

	virtual void Initialize();
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	bool IsClicked();

private:
	void AlignCollider();
	bool m_clicked;
	int m_imageWidth;
	int m_imageHeight;
};

