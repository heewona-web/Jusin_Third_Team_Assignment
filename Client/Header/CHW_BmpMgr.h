#pragma once

#include "Engine_Function.h"
#include "CHW_MyBmp.h"

class CHW_BmpMgr
{
private:
	CHW_BmpMgr();
	CHW_BmpMgr(const CHW_BmpMgr& rhs) = delete;
	CHW_BmpMgr& operator=(CHW_BmpMgr& rCHW_BmpMgr) = delete;
	~CHW_BmpMgr();

public:
	void	Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC		Find_Image(const TCHAR* pImgKey);
	void	Release();

public:
	static CHW_BmpMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CHW_BmpMgr;
		}

		return m_pInstance;
	}
	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CHW_BmpMgr* m_pInstance;
	map<const TCHAR*, CHW_MyBmp*>		m_mapBit;

};

