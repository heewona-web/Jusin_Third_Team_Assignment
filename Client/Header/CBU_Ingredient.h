#pragma once
#include "CBU_Object.h"

class CBU_Ingredient : public CBU_Object
{
public:
	explicit CBU_Ingredient();
	~CBU_Ingredient() override;

	void Initialize(void) override;
};

