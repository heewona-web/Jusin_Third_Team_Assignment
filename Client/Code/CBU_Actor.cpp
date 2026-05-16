#include "CBU_Actor.h"
#include "CBU_KeyManager.h"
#include "CBU_VectorUtil.h"

CBU_Actor::CBU_Actor() : CBU_Object(BU_OBJID::PLAYER)
{

}
CBU_Actor::~CBU_Actor()
{

}

void CBU_Actor::Initialize(void) 
{
	// 크기 정보 초기화
	m_vecScale = { 50.f, 20.f, 50.f };
	// 위치 정보 초기화
	m_tInfo.vPos = {400.f, 500.f, 0.f};
	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, 0.f, 1.f };

	// 버텍스 정보 초기화
	//m_vecOriginalVertices.push_back({ -1.2f, -0.5f, 0.f }); // 0
	//m_vecOriginalVertices.push_back({ 1.2f, -0.5f, 0.f }); // 1
	//m_vecOriginalVertices.push_back({ 0.9f, 0.5f, 0.f }); // 2
	//m_vecOriginalVertices.push_back({ -0.9f, 0.5f, 0.f }); // 3

	// 넓적한 팔각기둥인데 아래가 작음
	m_vecOriginalVertices.push_back({ -1.3065f, -0.5f, 0.f }); // 0
	m_vecOriginalVertices.push_back({ -0.923835f, -0.5f, 0.923835f }); // 1
	m_vecOriginalVertices.push_back({ 0.f, -0.5f, 1.3065f }); // 2
	m_vecOriginalVertices.push_back({ 0.923835f, -0.5f, 0.923835f }); // 3
	m_vecOriginalVertices.push_back({ 1.3065f, -0.5f, 0.f }); // 4
	m_vecOriginalVertices.push_back({ 0.923835f, -0.5f, -0.923835f }); // 5
	m_vecOriginalVertices.push_back({ 0.f, -0.5f, -1.3065f }); // 6
	m_vecOriginalVertices.push_back({ -0.923835f, -0.5f, -0.923835f }); // 7
	m_vecOriginalVertices.push_back({ -0.f, -0.5f, -0.f }); // 8 중심

	m_vecOriginalVertices.push_back({ -1.0452f, 0.5f, 0.f }); // 0
	m_vecOriginalVertices.push_back({ -0.739068f, 0.5f, 0.739068f }); // 1
	m_vecOriginalVertices.push_back({ 0.f, 0.5f, 1.0452f }); // 2
	m_vecOriginalVertices.push_back({ 0.739068f, 0.5f, 0.739068f }); // 3
	m_vecOriginalVertices.push_back({ 1.0452f, 0.5f, 0.f }); // 4
	m_vecOriginalVertices.push_back({ 0.739068f, 0.5f, -0.739068f }); // 5
	m_vecOriginalVertices.push_back({ 0.f, 0.5f, -1.0452f }); // 6
	m_vecOriginalVertices.push_back({ -0.739068f, 0.5f, -0.739068f }); // 7
	m_vecOriginalVertices.push_back({ -0.f, 0.5f, -0.f }); // 8 중심

	// 렌더 정보 버텍스에 같은 크기만큼 복사
	for (size_t idx = 0; idx < m_vecOriginalVertices.size(); ++idx)
	{
		m_vecRenderVertices.push_back({ 0.f, 0.f, 0.f });
	}

	// 인덱스 정보 초기화
	//m_pIndicesList.push_back(new INDEX32({ 0, 1, 2 }));
	//m_pIndicesList.push_back(new INDEX32({ 2, 3, 0 }));

	// 인덱스 정보 초기화
	m_pIndicesList.push_back(new INDEX32({ 0, 1, 8 }));
	m_pIndicesList.push_back(new INDEX32({ 1, 2, 8 }));
	m_pIndicesList.push_back(new INDEX32({ 2, 3, 8 }));
	m_pIndicesList.push_back(new INDEX32({ 3, 4, 8 }));
	m_pIndicesList.push_back(new INDEX32({ 4, 5, 8 }));
	m_pIndicesList.push_back(new INDEX32({ 5, 6, 8 }));
	m_pIndicesList.push_back(new INDEX32({ 6, 7, 8 }));
	m_pIndicesList.push_back(new INDEX32({ 7, 0, 8 }));

	m_pIndicesList.push_back(new INDEX32({ 0, 1, 10 }));
	m_pIndicesList.push_back(new INDEX32({ 10, 9, 0 }));
	m_pIndicesList.push_back(new INDEX32({ 1, 2, 11 }));
	m_pIndicesList.push_back(new INDEX32({ 11, 10, 1 }));
	m_pIndicesList.push_back(new INDEX32({ 2, 3, 12 }));
	m_pIndicesList.push_back(new INDEX32({ 12, 11, 2 }));
	m_pIndicesList.push_back(new INDEX32({ 3, 4, 13 }));
	m_pIndicesList.push_back(new INDEX32({ 13, 12, 3 }));
	m_pIndicesList.push_back(new INDEX32({ 4, 5, 14 }));
	m_pIndicesList.push_back(new INDEX32({ 14, 13, 4 }));
	m_pIndicesList.push_back(new INDEX32({ 5, 6, 15 }));
	m_pIndicesList.push_back(new INDEX32({ 15, 14, 5 }));
	m_pIndicesList.push_back(new INDEX32({ 6, 7, 16 }));
	m_pIndicesList.push_back(new INDEX32({ 16, 15, 6 }));
	m_pIndicesList.push_back(new INDEX32({ 7, 0, 9 }));
	m_pIndicesList.push_back(new INDEX32({ 9, 16, 7 }));

	m_pIndicesList.push_back(new INDEX32({ 9, 10, 17 }));
	m_pIndicesList.push_back(new INDEX32({ 10, 11, 17 }));
	m_pIndicesList.push_back(new INDEX32({ 11, 12, 17 }));
	m_pIndicesList.push_back(new INDEX32({ 12, 13, 17 }));
	m_pIndicesList.push_back(new INDEX32({ 13, 14, 17 }));
	m_pIndicesList.push_back(new INDEX32({ 14, 15, 17 }));
	m_pIndicesList.push_back(new INDEX32({ 15, 16, 17 }));
	m_pIndicesList.push_back(new INDEX32({ 16, 9, 17 }));

	m_fSpeed = 10.f;
}

