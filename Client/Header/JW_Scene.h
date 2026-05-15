#pragma once

#include "CScene.h"
#include "JW_Obj.h"

class JW_Scene : public CScene
{
public:
    JW_Scene();
    virtual ~JW_Scene();

public:
    // CScene을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    JW_Obj* m_pPlayer;
};