#pragma once

#include "Define.h"
#include "CBase.h"

class CHW_MyBmp : public CBase
{
public:
	CHW_MyBmp();
	~CHW_MyBmp();

public:
	HDC		Get_MemDC() { return m_hMemDC; }


public:
	void	Load_Bmp(const TCHAR* pFilePath);
	void	Free();


private:
	HDC	m_hMemDC;

	HBITMAP	m_hBitmap;
	HBITMAP	m_hOldbmp;

};

