#pragma once
#include "CBU_Ingredient.h"

class CBU_Patty : public CBU_Ingredient
{
public:
	explicit CBU_Patty();
	~CBU_Patty() override;

	void Initialize(void) override;
};

