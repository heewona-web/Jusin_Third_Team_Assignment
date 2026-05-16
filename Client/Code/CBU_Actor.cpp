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
	m_vecScale = { 20.f, 20.f, 20.f };
	// 위치 정보 초기화
	m_tInfo.vPos = {400.f, 500.f, 0.f};
	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, 0.f, 1.f };

	// 버텍스 정보 초기화
	m_pVecOriginalVertices.push_back(new _vec3({ -1.f, -0.5f, 0.f })); // 0
	m_pVecOriginalVertices.push_back(new _vec3({ 1.f, -0.5f, 0.f })); // 1
	m_pVecOriginalVertices.push_back(new _vec3({ 1.f, 0.5f, 0.f })); // 2
	m_pVecOriginalVertices.push_back(new _vec3({ -1.f, 0.5f, 0.f })); // 3

	// 렌더 정보 버텍스에 같은 크기만큼 복사
	for (size_t idx = 0; idx < m_pVecOriginalVertices.size(); ++idx)
	{
		m_pVecRenderVertices.push_back(new _vec3);
	}

	// 인덱스 정보 초기화
	m_pIndicesList.push_back(new INDEX32({ 0, 1, 2 }));
	m_pIndicesList.push_back(new INDEX32({ 2, 3, 0 }));

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

	// 월드 변환 행렬 업데이트(크자이)
	CBU_Object::Update();
}

void CBU_Actor::LateUpdate(void) 
{

}