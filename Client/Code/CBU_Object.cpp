#include "CBU_Object.h"

const _vec3 CBU_Object::UPVEC = { 0.f, -1.f, 0.f };
const _vec3 CBU_Object::DOWNVEC = { 0.f, 1.f, 0.f };
const float CBU_Object::MAX_GRAVITY = 10.f;
/**
 * 기본 크자이 까지만 계산하는 업데이트.
 * 
 */
void CBU_Object::Update(void)
{
	// 위치 업데이트
	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	// 중력 적용
	if (m_bAffectGravity)
	{
		UpdateGravity();
	}
	// 연결 된 상태. 중력을 받지 않고 현 위치에서 플레이어 기준으로 공전과 이동만 함
	// 자전값에는 공전값을 추가함
	if (m_pParentObject)
	{
		_matrix matScale;
		D3DXMatrixScaling(&matScale, m_vecScale.x, m_vecScale.y, m_vecScale.z);
		_matrix matRot;
		D3DXMatrixRotationZ(&matRot, m_fAngle);
		_matrix matTrans;
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
		_matrix matOrbit;
		D3DXMatrixRotationZ(&matOrbit, m_fOrbitOffset + m_pParentObject->GetAngle());
		_matrix matParent;
		D3DXMatrixTranslation(&matParent, m_pParentObject->GetInfo().vPos.x, m_pParentObject->GetInfo().vPos.y, m_pParentObject->GetInfo().vPos.z);

		m_tInfo.matWorld = matScale * matRot * matTrans * matOrbit * matParent;
	}
	// 연결이 안 된 상태. 중력을 받아 떨어짐
	else
	{
		// 크자이 까지만 업데이트
		_matrix matScale;
		D3DXMatrixScaling(&matScale, m_vecScale.x, m_vecScale.y, m_vecScale.z);
		_matrix matTrans;
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
		_matrix matRot;
		D3DXMatrixRotationZ(&matRot, m_fAngle);

		m_tInfo.matWorld = matScale * matRot * matTrans;
	}
	// m_pParentObject의 Angle 값으로 공전, 위치 값으로 이동을 추가해야함
	// 충돌 당시 위치를 Pos로 고정 (중력 안받음)

	// 정점 업데이트
	// 개선 필요
	//for (size_t idx = 0; idx < m_vecOriginalVertices.size(); ++idx)
	//{
	//	D3DXVec3TransformCoord(m_vecRenderVertices.at(idx), m_vecOriginalVertices.at(idx), &m_tInfo.matWorld);

	//}
	// 배열 연산으로 개선
	D3DXVec3TransformCoordArray(m_vecRenderVertices.data(), sizeof(_vec3), m_vecOriginalVertices.data(), sizeof(_vec3), &m_tInfo.matWorld, m_vecOriginalVertices.size());
}
void CBU_Object::Render(HDC hDC) const
{
	for (auto pIndices : m_pIndicesList)
	{
		MoveToEx(hDC, LONG(m_vecRenderVertices.at(pIndices->_0).x), LONG(m_vecRenderVertices.at(pIndices->_0).y), nullptr);
		LineTo(hDC, LONG(m_vecRenderVertices.at(pIndices->_1).x), LONG(m_vecRenderVertices.at(pIndices->_1).y));
		LineTo(hDC, LONG(m_vecRenderVertices.at(pIndices->_2).x), LONG(m_vecRenderVertices.at(pIndices->_2).y));
		LineTo(hDC, LONG(m_vecRenderVertices.at(pIndices->_0).x), LONG(m_vecRenderVertices.at(pIndices->_0).y));
	}
}
void CBU_Object::Free(void)
{
	for (auto iter = m_pIndicesList.begin(); iter != m_pIndicesList.end();)
	{
		if (*iter != nullptr)
		{
			delete* iter;
			iter = m_pIndicesList.erase(iter);
		}
	}

	Safe_Release(m_pParentObject);
}

void CBU_Object::UpdateGravity(void)
{
	if (m_fGravitySpeed < MAX_GRAVITY)
	{
		m_fGravitySpeed = min(MAX_GRAVITY, m_fGravitySpeed + 4.9f * powf(float(GetTickCount64() - m_ullFallingStartTime) / 1000.f, 2.f));
	}
	m_tInfo.vPos.y += m_fGravitySpeed;
}
