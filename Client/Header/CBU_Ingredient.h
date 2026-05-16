#pragma once
#include "CBU_Object.h"

class CBU_Ingredient : public CBU_Object
{
public:
	explicit CBU_Ingredient();
	~CBU_Ingredient() override;

	void Initialize(void) override;
	//void Update(void) override;
	void LateUpdate(void) override;
	void Render(HDC hDC) const override;
	//void Free(void) override;

	void OnCollision(CBU_Object* pObj) override;
};

