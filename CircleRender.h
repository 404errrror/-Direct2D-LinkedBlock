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

	// �� �Ǵ� ���� ���� �����մϴ�.
	void SetColor(D2D1_COLOR_F& color);
	// ���� ���⸦ �����մϴ�.
	void SetStrokeWidth(float width);
	// ���� ���ִ� �簢������ �����մϴ�.
	void SetFill(bool isFill);
	// �׶��̼��� ����� ������ �����մϴ�.
	void SetGraident(bool);
	// �ݶ��̴��� �簢�������� ����ϴ�.
	void AlignCollider();
	// transform�� �������� ������ �ٽ� �׸��ϴ�.
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

