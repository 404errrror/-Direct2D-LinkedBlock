// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <d2d1.h>			// direct2D
#include <atltypes.h>		// 각종 윈도우 구조체, 클래스
#include <atlstr.h>			// wchar string
#include <dwrite.h>			// text
#include <string>
#include <unordered_map>	// hash
#include <wincodec.h>		// Windows Imaging Component
#include <crtdbg.h>			// 메모리 누수 체크

#include "SystemDefine.h"
#include "InputClass.h"
#include "Random.h"
#include "Vector2.h"		// 좌표
#include "Global.h"
#include "BitmapTable.h"	// 이미지
#include "Time.h"			// 시간
#include "Camera.h"			// 카메라

#include "Event.h"
#include "ScreenResizeEvent.h"
#include "CollisionEvent.h"
#include "MessageEvent.h"

#include "GameObject.h"

#include "SceneClass.h"
#include "SceneManager.h"		// 씬 관리


// Library Files.
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "Dwrite.lib")

