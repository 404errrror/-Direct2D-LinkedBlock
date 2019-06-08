#pragma once
#include "Component.h"

class Transform;
class Image : public Component
{
public:
	Image();
	~Image();

	void Initialize	(GameObject*);
	void Release	();

	virtual int Start	();
	virtual int Update	();
	virtual int OnEvent	(Event&);
	void Debug();



	int			SetImage			(const size_t& imageId);
	void		SetOpacity			(float);
	// �ٴ��� �����մϴ�. �� ���� �׸��� ������ �������� ������ �ݴϴ�.
	void		SetBottom			(float);
	// Transform ������Ʈ�� ũ�⳪ ��ġ�� ����ɶ� ȣ���.
	void		RefreshBitmapBrush	();
	void		ImageRectRefresh	();

	size_t		GetImageId() const;
	int			GetImageWidth() const;
	int			GetImageHeight() const;
	float		GetOpacity() const;
	float		GetDepth() const;

	static std::list<Image*> list;
private:
	IWICImagingFactory *m_pWicFactory;
	ID2D1Bitmap *m_pBitmap;
	ID2D1BitmapBrush *m_pBitmapBrush;
	Transform* m_pTransform;

	bool m_enable;
	float m_depth;
	float m_bottom;
	float m_opacity;
	D2D1_RECT_F m_imageSizeRect;
	D2D1_RECT_F m_imageScreenPos;
	D2D1_POINT_2F m_pivot;
	size_t		m_imageId;
	D2D1_MATRIX_3X2_F m_matrix;

};

class ImageSort
{
public:
	// ���� ����.
	bool operator()(const Image* a, const Image* b)const
	{
		return a->GetDepth() >  b->GetDepth();
	}
};