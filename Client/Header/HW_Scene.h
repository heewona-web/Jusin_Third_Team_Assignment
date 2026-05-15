#pragma once
#include "CScene.h"
class HW_Scene :
    public CScene
{
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

