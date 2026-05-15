#pragma once
#include "CScene.h"

#include "CHW_Obj.h"
#include "CHW_BmpMgr.h"

class HW_Scene :
    public CScene
{
public:
    HW_Scene();
    ~HW_Scene();
public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;


private:
    CHW_Obj* m_pBall;
};

