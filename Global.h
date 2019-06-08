#pragma once
#include "stdafx.h"

///////////////////////////////////////////
//             Global                    //
///////////////////////////////////////////

extern HWND						g_hwnd;				// 윈도우 핸들. 원래 멤버였으나, 메세지박스를 어디서든 사용하기 위해.

extern CRect					g_screenRect;		// 화면크기
extern float					g_screenRatio;		// 화면곱
extern float					g_screenRatioInv;	// 화면곱의 역수. 마우스 포인터와 같이 화면 크기를 상쇄 시켜야할때.
extern float					g_screenHeightRatio;// height 비율 
extern float					g_screenWidthRatio;	// width 비율 화면 끝에 좌표를 알기 위해서. 길쭈우욱하게 될 경우 이미지 클리핑 마스크 위치를 위해서.
extern D2D1_MATRIX_3X2_F		g_defaultMatrix;
extern float					g_screenMag;		// 화면 배율

extern float					g_windowRight;		// 윈도우 좌우 창틀 크기
extern float					g_windowTop;		// 윈도우 아래위 창틀 크기

extern bool						g_debugMode;		// 디버그 모드.

extern bool						g_leftDown;			// 왼쪽 마우스. ------> 테스트용으로 만듬. 나중에 클래스화.
extern D2D1_POINT_2F			g_mousePos;
extern Vector2					g_mouseDesPos;

extern InputClass*				g_pInput;

extern std::hash<std::string>	g_hasher;			// 문자열 해시



//////////////////////////////////////////
//				Function				//
//////////////////////////////////////////

