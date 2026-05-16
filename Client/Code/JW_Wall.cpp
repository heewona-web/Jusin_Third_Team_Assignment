#include "pch.h"
#include "JW_Wall.h"

JW_Wall::JW_Wall() :m_fWidth(0.f), m_fGapSize(0.f), m_fGapY(0.f)
{
}

JW_Wall::~JW_Wall()
{
	Release();
}

void JW_Wall::Initialize()
{
	m_tInfo.vPos.x = WINCX;
	m_tInfo.vPos.y = 0.f;
	m_fSpeed = 0.04f;

	m_fWidth = 60.f;
	m_fGapSize = 250.f;

	m_fGapY = (float)(rand() % (WINCY - 300) + 150);
}

void JW_Wall::Update()
{
	m_tInfo.vPos.x -= m_fSpeed;

	if (m_tInfo.vPos.x < -m_fWidth) {
		m_tInfo.vPos.x = WINCX + m_fWidth;
		m_fGapY = (float)(rand() % (WINCY - 300) + 150);
	}
}

void JW_Wall::LateUpdate()
{
}

void JW_Wall::Render(HDC hDC)
{
	Rectangle(hDC, m_tInfo.vPos.x - m_fWidth * 0.5f, 0, m_tInfo.vPos.x + m_fWidth * 0.5f, m_fGapY - m_fGapSize * 0.5f);

	Rectangle(hDC, m_tInfo.vPos.x - m_fWidth * 0.5f, m_fGapY + m_fGapSize * 0.5f, m_tInfo.vPos.x + m_fWidth * 0.5f, WINCY);
}

void JW_Wall::Release()
{
}
