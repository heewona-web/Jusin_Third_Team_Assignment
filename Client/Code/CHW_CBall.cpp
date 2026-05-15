#include "CHW_CBall.h"

CHW_CBall::CHW_CBall() : m_fRadius(0.f), m_fSpeed(0.f)
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
	m_fSpeed = 0.5f;
	m_vVelocity = { m_fSpeed , -m_fSpeed , 0.f }; //초기 속도
	D3DXVec3Normalize(&m_tInfo.vDir, &m_vVelocity);
	
}

void CHW_CBall::Update()
{
	//원점으로 이동
	m_vWorldCenter = m_vOriginCenter;
	m_vWorldCenter -= m_vOriginCenter;

	//MoveToOrigin(m_vWorldCenter, m_vOriginCenter);

	//SetDir();

	//경계면 체크
	CheckBoundary();

	//속도 및 위치 업데이트
	m_vVelocity = m_tInfo.vDir * m_fSpeed;
	m_tInfo.vPos += m_vVelocity;


	//행렬 적용
	MakeWorldMatrix();
	
	//행렬 반영
	D3DXVec3TransformCoord(&m_vWorldCenter, &m_vWorldCenter, &m_tInfo.matWorld);

	
}

void CHW_CBall::LateUpdate()
{
}



void CHW_CBall::Render(HDC hDC)
{
	Ellipse(hDC, m_vWorldCenter.x - m_fRadius, m_vWorldCenter.y - m_fRadius, m_vWorldCenter.x + m_fRadius, m_vWorldCenter.y + m_fRadius);
}

void CHW_CBall::Release()
{
}

void CHW_CBall::MoveToOrigin(_vec3 vWorld, _vec3 Origin) 
{
	vWorld = Origin;
	vWorld -= Origin;
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

void CHW_CBall::SetDir()
{
	// 경계면에 닿으면 반사각으로 Dir 적용
	//float fLeft = m_tInfo.vPos.x - m_fRadius;
	//float fRight = m_tInfo.vPos.x + m_fRadius;
	//float fTop = m_tInfo.vPos.y - m_fRadius;
	//float fBottom = m_tInfo.vPos.y + m_fRadius;

	//임시 test
	
	if (m_tInfo.vPos.y >= WINCY) {
		_vec3 n = { 0, -1, 0 };
		float fDot = D3DXVec3Dot(&m_vVelocity, &n);
		_vec3 v = m_vVelocity - 2 * fDot * n;
		
		D3DXVec3Normalize(&m_tInfo.vDir, &v);
		m_vVelocity = m_tInfo.vDir * m_fSpeed;
	}

	if (m_tInfo.vPos.y <= 0) {
		_vec3 n = { 0, 1, 0 };
		float fDot = D3DXVec3Dot(&m_vVelocity, &n);
		_vec3 v = m_vVelocity - 2 * fDot * n;

		D3DXVec3Normalize(&m_tInfo.vDir, &v);
		m_vVelocity = m_tInfo.vDir * m_fSpeed;
	}
	

	if (m_tInfo.vPos.x <= 0) {
		_vec3 n = { -1, 0, 0 };
		float fDot = D3DXVec3Dot(&m_vVelocity, &n);
		_vec3 v = m_vVelocity - 2 * fDot * n;

		D3DXVec3Normalize(&m_tInfo.vDir, &v);
		m_vVelocity = m_tInfo.vDir * m_fSpeed;
	}
	if (m_tInfo.vPos.x >= WINCX) {
		_vec3 n = { 1, 0, 0 };
		float fDot = D3DXVec3Dot(&m_vVelocity, &n);
		_vec3 v = m_vVelocity - 2 * fDot * n;

		D3DXVec3Normalize(&m_tInfo.vDir, &v);
		m_vVelocity = m_tInfo.vDir * m_fSpeed;
	}


}




void CHW_CBall::MakeWorldMatrix()
{
	D3DXMATRIX		matScale, matRotZ, matTrans;
	//D3DXMatrixScaling(&matScale, -1.f, 1.f, 1.f);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixIdentity(&matRotZ); // 일단 원이여서 회전 적용하지 않고.. 나중에  Rect로 테스트해서 회전 잘 적용되는 지 보자..?
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;
}

