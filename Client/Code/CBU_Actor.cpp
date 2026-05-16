#include "CBU_Actor.h"
#include "CBU_KeyManager.h"
#include "CBU_VectorUtil.h"

CBU_Actor::CBU_Actor()
{

}
CBU_Actor::~CBU_Actor()
{

}

void CBU_Actor::Initialize(void) 
{
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
	if (CBU_KeyManager::GetInstance()->KeyPressing('W'))
	{
		m_tInfo.vDir = CBU_VectorUtil::GetXZProjectedVector(m_tInfo.vLook);
		m_tInfo.vPos += m_tInfo.vDir * (m_fSpeed*0.1f);
	}
	else if (CBU_KeyManager::GetInstance()->KeyPressing('S'))
	{
		m_tInfo.vDir = -CBU_VectorUtil::GetXZProjectedVector(m_tInfo.vLook);
		m_tInfo.vPos += m_tInfo.vDir * (m_fSpeed * 0.3f * 0.1f);
	}
	else if (CBU_KeyManager::GetInstance()->KeyPressing('A'))
	{
		// 왼쪽으로 가려면 아래 방향과 외적
		_vec3 vecXZProjectedLook = CBU_VectorUtil::GetXZProjectedVector(m_tInfo.vLook);
		D3DXVec3Cross(&m_tInfo.vDir, &CBU_Object::UPVEC, &vecXZProjectedLook);
		m_tInfo.vPos += m_tInfo.vDir * (m_fSpeed * 0.5f);
	}
	else if (CBU_KeyManager::GetInstance()->KeyPressing('D'))
	{
		// 오른쪽으로 가려면 윗 방향과 외적
		_vec3 vecXZProjectedLook = CBU_VectorUtil::GetXZProjectedVector(m_tInfo.vLook);
		D3DXVec3Cross(&m_tInfo.vDir, &CBU_Object::DOWNVEC, &vecXZProjectedLook);
		m_tInfo.vPos += m_tInfo.vDir * (m_fSpeed * 0.5f);
	}
	else
	{
		
	}

	// 월드 변환 행렬 업데이트
	_matrix matScale;
	D3DXMatrixScaling(&matScale, 20.f, 20.f, 20.f);
	_matrix matTrans;
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	_matrix matRot;
	D3DXMatrixRotationZ(&matRot, m_fAngle);

	m_tInfo.matWorld = matScale * matRot * matTrans;

	// 정점 업데이트
	for (size_t idx = 0; idx < m_pVecOriginalVertices.size(); ++idx)
	{
		D3DXVec3TransformCoord(m_pVecRenderVertices.at(idx), m_pVecOriginalVertices.at(idx), &m_tInfo.matWorld);
	}
}

void CBU_Actor::LateUpdate(void) 
{

}

void CBU_Actor::Render(HDC hDC) const 
{
	// 점 기준 원 출력. 대신 거리 비례해서 크기를 조정할 순 없을까?
	// 버텍스 프로세싱은 그런 원리가 아님. 불가능
	RECT rect = {m_tInfo.vPos.x};
	Ellipse(hDC, rect.left, rect.top, rect.right, rect.bottom);
	for (auto pIndices : m_pIndicesList)
	{
		MoveToEx(hDC, m_pVecRenderVertices.at(pIndices->_0)->x, m_pVecRenderVertices.at(pIndices->_0)->y, nullptr);
		LineTo(hDC, m_pVecRenderVertices.at(pIndices->_1)->x, m_pVecRenderVertices.at(pIndices->_1)->y);
		LineTo(hDC, m_pVecRenderVertices.at(pIndices->_2)->x, m_pVecRenderVertices.at(pIndices->_2)->y);
		LineTo(hDC, m_pVecRenderVertices.at(pIndices->_0)->x, m_pVecRenderVertices.at(pIndices->_0)->y);
	}
	
}
