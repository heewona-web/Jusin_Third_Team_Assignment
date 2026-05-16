#pragma once
#include "CScene.h"

class CBU_Scene : public CScene
{
public:
	void Initialize(void) override;
	int Update(void) override;
	void Late_Update(void) override;
	void Render(HDC hDC) override;
	void Release(void) override;
};

