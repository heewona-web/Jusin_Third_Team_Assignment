#include "pch.h"
#include "JW_Player.h"

JW_Player::JW_Player()
{

}

JW_Player::~JW_Player()
{
    Release();
}

void JW_Player::Initialize()
{
    m_tInfo.vPos = { 200.f,WINCY >> 1,0.f };
    m_tInfo.vLook = { 1.f,0.f,0.f };
    m_fSpeed = 2.f;

    m_fBodyLength = 15.f;
    m_fBeakLength = 20.f;

    // 왼쪽 위부터 시계방향으로 회전
    vBodyVertex[0] = { m_tInfo.vPos.x - m_fBodyLength, m_tInfo.vPos.y - m_fBodyLength, 0.f };
    vBodyVertex[1] = { m_tInfo.vPos.x + m_fBodyLength, m_tInfo.vPos.y - m_fBodyLength, 0.f };
    vBodyVertex[2] = { m_tInfo.vPos.x + m_fBodyLength, m_tInfo.vPos.y + m_fBodyLength, 0.f };
    vBodyVertex[3] = { m_tInfo.vPos.x - m_fBodyLength, m_tInfo.vPos.y + m_fBodyLength, 0.f };
    vBodyVertex[4] = { m_tInfo.vPos.x + m_fBeakLength, m_tInfo.vPos.y, 0.f };
}

int JW_Player::Update()
{
    return 0;
}

void JW_Player::LateUpdate()
{
}

void JW_Player::Render(HDC hDC)
{
    MoveToEx(hDC, vBodyVertex[0].x, vBodyVertex[0].y, NULL);
    LineTo(hDC, vBodyVertex[1].x, vBodyVertex[1].y);
    LineTo(hDC, vBodyVertex[2].x, vBodyVertex[2].y);
    LineTo(hDC, vBodyVertex[3].x, vBodyVertex[3].y);
    LineTo(hDC, vBodyVertex[0].x, vBodyVertex[0].y);

    MoveToEx(hDC, vBodyVertex[1].x, vBodyVertex[1].y, NULL);
    LineTo(hDC, vBodyVertex[4].x, vBodyVertex[4].y);
    LineTo(hDC, vBodyVertex[2].x, vBodyVertex[2].y);
}

void JW_Player::Release()
{
}
