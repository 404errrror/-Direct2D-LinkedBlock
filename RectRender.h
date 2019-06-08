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

	// trnasform.SetScale �� ���������ؼ� ���������.
	//void SetWidth		(float width);
	//void SetHeight		(float height);

	// �� �Ǵ� ���� ���� �����մϴ�.
	void SetColor		(D2D1_COLOR_F& color);
	// ���� ���⸦ �����մϴ�.
	void SetStrokeWidth	(float width);
	// ���� ���ִ� �簢������ �����մϴ�.
	void SetFill		(bool isFill);
	// �ݶ��̴��� �簢�������� ����ϴ�.
	void AlignCollider	();
	// transform�� �������� ������ �ٽ� �׸��ϴ�.

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