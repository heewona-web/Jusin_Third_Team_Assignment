#include "pch.h"
#include "CHW_MyBmp.h"

CHW_MyBmp::CHW_MyBmp()
{
}

CHW_MyBmp::~CHW_MyBmp()
{
	//Release();
}

void CHW_MyBmp::Load_Bmp(const TCHAR* pFilePath)
{
	HDC	hDC = GetDC(g_hWnd);

	// CreateCompatibleDC : 매개 변수로 전달하는 dc와 호환되는 dc를 할당

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,			// 프로그램 인스턴스 핸들
		pFilePath,		// 파일의 위치 및 경로
		IMAGE_BITMAP,	// 어떤 타입을 읽어올 것인가
		0, 0,			// 이미지의 가로, 세로 사이즈(파일로 불러올 것이기 때문에 사이즈를 직접 지정해줄 필요가 없음)
		LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : 파일에서 이미지를 불러옴
	// LR_CREATEDIBSECTION : 읽어올 파일을 DIB 형태로 변환

// SelectObject : 준비한 dc의 gdi 오브젝트(m_hBitmap)에 불러들인 비트맵 정보를 선택함
// - gdi 오브젝트를 선택하기 전에 기존에 가지고 있던 오브젝트를 반환
	m_hOldbmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

}

void CHW_MyBmp::Free()
{
	SelectObject(m_hMemDC, m_hOldbmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
