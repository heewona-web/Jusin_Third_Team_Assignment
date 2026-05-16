#include "CBU_Ingredient.h"

CBU_Ingredient::CBU_Ingredient() : CBU_Object(BU_OBJID::INGREDIENT)
{

}

CBU_Ingredient::~CBU_Ingredient()
{

}

void CBU_Ingredient::Initialize(void)
{
	// 크기 정보 초기화
	m_vecScale = { 10.f, 10.f, 10.f };
	// 위치 정보 초기화
	m_tInfo.vPos = { float(WINCX) / 2.f, 50.f, 0.f };
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
	ToggleGravity();
}

void CBU_Ingredient::LateUpdate(void)
{
}

void CBU_Ingredient::Render(HDC hDC) const
{
	CBU_Object::Render(hDC);
}

void CBU_Ingredient::OnCollision(CBU_Object* pObj)
{
	// 부모객체 미소유 시에만 충돌 처리
	if (!m_pParentObject)
	{
		switch (pObj->GetObjType())
		{
		// 플레이어와 충돌하면 m_pParentObject를 플레이어 포인터로
		case BU_OBJID::PLAYER:
		{
			m_pParentObject = pObj;
			pObj->AddRef();
		}
		break;
		// 재료와 충돌하면 재료가 가진 m_pParentObject값으로 지정해줘야함.
		case BU_OBJID::INGREDIENT:
		{
			if (pObj->GetParentObjectP())
			{
				m_pParentObject = pObj->GetParentObjectP();
				pObj->GetParentObjectP()->AddRef();
			}
		}
		break;
		default:
			break;
		}

		// 충돌했을 때 Pos 값을 m_pParentObject에서의 상대값으로 업데이트 해줘야함
		m_tInfo.vPos = m_tInfo.vPos - m_pParentObject->GetInfo().vPos;

		// 자전 값은 유지

		// 중력 영향 안받게 됨
		ToggleGravity();
	}
}
