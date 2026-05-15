#include "CHW_Stick.h"
#include "CHW_KeyMgr.h"

CHW_Stick::CHW_Stick() : m_fCurAngle(0.f), m_fSpeed(0.f)
{
}

CHW_Stick::~CHW_Stick()
{
	Release();
}

void CHW_Stick::Initialize()
{
	m_tInfo.vPos = {static_cast<float>(WINCX >> 1), static_cast<float>(WINCY) - 30.f, 0.f};		// 월드 위치




	m_vOriginScale = { 100.f , 20.f, 0.f };

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


	m_fSpeed = 2.f;


}

void CHW_Stick::Update()
{
	MoveToOrigin();

	KeyInput();
	//행렬 적용
	D3DXVECTOR3 vDir = { cosf(m_fCurAngle) ,sinf(m_fCurAngle), 0.f };
	D3DXVec3Normalize(&m_tInfo.vDir, &vDir);

	MakeWorldMatrix();

	//행렬 반영
	AdjustWorldMatrix();

}

void CHW_Stick::KeyInput()
{
	if (CHW_KeyMgr::Get_Instance()->KeyPressing(VK_LEFT))
		m_tInfo.vPos.x -= m_fSpeed;
	if (CHW_KeyMgr::Get_Instance()->KeyPressing(VK_RIGHT))
		m_tInfo.vPos.x += m_fSpeed;
	if (CHW_KeyMgr::Get_Instance()->KeyDown(VK_UP))
		m_fCurAngle += m_fRotAngle;
	if (CHW_KeyMgr::Get_Instance()->KeyDown(VK_DOWN))
		m_fCurAngle -= m_fRotAngle;


	//x좌표 clamping
	if (m_tInfo.vPos.x - m_vOriginScale.x < 0) {
		m_tInfo.vPos.x = m_vOriginScale.x;
	}
	if (m_tInfo.vPos.x + m_vOriginScale.x > WINCX) {
		m_tInfo.vPos.x = static_cast<float>(WINCX) - m_vOriginScale.x;
	}
}
void CHW_Stick::LateUpdate()
{
}

void CHW_Stick::Render(HDC hDC)
{
	RenderVertex(hDC);
}

void CHW_Stick::Release()
{
}


