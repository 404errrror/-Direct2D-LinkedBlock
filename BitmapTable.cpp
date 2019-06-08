#include "stdafx.h"
#include "BitmapTable.h"

// 정적변수 초기화.
IWICImagingFactory*				BitmapTable::m_pWicFactory;
std::map<size_t, ID2D1Bitmap*>	BitmapTable::list;
ID2D1HwndRenderTarget*			BitmapTable::m_pRenderTarget;

BitmapTable::BitmapTable()
{
	m_pWicFactory = nullptr;
	list.clear();
}


BitmapTable::~BitmapTable()
{
	RELEASE(m_pWicFactory);
	list.clear();
}

void BitmapTable::Initialize(ID2D1HwndRenderTarget*& hwndRenderTarget)
{
	static HRESULT hr;
	m_pRenderTarget = hwndRenderTarget;

	if(m_pWicFactory == nullptr)
		hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&m_pWicFactory)
		);

	if (FAILED(hr))
	{
		MessageBox(
			g_hwnd,
			L"Image::Initialize()\nWicFactory 생성에 실패했습니다.",
			L"CoCreateInstance()",
			MB_ICONERROR
			);
	}

	//////////////// Image Loading /////////////////////
	LoadImageFile((L"test\\CharacterBase@0.png"), "MyCharacterImgIdle0");
	LoadImageFile((L"test\\CharacterBase@1.png"), "MyCharacterImgIdle1");
	LoadImageFile((L"test\\CharacterBase_Run@0.png"), "MyCharacterImgRun0");
	LoadImageFile((L"test\\CharacterBase_Run@1.png"), "MyCharacterImgRun1");
	LoadImageFile((L"test\\CharacterBase_Run@2.png"), "MyCharacterImgRun2");
	LoadImageFile((L"test\\CharacterBase_Run@3.png"), "MyCharacterImgRun3");
	LoadImageFile((L"test\\CharacterBase_Run@4.png"), "MyCharacterImgRun4");
	LoadImageFile((L"test\\CharacterBase_Run@5.png"), "MyCharacterImgRun5");
	LoadImageFile((L"test\\CharacterBase_Run@6.png"), "MyCharacterImgRun6");
	LoadImageFile((L"test\\CharacterBase_Run@7.png"), "MyCharacterImgRun7");
	LoadImageFile((L"test\\TestRock.png"),		"TestRockImg");
	LoadImageFile((L"test\\StartBtn.png"),		"StartBtnImg");
	LoadImageFile((L"test\\StartBtnFocus.png"), "StartBtnFocusImg");
	LoadImageFile((L"test\\StartBtnDown.png"),	"StartBtnDownImg");

	LoadImageFile((L"GameResources\\TitleImage.png"),		"TitleImg");
	LoadImageFile((L"GameResources\\StartBtn_Idle.png"),	"StartBtnImg_Idle");
	LoadImageFile((L"GameResources\\StartBtn_Focus.png"),	"StartBtnImg_Focus");
	LoadImageFile((L"GameResources\\StartBtn_Press.png"),	"StartBtnImg_Press");
	LoadImageFile((L"GameResources\\SelectStage.png"),		"SelectStageImg");
	LoadImageFile((L"GameResources\\Stage1Btn_Idle.png"),	"Stage1Btn_Idle");
	LoadImageFile((L"GameResources\\Stage1Btn_Focus.png"),	"Stage1Btn_Focus");
	LoadImageFile((L"GameResources\\Stage1Btn_Press.png"),	"Stage1Btn_Press");
	LoadImageFile((L"GameResources\\Stage2Btn_Idle.png"),	"Stage2Btn_Idle");
	LoadImageFile((L"GameResources\\Stage2Btn_Focus.png"),	"Stage2Btn_Focus");
	LoadImageFile((L"GameResources\\Stage2Btn_Press.png"),	"Stage2Btn_Press");
	LoadImageFile((L"GameResources\\Stage3Btn_Idle.png"),	"Stage3Btn_Idle");
	LoadImageFile((L"GameResources\\Stage3Btn_Focus.png"),	"Stage3Btn_Focus");
	LoadImageFile((L"GameResources\\Stage3Btn_Press.png"),	"Stage3Btn_Press");
	LoadImageFile((L"GameResources\\Stage4Btn_Idle.png"),	"Stage4Btn_Idle");
	LoadImageFile((L"GameResources\\Stage4Btn_Focus.png"),	"Stage4Btn_Focus");
	LoadImageFile((L"GameResources\\Stage4Btn_Press.png"),	"Stage4Btn_Press");
	LoadImageFile((L"GameResources\\Stage5Btn_Idle.png"),	"Stage5Btn_Idle");
	LoadImageFile((L"GameResources\\Stage5Btn_Focus.png"),	"Stage5Btn_Focus");
	LoadImageFile((L"GameResources\\Stage5Btn_Press.png"),	"Stage5Btn_Press");
	LoadImageFile((L"GameResources\\Stage6Btn_Idle.png"),	"Stage6Btn_Idle");
	LoadImageFile((L"GameResources\\Stage6Btn_Focus.png"),	"Stage6Btn_Focus");
	LoadImageFile((L"GameResources\\Stage6Btn_Press.png"),	"Stage6Btn_Press");
	LoadImageFile((L"GameResources\\StageClearImage.png"),	"StageClear");
	LoadImageFile((L"GameResources\\Clear_SelectStageBtn_Idle.png"),	"Clear_SelectBtn_Idle");
	LoadImageFile((L"GameResources\\Clear_SelectStageBtn_Focus.png"),	"Clear_SelectBtn_Focus");
	LoadImageFile((L"GameResources\\Clear_SelectStageBtn_Press.png"),	"Clear_SelectBtn_Press");

	LoadImageFile((L"GameResources\\2\\Rock.png"),				"Rock");
	LoadImageFile((L"GameResources\\2\\Tree.png"),				"Tree");
	LoadImageFile((L"GameResources\\2\\HalfTree.png"),			"HalfTree");
	LoadImageFile((L"GameResources\\2\\FireWood.png"),			"FireWood");
	LoadImageFile((L"GameResources\\2\\ShootPoint_Default.png"),"ShootPoint_Default");
	LoadImageFile((L"GameResources\\2\\BulletCount.png"), "BulletCount");
	LoadImageFile((L"GameResources\\2\\Slime.png"), "Slime");
	LoadImageFile((L"GameResources\\2\\Slime_Move@1.png"), "Slime_Move@1");
	LoadImageFile((L"GameResources\\2\\Slime_Move@2.png"), "Slime_Move@2");
	LoadImageFile((L"GameResources\\2\\Slime_Move@3.png"), "Slime_Move@3");
	LoadImageFile((L"GameResources\\2\\Slime_Move@4.png"), "Slime_Move@4");
	LoadImageFile((L"GameResources\\2\\Slime_Move@5.png"), "Slime_Move@5");
	LoadImageFile((L"GameResources\\2\\Slime_Move@6.png"), "Slime_Move@6");
	LoadImageFile((L"GameResources\\2\\Slime_Attack@1.png"), "Slime_Attack@1");
	LoadImageFile((L"GameResources\\2\\Slime_Attack@2.png"), "Slime_Attack@2");
	LoadImageFile((L"GameResources\\2\\Slime_Attack@3.png"), "Slime_Attack@3");
	LoadImageFile((L"GameResources\\2\\Slime_Attack@4.png"), "Slime_Attack@4");
	LoadImageFile((L"GameResources\\2\\Slime_Attack@5.png"), "Slime_Attack@5");
	LoadImageFile((L"GameResources\\2\\Slime_Attack@6.png"), "Slime_Attack@6");
	LoadImageFile((L"GameResources\\2\\Slime_Hitted@1.png"), "Slime_Hitted@1");
	LoadImageFile((L"GameResources\\2\\Slime_Die@1.png"), "Slime_Die@1");
	LoadImageFile((L"GameResources\\2\\Character.png"), "Character");
	LoadImageFile((L"GameResources\\2\\Fire@1.png"), "Fire@1");
	LoadImageFile((L"GameResources\\2\\Fire@2.png"), "Fire@2");
	LoadImageFile((L"GameResources\\2\\Fire@3.png"), "Fire@3");
	LoadImageFile((L"GameResources\\2\\Fire@4.png"), "Fire@4");
	LoadImageFile((L"GameResources\\2\\Fire@5.png"), "Fire@5");
	LoadImageFile((L"GameResources\\2\\Fire@6.png"), "Fire@6");
	LoadImageFile((L"GameResources\\2\\RestartBtn_Idle.png"), "RestartBtn_Idle");
	LoadImageFile((L"GameResources\\2\\RestartBtn_Focus.png"), "RestartBtn_Focus");
	LoadImageFile((L"GameResources\\2\\RestartBtn_Press.png"), "RestartBtn_Press");


}


