#pragma once
class CircleRender : public Component
{
public:
	CircleRender();
	~CircleRender();

	virtual void Initialize(GameObject*);
	virtual void Release();

	virtual int Start();
	virtual int Update();
	virtual int OnEvent(Event&);

	// 선 또는 면의 색을 변경합니다.
	void SetColor(D2D1_COLOR_F& color);
	// 선의 굵기를 변경합니다.
	void SetStrokeWidth(float width);
	// 색이 차있는 사각형으로 설정합니다.
	void SetFill(bool isFill);
	// 그라데이션이 적용된 원으로 설정합니다.
	void SetGraident(bool);
	// 콜라이더를 사각형렌더에 맞춥니다.
	void AlignCollider();
	// transform을 기준으로 도형을 다시 그립니다.
	void Refresh();
	D2D1_COLOR_F	GetColor() const;
	float			GetWidth() const;
	float			GetHeight() const;

	static std::list<CircleRender*> list;

private:
	void MakeRadialGradientBrush(
		const D2D1_COLOR_F& centerBrushColor,
		const D2D1_COLOR_F& edgeBrushColor,
		ID2D1RadialGradientBrush*& radiaGradientBrush
		);

	Transform*					m_pTransform;
	ID2D1SolidColorBrush*		m_pBrush;
	ID2D1RadialGradientBrush*	m_pGradientBrush;
	D2D1_MATRIX_3X2_F			m_matrix;
	bool	m_isFill;
	bool	m_isGradient;
	float	m_strokeWidth;
	float	m_width;
	float	m_height;

};