void CBU_Actor::Update(void) 
{
	// 방향 벡터 초기화
	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	if (CBU_KeyManager::GetInstance()->KeyPressing('W'))
	{
		m_tInfo.vDir = CBU_VectorUtil::GetXZProjectedVector(m_tInfo.vLook);
		//m_tInfo.vPos += m_tInfo.vDir * (m_fSpeed*0.1f);
	}
	if (CBU_KeyManager::GetInstance()->KeyPressing('S'))
	{
		m_tInfo.vDir = -CBU_VectorUtil::GetXZProjectedVector(m_tInfo.vLook);
		//m_tInfo.vPos += m_tInfo.vDir * (m_fSpeed * 0.3f * 0.1f);
	}
	if (CBU_KeyManager::GetInstance()->KeyPressing('A'))
	{
		// 왼쪽으로 가려면 아래 방향과 외적
		_vec3 vecXZProjectedLook = CBU_VectorUtil::GetXZProjectedVector(m_tInfo.vLook);
		D3DXVec3Cross(&m_tInfo.vDir, &CBU_Object::UPVEC, &vecXZProjectedLook);
		//m_tInfo.vPos += m_tInfo.vDir * (m_fSpeed * 0.5f);
	}
	if (CBU_KeyManager::GetInstance()->KeyPressing('D'))
	{
		// 오른쪽으로 가려면 윗 방향과 외적
		_vec3 vecXZProjectedLook = CBU_VectorUtil::GetXZProjectedVector(m_tInfo.vLook);
		D3DXVec3Cross(&m_tInfo.vDir, &CBU_Object::DOWNVEC, &vecXZProjectedLook);
		//m_tInfo.vPos += m_tInfo.vDir * (m_fSpeed * 0.5f);
	}

	if (CBU_KeyManager::GetInstance()->KeyPressing(VK_LEFT))
	{
		// 반시계로 회전
		m_fAngle -= 0.01f * D3DX_PI;
	}
	if (CBU_KeyManager::GetInstance()->KeyPressing(VK_RIGHT))
	{
		// 시계로 회전
		m_fAngle += 0.01f * D3DX_PI;
	}
	if (CBU_KeyManager::GetInstance()->KeyPressing(VK_UP))
	{
		// 시계로 회전
		m_fAngleX += 0.01f * D3DX_PI;
	}
	if (CBU_KeyManager::GetInstance()->KeyPressing(VK_DOWN))
	{
		// 시계로 회전
		m_fAngleX -= 0.01f * D3DX_PI;
	}

	// 월드 변환 행렬 업데이트(크자이)
	CBU_Object::Update();
}

void CBU_Actor::LateUpdate(void) 
{

}