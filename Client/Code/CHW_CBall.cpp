#include "CHW_CBall.h"

CHW_CBall::CHW_CBall() : m_fRadius(0)
{
}

CHW_CBall::~CHW_CBall()
{
}

void CHW_CBall::Initialize()
{

	m_tInfo.vPos = { 400.f, 300.f, 0.f };		// 월드 위치

	m_vWorldCenter = { m_tInfo.vPos.x , m_tInfo.vPos.y, m_tInfo.vPos.z };

	m_vOriginCenter = m_vWorldCenter;

	m_fRadius = 50.f;
	m_fSpeed = 0.f;
	
}

void CHW_CBall::Update()
{

}

void CHW_CBall::LateUpdate()
{
}

void CHW_CBall::Render(HDC hDC)
{
	Ellipse(hDC, m_vWorldCenter.x - m_fRadius, m_vOriginCenter.y - m_fRadius, m_vWorldCenter.x + m_fRadius, m_vWorldCenter.y + m_fRadius);
}

void CHW_CBall::Release()
{
}
