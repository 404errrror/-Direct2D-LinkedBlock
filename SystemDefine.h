#pragma once

//////////////////////////////////
//// Define
//////////////////////////////////

// ȭ�� �⺻ ������.
#define DEFALUT_SCREEN_WIDTH	1280
#define DEFAULT_SCREEN_HEIGHT	720

#define MAX_SCREEN_WIDTH		1920
#define MAX_SCREEN_HEIGHT		1080

// ���� Ű
#define LEFT	37
#define UP		38
#define RIGHT	39
#define DOWN	40

#define KEY_TAB		9		// ��Ű

/////////////////////////////////
//// ��ũ��
/////////////////////////////////

// �ν��Ͻ� ����.
#define		RELEASE(X)		if(X){X->Release(); X = nullptr;}
#define		DELETE(X)		if(X){delete X; X = nullptr;}


// �޸� ���� üũ
#ifndef _DEBUG
#define new new(_CLIENT_BLOCK,__FILE__,__LINE)
#endif // !_DEBUG
