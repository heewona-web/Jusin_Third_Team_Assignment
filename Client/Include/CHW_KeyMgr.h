#pragma once

#include "Define.h"

class CHW_KeyMgr
{
private:
	CHW_KeyMgr();
	CHW_KeyMgr(const CHW_KeyMgr& rhs) = delete;
	CHW_KeyMgr& operator=(CHW_KeyMgr& rKeyMgr) = delete;
	~CHW_KeyMgr();

public:
	bool KeyPressing(int iKey) const;
	bool KeyDown(int iKey) const;
	bool KeyUp(int iKey) const;

public:
	void Update();

public:
	static CHW_KeyMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CHW_KeyMgr;
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
	static CHW_KeyMgr* m_pInstance;


private:
	bool	m_bCurKeyState[0x99];
	bool	m_bPrevKeyState[0x99];

};

