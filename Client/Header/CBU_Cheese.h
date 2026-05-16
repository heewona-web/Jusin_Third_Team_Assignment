#pragma once
#include "CBU_Ingredient.h"

class CBU_Cheese : public CBU_Ingredient
{
public:
	CBU_Cheese();
	~CBU_Cheese() override;

	void Initialize(void) override;
};

