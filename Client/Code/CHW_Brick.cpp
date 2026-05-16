#include "CHW_Brick.h"

CHW_Brick::CHW_Brick()
{
}

CHW_Brick::CHW_Brick(float fX, float fY)
{
	m_tInfo.vPos.x = fX;
	m_tInfo.vPos.y = fY;

}

CHW_Brick::~CHW_Brick()
{
	Release();
}

void CHW_Brick::Initialize()
{
	m_vOriginScale = { 50.f , 15.f, 0.f };

	// 사각형
	m_vWorldPoints.resize(4);
	m_vWorldPoints[0] = { m_tInfo.vPos.x - m_vOriginScale.x, m_tInfo.vPos.y - m_vOriginScale.y, 0.f }; // 죄상단
	m_vWorldPoints[1] = { m_tInfo.vPos.x + m_vOriginScale.x, m_tInfo.vPos.y - m_vOriginScale.y, 0.f }; // 우상단
	m_vWorldPoints[2] = { m_tInfo.vPos.x + m_vOriginScale.x, m_tInfo.vPos.y + m_vOriginScale.y, 0.f }; // 우하단
	m_vWorldPoints[3] = { m_tInfo.vPos.x - m_vOriginScale.x, m_tInfo.vPos.y + m_vOriginScale.y, 0.f }; // 좌하단


	m_vOriginPoints.reserve(m_vWorldPoints.size());
	for (auto& v : m_vWorldPoints) {
		m_vOriginPoints.push_back(v - m_tInfo.vPos); //Origin 은 (0,0)기준으로 크기만 반영되게끔 조작
	}

}

int CHW_Brick::Update()
{
	if (m_bIsCollide)
		return -1;


	return 0;

}

void CHW_Brick::LateUpdate()
{
}

void CHW_Brick::Render(HDC hDC)
{
	RenderVertex(hDC);
}

void CHW_Brick::Release()
{
}
