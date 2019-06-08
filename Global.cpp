#include "stdafx.h"
#include "Global.h"

///////////////////////////////////////////
//             Global                    //
///////////////////////////////////////////

HWND					g_hwnd = nullptr;

CRect					g_screenRect;
float					g_screenRatio;
float					g_screenRatioInv;
float					g_screenHeightRatio;
float					g_screenWidthRatio;
D2D1_MATRIX_3X2_F		g_defaultMatrix;
float					g_screenMag = 1;

float					g_windowRight;
float					g_windowTop;

bool					g_debugMode = false;

bool					g_leftDown = false;
D2D1_POINT_2F			g_mousePos;
Vector2					g_mouseDesPos(0,0);

InputClass*				g_pInput = nullptr;

std::hash<std::string>	g_hasher;

//////////////////////////////////////////
//				Function				//
//////////////////////////////////////////
