#pragma once
#include "CBU_Ingredient.h"

class CBU_Letuce : public CBU_Ingredient
{
public:
	explicit CBU_Letuce();
	~CBU_Letuce() override;

	void Initialize(void) override;
};

