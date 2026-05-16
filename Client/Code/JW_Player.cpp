#include "pch.h"
#include "JW_Player.h"

JW_Player::JW_Player() : m_bJump(false), m_fJumpPower(0.f), m_fGravity(0.f)
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
    
    m_fSpeed = 0.f;
    m_fJumpPower = -2.f;
    m_fGravity = 0.02f;
    m_fMaxFallSpeed = 0.25f;

    m_fAngle = 0.f;
    m_fRotateSpeed = 0.01f;

    m_fBodyLength = 15.f;
    m_fBeakLength = 20.f;

    // 왼쪽 위부터 시계방향으로 회전
    vBodyVertex[0] = { m_tInfo.vPos.x - m_fBodyLength, m_tInfo.vPos.y - m_fBodyLength, 0.f };
    vBodyVertex[1] = { m_tInfo.vPos.x + m_fBodyLength, m_tInfo.vPos.y - m_fBodyLength, 0.f };
    vBodyVertex[2] = { m_tInfo.vPos.x + m_fBodyLength, m_tInfo.vPos.y + m_fBodyLength, 0.f };
    vBodyVertex[3] = { m_tInfo.vPos.x - m_fBodyLength, m_tInfo.vPos.y + m_fBodyLength, 0.f };
    vBodyVertex[4] = { m_tInfo.vPos.x + m_fBeakLength, m_tInfo.vPos.y, 0.f };
}

void JW_Player::Update()
{
    Key_Input();
    
}

void JW_Player::LateUpdate() 
{
    Jump();
    Body_Rotate();
}

void JW_Player::Render(HDC hDC)
{
    MoveToEx(hDC, vBodyVertex[0].x, vBodyVertex[0].y, NULL);
    
    for (int i = 0; i < 4; i++) {
        LineTo(hDC, vBodyVertex[i].x, vBodyVertex[i].y);
    }
    LineTo(hDC, vBodyVertex[0].x, vBodyVertex[0].y);

    MoveToEx(hDC, vBodyVertex[1].x, vBodyVertex[1].y, NULL);
    LineTo(hDC, vBodyVertex[4].x, vBodyVertex[4].y);
    LineTo(hDC, vBodyVertex[2].x, vBodyVertex[2].y);
}

void JW_Player::Release()
{

}

void JW_Player::Key_Input()
{
    if (GetAsyncKeyState(VK_SPACE) & 0x0001) {
        m_fSpeed = m_fJumpPower;
    }
}

void JW_Player::Jump()
{
    m_fSpeed += m_fGravity;

    if (m_fSpeed > m_fMaxFallSpeed) {
        m_fSpeed = m_fMaxFallSpeed;
    }

    m_tInfo.vPos.y += m_fSpeed;

    if (m_tInfo.vPos.y > WINCY) {
        m_tInfo.vPos.y = WINCY;
        //게임 오버 처리 필요
    }

    if (m_fSpeed < 0.f) {
        m_fAngle = D3DXToRadian(-45.f);
    }
    else {
        if (m_fAngle < D3DXToRadian(90.f)) {
            m_fAngle += m_fRotateSpeed;
        }
    }
}

void JW_Player::Body_Rotate()
{
    D3DXMATRIX matRotZ, matTrans;

    D3DXMatrixRotationZ(&matRotZ, m_fAngle);
    D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

    m_tInfo.matWorld = matRotZ * matTrans;

    /*for (int i = 0; i < 5; ++i) {
        vLocalBodyVertex[i] = { vBodyVertex[i].x - m_tInfo.vPos.x,vBodyVertex[i].y - m_tInfo.vPos.y,0.f };
    }*/
    vLocalBodyVertex[0] = { -m_fBodyLength,-m_fBodyLength,0.f };
    vLocalBodyVertex[1] = { m_fBodyLength,-m_fBodyLength,0.f };
    vLocalBodyVertex[2] = { m_fBodyLength,m_fBodyLength,0.f };
    vLocalBodyVertex[3] = { -m_fBodyLength,m_fBodyLength,0.f };
    vLocalBodyVertex[4] = { m_fBeakLength,0.f,0.f };

    for (int i = 0; i < 5; ++i) {
        D3DXVec3TransformCoord(&vBodyVertex[i], &vLocalBodyVertex[i], &m_tInfo.matWorld);
    }

    D3DXVECTOR3 vLookLocal = { 1.f, 0.f, 0.f };
    D3DXVec3TransformNormal(&m_tInfo.vLook, &vLookLocal, &m_tInfo.matWorld);
}