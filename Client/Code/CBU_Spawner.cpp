#include "CBU_Spawner.h"
#include "CBU_Ingredient.h"
#include "CBU_Patty.h"
#include "CBU_Letuce.h"
#include "CBU_Cheese.h"
#include "CBU_Tomato.h"

#include "CBU_ObjectManager.h"

CBU_Spawner::CBU_Spawner() : CBU_Object(BU_OBJID::SPAWNER), m_ullSpawnCoolTime(0), m_ullLastSpawnTime(0)
{

}

CBU_Spawner::~CBU_Spawner()
{

}

void CBU_Spawner::Initialize(void)
{
	// 크기 정보 초기화
	m_vecScale = { 50.f, 20.f, 50.f };
	// 위치 정보 초기화
	m_tInfo.vPos = {float(WINCX)/2.f, 50.f, 0.f};
	m_tInfo.vDir = { -1.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, 0.f, 1.f };

	// 버텍스 정보 초기화
	// 넓적한 팔각기둥인데 위가 작음
	m_vecOriginalVertices.push_back({ -1.0452f, -0.5f, 0.f }); // 0
	m_vecOriginalVertices.push_back({ -0.739068f, -0.5f, 0.739068f }); // 1
	m_vecOriginalVertices.push_back({ 0.f, -0.5f, 1.0452f }); // 2
	m_vecOriginalVertices.push_back({ 0.739068f, -0.5f, 0.739068f }); // 3
	m_vecOriginalVertices.push_back({ 1.0452f, -0.5f, 0.f }); // 4
	m_vecOriginalVertices.push_back({ 0.739068f, -0.5f, -0.739068f }); // 5
	m_vecOriginalVertices.push_back({ 0.f, -0.5f, -1.0452f }); // 6
	m_vecOriginalVertices.push_back({ -0.739068f, -0.5f, -0.739068f }); // 7
	m_vecOriginalVertices.push_back({ -0.f, -0.5f, -0.f }); // 8 중심
	
	m_vecOriginalVertices.push_back({ -1.3065f, 0.5f, 0.f }); // 0
	m_vecOriginalVertices.push_back({ -0.923835f, 0.5f, 0.923835f }); // 1
	m_vecOriginalVertices.push_back({ 0.f, 0.5f, 1.3065f }); // 2
	m_vecOriginalVertices.push_back({ 0.923835f, 0.5f, 0.923835f }); // 3
	m_vecOriginalVertices.push_back({ 1.3065f, 0.5f, 0.f }); // 4
	m_vecOriginalVertices.push_back({ 0.923835f, 0.5f, -0.923835f }); // 5
	m_vecOriginalVertices.push_back({ 0.f, 0.5f, -1.3065f }); // 6
	m_vecOriginalVertices.push_back({ -0.923835f, 0.5f, -0.923835f }); // 7
	m_vecOriginalVertices.push_back({ -0.f, 0.5f, -0.f }); // 8 중심

	// 렌더 정보 버텍스에 같은 크기만큼 복사
	for (size_t idx = 0; idx < m_vecOriginalVertices.size(); ++idx)
	{
		m_vecRenderVertices.push_back({ 0.f, 0.f, 0.f });
	}

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

	// 스폰 정보 초기화
	m_ullSpawnCoolTime = 100;
	m_ullLastSpawnTime = 0;

	srand(time(NULL));
}

void CBU_Spawner::LateUpdate(void)
{
	if ((m_tInfo.vPos.x < 0.f || m_tInfo.vPos.x > float(WINCX)) && !m_pParentObject)
	{
		m_tInfo.vDir.x *= -1.f;
	}

	//ULONGLONG ullCurrentTime = GetTickCount64();
	if (m_ullLastSpawnTime <= 0 && !m_pParentObject)
	{
		int iRandom = rand() % 100;
		CBU_Ingredient* pIngredient = nullptr;
		if (iRandom < 33)
		{
			// 33%확률로 패티
			pIngredient = new CBU_Patty;
		}
		else if (iRandom < 66)
		{
			// 33%확률로 치즈
			pIngredient = new CBU_Cheese;
		}
		else if (iRandom < 100)
		{
			// 34%확률로 토마토
			pIngredient = new CBU_Tomato;
		}
		//else if (iRandom < 100)
		//{
		//	// 20%확률로 양상추
		//	pIngredient = new CBU_Letuce;
		//}
		pIngredient->Initialize();
		pIngredient->SetPos({ m_tInfo.vPos.x, m_tInfo.vPos.y + m_vecScale.y, m_tInfo.vPos.z });
		CBU_ObjectManager::GetInstance()->AddObject(BU_OBJID::INGREDIENT, pIngredient);
		// 최종 스폰시간 최신화
		m_ullLastSpawnTime = m_ullSpawnCoolTime;
	}
	else
	{
		--m_ullLastSpawnTime;
	}
}

void CBU_Spawner::OnCollision(CBU_Object* pObj)
{
	// 종료 1회 처리하기 위해 parentObject에 등록
	if (pObj->GetObjType() == BU_OBJID::INGREDIENT && !m_pParentObject)
	{
		m_pParentObject = pObj->GetParentObjectP();
		pObj->GetParentObjectP()->AddRef();

		// 충돌했을 때 Pos 값을 m_pParentObject에서의 상대값으로 업데이트 해줘야함
		m_tInfo.vPos = m_tInfo.vPos - m_pParentObject->GetInfo().vPos;

		// 크자이 값을 고정하여 저장
		_matrix matScale;
		D3DXMatrixScaling(&matScale, m_vecScale.x, m_vecScale.y, m_vecScale.z);
		_matrix matRot;
		D3DXMatrixRotationZ(&matRot, m_fAngle);
		_matrix matTrans;
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
		m_matFixed = matScale * matRot * matTrans;

		// 공전 값을 현재 각도의 -만큼으로 저장해둬야 회전 오차가 사라짐
		m_fOrbitOffset = -m_pParentObject->GetAngle();
		m_fOrbitOffsetX = -m_pParentObject->GetAngleX();

		// 스폰 종료 처리 추가(혹시 모르니)
		m_ullLastSpawnTime = -1;
	}
}
