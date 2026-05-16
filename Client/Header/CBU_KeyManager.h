#pragma once
#include "Engine_Define.h"
#include "BU_Define.h"

class CBU_KeyManager
{
private:
	CBU_KeyManager() {}
	~CBU_KeyManager() {}
	DECLARE_SINGLETON(CBU_KeyManager)

public:
	void Update(void);

	bool KeyPressing(int iKey);
	bool KeyUp(int iKey);
	bool KeyDown(int iKey);
	bool GetKeyPressed(int iKey) const;

private:
	bool m_bKeyState[VK_MAX];
};

