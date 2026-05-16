#pragma once
#include "CBU_Ingredient.h"

class CBU_Tomato : public CBU_Ingredient
{
public:
	CBU_Tomato();
	~CBU_Tomato() override;

	void Initialize(void) override;
};

