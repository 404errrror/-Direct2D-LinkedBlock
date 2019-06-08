#pragma once

//////////////////////////////////
//// Define
//////////////////////////////////

// 화면 기본 사이즈.
#define DEFALUT_SCREEN_WIDTH	1280
#define DEFAULT_SCREEN_HEIGHT	720

#define MAX_SCREEN_WIDTH		1920
#define MAX_SCREEN_HEIGHT		1080

// 방향 키
#define LEFT	37
#define UP		38
#define RIGHT	39
#define DOWN	40

#define KEY_TAB		9		// 탭키

/////////////////////////////////
//// 매크로
/////////////////////////////////

// 인스턴스 삭제.
#define		RELEASE(X)		if(X){X->Release(); X = nullptr;}
#define		DELETE(X)		if(X){delete X; X = nullptr;}


// 메모리 누수 체크
#ifndef _DEBUG
#define new new(_CLIENT_BLOCK,__FILE__,__LINE)
#endif // !_DEBUG
