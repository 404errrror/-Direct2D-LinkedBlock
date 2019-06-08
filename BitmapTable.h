#pragma once
#include <map>
// 전역 클래스입니다. 객체를 생성할 필요 없습니다.
class BitmapTable
{
public:
	BitmapTable();
	~BitmapTable();

	static void Initialize(ID2D1HwndRenderTarget*&);
	static void Release();

	// 비트맵 이미지를 하드디스크로부터 불러오고, 그 이미지의 고유ID를 설정합니다.
	static int LoadImageFile(LPCWSTR filePath, std::string imageId);
	// 비트맵이미지를 가져옵니다.
	static ID2D1Bitmap* GetBitmap(const size_t& imageId);

private:

	static IWICImagingFactory				*m_pWicFactory;
	static std::map<size_t, ID2D1Bitmap*>	list;
	static ID2D1HwndRenderTarget			*m_pRenderTarget;
};

