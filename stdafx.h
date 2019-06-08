// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <d2d1.h>			// direct2D
#include <atltypes.h>		// ���� ������ ����ü, Ŭ����
#include <atlstr.h>			// wchar string
#include <dwrite.h>			// text
#include <string>
#include <unordered_map>	// hash
#include <wincodec.h>		// Windows Imaging Component
#include <crtdbg.h>			// �޸� ���� üũ

#include "SystemDefine.h"
#include "InputClass.h"
#include "Random.h"
#include "Vector2.h"		// ��ǥ
#include "Global.h"
#include "BitmapTable.h"	// �̹���
#include "Time.h"			// �ð�
#include "Camera.h"			// ī�޶�

#include "Event.h"
#include "ScreenResizeEvent.h"
#include "CollisionEvent.h"
#include "MessageEvent.h"

#include "GameObject.h"

#include "SceneClass.h"
#include "SceneManager.h"		// �� ����


// Library Files.
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "Dwrite.lib")

