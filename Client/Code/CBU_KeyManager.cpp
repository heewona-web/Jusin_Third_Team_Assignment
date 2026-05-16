#include "CBU_KeyManager.h"

IMPLEMENT_SINGLETON(CBU_KeyManager)
void CBU_KeyManager::Update(void)
{
    for (int i = 0; i < VK_MAX; ++i)
    {
        if ((m_bKeyState[i]) && !KeyPressing(i))
        {
            m_bKeyState[i] = !m_bKeyState[i];
        }

        if ((!m_bKeyState[i]) && KeyPressing(i))
        {
            m_bKeyState[i] = !m_bKeyState[i];
        }
    }
}

bool CBU_KeyManager::KeyPressing(int iKey)
{
    // 0x8000은 GetAsyncKeyState 함수 반환 쪽 참고. 리턴값 이전에 첨부 해드렸음
    // & 연산해서 8001, 8000 둘 다 걸리게 함
    return GetAsyncKeyState(iKey) & 0x8000;
}

bool CBU_KeyManager::KeyUp(int iKey)
{
    if (m_bKeyState[iKey] && !KeyPressing(iKey))
    {
        m_bKeyState[iKey] = !m_bKeyState[iKey];
        return true;
    }

    return false;
}

bool CBU_KeyManager::KeyDown(int iKey)
{
    if (!m_bKeyState[iKey] && KeyPressing(iKey))
    {
        m_bKeyState[iKey] = !m_bKeyState[iKey];
        return true;
    }

    return false;
}

bool CBU_KeyManager::GetKeyPressed(int iKey) const
{
    return m_bKeyState[iKey];
}