void BitmapTable::Release()
{
	for (std::map<size_t, ID2D1Bitmap*>::iterator it = list.begin(); it != list.end(); ++it)
	{
		it->second->Release();
		it->second = nullptr;
	}
	list.clear();
}


int BitmapTable::LoadImageFile(LPCWSTR filePath, std::string imageId)
{
	HRESULT hr;

	IWICBitmapDecoder *pImageDecoder = nullptr;
	IWICBitmapFrameDecode *pFrameDecoder = nullptr;
	IWICFormatConverter *pFormatConverter = nullptr;
	ID2D1Bitmap *pBitmap;

	////////// ----------- 메모리 누수
	hr = m_pWicFactory->CreateDecoderFromFilename(
		filePath,
		NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&pImageDecoder
		);
	//////////   -----------> 메모리 누수

	if (FAILED(hr))
	{
		CString errorLog = L"BitmapTable::LoadImageFile()\nImageDecoder를 생성하지 못했습니다.\n";
		errorLog += filePath;
		MessageBox(
			g_hwnd,
			errorLog,
			L"CreateDecoderFromFilename()",
			MB_ICONERROR);
		return -1;
	}

	hr = pImageDecoder->GetFrame(0, &pFrameDecoder);
	if (FAILED(hr))
	{
		MessageBox(
			g_hwnd,
			L"BitmapTable::LoadImageFile()\nFrameDecoder을 얻어오지 못했습니다.",
			L"GetFrame()",
			MB_ICONERROR);
		return -1;
	}

	hr = m_pWicFactory->CreateFormatConverter(&pFormatConverter);
	if (FAILED(hr))
	{
		MessageBox(
			g_hwnd,
			L"BitmapTable::LoadImageFile()\nFormatConverter을 생성하지 못했습니다.",
			L"CreateFormatConverter()",
			MB_ICONERROR);
		return -1;
	}

	hr = pFormatConverter->Initialize(pFrameDecoder,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, nullptr, 0.0f,
		WICBitmapPaletteTypeCustom);

	if (FAILED(hr))
	{
		MessageBox(
			g_hwnd,
			L"BitmapTable::LoadImageFile()\npFormatConverter를 초기화하지 못했습니다.",
			L"Initialize()",
			MB_ICONERROR);
		return -1;
	}

	m_pRenderTarget->CreateBitmapFromWicBitmap(pFormatConverter, nullptr, &pBitmap);

	// 화면 Resize() 일수도 있으니깐 체크한 뒤 지워주기.
	if(list[(g_hasher(imageId))])
		list[(g_hasher(imageId))]->Release();
	list[(g_hasher(imageId))] = pBitmap;
		

	///////// 메모리 누수 해결. Release 순서 주의
	RELEASE(pFrameDecoder);
	RELEASE(pFormatConverter);
	RELEASE(pImageDecoder);

	return 0;
}


ID2D1Bitmap* BitmapTable::GetBitmap(const size_t& imageId)
{
	return list[imageId];
}


//ID2D1Bitmap* BitmapTable::GetBitmap(const std::string& imageId)
//{
//	return m_bitmapList[g_hasher(imageId)];
//}