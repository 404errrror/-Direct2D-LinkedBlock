#pragma once
#include "stdafx.h"

///////////////////////////////////////////
//             Global                    //
///////////////////////////////////////////

extern HWND						g_hwnd;				// ������ �ڵ�. ���� ���������, �޼����ڽ��� ��𼭵� ����ϱ� ����.

extern CRect					g_screenRect;		// ȭ��ũ��
extern float					g_screenRatio;		// ȭ���
extern float					g_screenRatioInv;	// ȭ����� ����. ���콺 �����Ϳ� ���� ȭ�� ũ�⸦ ��� ���Ѿ��Ҷ�.
extern float					g_screenHeightRatio;// height ���� 
extern float					g_screenWidthRatio;	// width ���� ȭ�� ���� ��ǥ�� �˱� ���ؼ�. ���޿���ϰ� �� ��� �̹��� Ŭ���� ����ũ ��ġ�� ���ؼ�.
extern D2D1_MATRIX_3X2_F		g_defaultMatrix;
extern float					g_screenMag;		// ȭ�� ����

extern float					g_windowRight;		// ������ �¿� âƲ ũ��
extern float					g_windowTop;		// ������ �Ʒ��� âƲ ũ��

extern bool						g_debugMode;		// ����� ���.

extern bool						g_leftDown;			// ���� ���콺. ------> �׽�Ʈ������ ����. ���߿� Ŭ����ȭ.
extern D2D1_POINT_2F			g_mousePos;
extern Vector2					g_mouseDesPos;

extern InputClass*				g_pInput;

extern std::hash<std::string>	g_hasher;			// ���ڿ� �ؽ�



//////////////////////////////////////////
//				Function				//
//////////////////////////////////////////

