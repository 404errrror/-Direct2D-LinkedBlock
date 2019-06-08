#pragma once
#include "Component.h"
class Text :
	public Component
{
public:
	Text();
	~Text();

	virtual void Initialize(GameObject*);
	virtual void Release();

	virtual int Start	();
	virtual int Update	();
	virtual int OnEvent	(Event&);
	void Debug();

	void SetText			(const char*);
	void SetTextSize		(float);
	void SetWidth			(float);
	void SetHeight			(float);
	void SetColor			(D2D1_COLOR_F);
	void SetOpacity			(float);
	void SetTextAlignment	(DWRITE_TEXT_ALIGNMENT);

	D2D1_COLOR_F	GetColor	() const;
	float			GetOpacity	() const;

	static std::list<Text*> list;
	static IDWriteFactory*	pTextFactory;
private:
	Transform*			m_pTransform;

	IDWriteTextFormat*	m_pTextFormat;
	IDWriteTextLayout*	m_pTextLayout;
	ID2D1SolidColorBrush* m_pColorBrush;

	CString		m_pText;
	float		m_textSize;
	float		m_layoutWidth;
	float		m_layoutHeight;
};

