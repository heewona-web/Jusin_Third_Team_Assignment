#include "CHW_CBall.h"

CHW_CBall::CHW_CBall() : m_fRadius(0.f), m_fSpeed(0.f), m_fCurAngle(0.f)
{
}

CHW_CBall::~CHW_CBall()
{
	Release();
}

void CHW_CBall::Initialize()
{

	m_tInfo.vPos = { 400.f, 300.f, 0.f };		// 월드 위치


	m_fRadius = 20.f;

	m_vOriginScale = { 20.f , 20.f, 0.f };

	// 사각형
	//m_vWorldPoints.resize(4);
	//m_vWorldPoints[0] = { m_tInfo.vPos.x - m_vOriginScale.x, m_tInfo.vPos.y - m_vOriginScale.y, 0.f }; // 죄상단
	//m_vWorldPoints[1] = { m_tInfo.vPos.x + m_vOriginScale.x, m_tInfo.vPos.y - m_vOriginScale.y, 0.f }; // 우상단
	//m_vWorldPoints[2] = { m_tInfo.vPos.x + m_vOriginScale.x, m_tInfo.vPos.y + m_vOriginScale.y, 0.f }; // 우하단
	//m_vWorldPoints[3] = { m_tInfo.vPos.x - m_vOriginScale.x, m_tInfo.vPos.y + m_vOriginScale.y, 0.f }; // 좌하단

	// 거의 원
	const int iVertexNum = 18;
	m_vWorldPoints.reserve(iVertexNum);
	for (size_t i = 0; i < iVertexNum; ++i) {
		
		float fDegree = i * (360.f / iVertexNum);
		float fRadian = fDegree * D3DX_PI / 180.f;

		m_vWorldPoints.push_back({ m_tInfo.vPos.x + m_fRadius * cosf(fRadian),m_tInfo.vPos.y + m_fRadius * sinf(fRadian), 0.f });

	}




	m_vOriginPoints.reserve(m_vWorldPoints.size());
	for (auto& v : m_vWorldPoints) {
		m_vOriginPoints.push_back(v - m_tInfo.vPos); //Origin 은 (0,0)기준으로 크기만 반영되게끔 조작

		//m_vOriginPoints.push_back(v);
	}


	m_fSpeed = 0.5f;
	m_vVelocity = { m_fSpeed , 1 , 0.f }; //초기 속도
	D3DXVec3Normalize(&m_tInfo.vDir, &m_vVelocity); 
	
}

int CHW_CBall::Update()
{


	MoveToOrigin();


	// 매 프레임 회전
	m_fCurAngle += m_fRotAngle;
	if (m_fCurAngle > 2 * D3DX_PI) {
		m_fCurAngle -= 2 * D3DX_PI;
	}
	

	//경계면 체크
	CheckBoundary();

	//속도 및 위치 업데이트
	m_vVelocity = m_tInfo.vDir * m_fSpeed;
	m_tInfo.vPos += m_vVelocity;


	//행렬 적용
	MakeWorldMatrix();
	
	//행렬 반영
	AdjustWorldMatrix();


	return 0;

	
}

void CHW_CBall::LateUpdate()
{
}



void CHW_CBall::Render(HDC hDC)
{
	RenderVertex(hDC);
	//회전을 시각적으로 보여주기 위해
	MoveToEx(hDC, m_vWorldPoints[0].x, m_vWorldPoints[0].y, NULL);
	int next = m_vWorldPoints.size() / 2;
	LineTo(hDC, m_vWorldPoints[next].x, m_vWorldPoints[next].y);
}

void CHW_CBall::Release()
{
}


void CHW_CBall::CheckBoundary()
{
	
	// 정확하게는 체크 X



	if (m_tInfo.vPos.x - m_fRadius > 0 && m_tInfo.vPos.x + m_fRadius < WINCX && m_tInfo.vPos.y - m_fRadius > 0 && m_tInfo.vPos.y + m_fRadius < WINCY)
		return;

	_vec3 n = { 0,0,0 };



	if (m_tInfo.vPos.x - m_fRadius <= 0) {
		n = { -1, 0, 0 };
	}
	if (m_tInfo.vPos.x + m_fRadius >= WINCX) {
		n = { 1, 0, 0 };
	}
	if (m_tInfo.vPos.y - m_fRadius <= 0) {
		n = { 0, 1, 0 };
	}
	if (m_tInfo.vPos.y + m_fRadius >= WINCY) {
		n = { 0, -1, 0 };
	}

	SetDirection_UseNormal(n);


}

void CHW_CBall::SetDirection_UseNormal(_vec3 normal)
{
	float fDot = D3DXVec3Dot(&m_vVelocity, &normal);
	_vec3 vNewDir = m_vVelocity - 2 * fDot * normal;

	D3DXVec3Normalize(&m_tInfo.vDir, &vNewDir);
}

void CHW_CBall::SetPosion_UseMTV(_vec3 normal, float value)
{
	m_tInfo.vPos += normal * value; 
}

void CHW_CBall::MakeWorldMatrix()
{
	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixRotationZ(&matRotZ, m_fCurAngle);

	
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;
}





