#pragma once
#include <map>
// ���� Ŭ�����Դϴ�. ��ü�� ������ �ʿ� �����ϴ�.
class BitmapTable
{
public:
	BitmapTable();
	~BitmapTable();

	static void Initialize(ID2D1HwndRenderTarget*&);
	static void Release();

	// ��Ʈ�� �̹����� �ϵ��ũ�κ��� �ҷ�����, �� �̹����� ����ID�� �����մϴ�.
	static int LoadImageFile(LPCWSTR filePath, std::string imageId);
	// ��Ʈ���̹����� �����ɴϴ�.
	static ID2D1Bitmap* GetBitmap(const size_t& imageId);

private:

	static IWICImagingFactory				*m_pWicFactory;
	static std::map<size_t, ID2D1Bitmap*>	list;
	static ID2D1HwndRenderTarget			*m_pRenderTarget;
};

