#pragma once
class RectRender : public Component
{
public:
	RectRender();
	~RectRender();

	virtual void Initialize(GameObject*);
	virtual void Release();


	virtual int Start	();
	virtual int Update	();
	virtual int OnEvent	(Event&);

	// trnasform.SetScale 로 조절가능해서 쓸모없을듯.
	//void SetWidth		(float width);
	//void SetHeight		(float height);

	// 선 또는 면의 색을 변경합니다.
	void SetColor		(D2D1_COLOR_F& color);
	// 선의 굵기를 변경합니다.
	void SetStrokeWidth	(float width);
	// 색이 차있는 사각형으로 설정합니다.
	void SetFill		(bool isFill);
	// 콜라이더를 사각형렌더에 맞춥니다.
	void AlignCollider	();
	// transform을 기준으로 도형을 다시 그립니다.

	void Refresh();
	float GetWidth();
	float GetHeight();
	D2D1_COLOR_F GetColor();

	static std::list<RectRender*> list;
private:
	Transform* m_pTransform;
	ID2D1SolidColorBrush* m_pBrush;
	D2D1_MATRIX_3X2_F m_matrix;
	bool m_isFill;
	float m_strokeWidth;
	float m_width;
	float m_height;
};