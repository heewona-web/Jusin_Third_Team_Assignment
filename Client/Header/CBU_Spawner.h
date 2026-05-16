#pragma once
#include "CBU_Object.h"

class CBU_Spawner : public CBU_Object
{
public:
	explicit CBU_Spawner();
	~CBU_Spawner() override;

	void Initialize(void) override;
	//void Update(void) override;
	void LateUpdate(void) override;
	//void Render(HDC hDC) const override;
	//void Free(void) override;

	void OnCollision(CBU_Object* pObj) override {}

private:
	ULONGLONG m_ullSpawnCoolTime; // 스폰 간격
	ULONGLONG m_ullLastSpawnTime; // 최종 스폰 시간
};

