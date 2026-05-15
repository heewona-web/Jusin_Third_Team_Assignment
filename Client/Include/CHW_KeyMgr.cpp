#include "CHW_KeyMgr.h"

CHW_KeyMgr* CHW_KeyMgr::m_pInstance = nullptr;

CHW_KeyMgr::CHW_KeyMgr() {
	ZeroMemory(m_bCurKeyState, sizeof(m_bCurKeyState));
	ZeroMemory(m_bPrevKeyState, sizeof(m_bPrevKeyState));
}

CHW_KeyMgr::~CHW_KeyMgr() {

}

void CHW_KeyMgr::Update() {
	// 이전 상태 저장
	for (int i = 0; i < 0x99; ++i)
		m_bPrevKeyState[i] = m_bCurKeyState[i];

	// 현재 상태 갱신
	for (int i = 0; i < 0x99; ++i)
		m_bCurKeyState[i] = ((GetAsyncKeyState(i) & 0x8000) != 0);
}


bool CHW_KeyMgr::KeyPressing(int iKey) const
{
	if (iKey < 0 || iKey >= 0x99) return false;


	return m_bCurKeyState[iKey];
}

bool CHW_KeyMgr::KeyDown(int iKey) const
{
	if (iKey < 0 || iKey >= 0x99) return false;


	return m_bCurKeyState[iKey] && !m_bPrevKeyState[iKey];
}

bool CHW_KeyMgr::KeyUp(int iKey) const
{
	if (iKey < 0 || iKey >= 0x99) return false;


	return !m_bCurKeyState[iKey] && m_bPrevKeyState[iKey];
}
