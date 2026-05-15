#include "CHW_CBall.h"

CHW_CBall::CHW_CBall() : m_fSpeed(0.f)
{
}

CHW_CBall::~CHW_CBall()
{
	Release();
}

void CHW_CBall::Initialize()
{

	m_tInfo.vPos = { 400.f, 300.f, 0.f };		// 월드 위치




	m_vOriginScale = { 30.f , 30.f, 0.f };

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


	m_fSpeed = 0.5f;
	m_vVelocity = { m_fSpeed , m_fSpeed , 0.f }; //초기 속도
	D3DXVec3Normalize(&m_tInfo.vDir, &m_vVelocity); 
	
}

void CHW_CBall::Update()
{


	MoveToOrigin();

	//경계면 체크
	CheckBoundary();

	//속도 및 위치 업데이트
	m_vVelocity = m_tInfo.vDir * m_fSpeed;
	m_tInfo.vPos += m_vVelocity;


	//행렬 적용
	MakeWorldMatrix();
	
	//행렬 반영
	AdjustWorldMatrix();


	
}

void CHW_CBall::LateUpdate()
{
}



void CHW_CBall::Render(HDC hDC)
{
	RenderVertex(hDC);
}

void CHW_CBall::Release()
{
}


void CHW_CBall::CheckBoundary()
{

	if (m_tInfo.vPos.x > 0 && m_tInfo.vPos.x < WINCX && m_tInfo.vPos.y > 0 && m_tInfo.vPos.y < WINCY)
		return;

	_vec3 n = { 0,0,0 };



	if (m_tInfo.vPos.x <= 0) {
		n = { -1, 0, 0 };
	}
	if (m_tInfo.vPos.x >= WINCX) {
		n = { 1, 0, 0 };
	}
	if (m_tInfo.vPos.y <= 0) {
		n = { 0, 1, 0 };
	}
	if (m_tInfo.vPos.y >= WINCY) {
		n = { 0, -1, 0 };
	}

	SetDirection(n);


}

void CHW_CBall::SetDirection(_vec3 normal)
{
	float fDot = D3DXVec3Dot(&m_vVelocity, &normal);
	_vec3 vNewDir = m_vVelocity - 2 * fDot * normal;

	D3DXVec3Normalize(&m_tInfo.vDir, &vNewDir);
}





