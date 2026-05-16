#include "CBU_Spawner.h"
#include "CBU_Ingredient.h"

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
	m_vecScale = { 5.f, 5.f, 5.f };
	// 위치 정보 초기화
	m_tInfo.vPos = {float(WINCX)/2.f, 50.f, 0.f};
	m_tInfo.vDir = { -1.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, 0.f, 1.f };

	// 버텍스 정보 초기화
	m_vecOriginalVertices.push_back({ -1.f, -0.5f, 0.f }); // 0
	m_vecOriginalVertices.push_back({ 1.f, -0.5f, 0.f }); // 1
	m_vecOriginalVertices.push_back({ 1.f, 0.5f, 0.f }); // 2
	m_vecOriginalVertices.push_back({ -1.f, 0.5f, 0.f }); // 3

	// 렌더 정보 버텍스에 같은 크기만큼 복사
	for (size_t idx = 0; idx < m_vecOriginalVertices.size(); ++idx)
	{
		m_vecRenderVertices.push_back({ 0.f, 0.f, 0.f });
	}

	// 인덱스 정보 초기화
	m_pIndicesList.push_back(new INDEX32({ 0, 1, 2 }));
	m_pIndicesList.push_back(new INDEX32({ 2, 3, 0 }));

	m_fSpeed = 10.f;

	// 스폰 정보 초기화
	m_ullSpawnCoolTime = 10;
	m_ullLastSpawnTime = 0;
}

void CBU_Spawner::LateUpdate(void)
{
	if (m_tInfo.vPos.x < 0.f || m_tInfo.vPos.x > float(WINCX))
	{
		m_tInfo.vDir.x *= -1.f;
	}

	//ULONGLONG ullCurrentTime = GetTickCount64();
	if (m_ullLastSpawnTime <= 0)
	{
		CBU_Ingredient* pIngredient = new CBU_Ingredient;
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
