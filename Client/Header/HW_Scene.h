#pragma once
#include "CScene.h"



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


//private:
//    CHW_Obj* m_pBall;
//    CHW_Obj* m_pStick;

private:
    int			m_iFPS;
    TCHAR		m_szFPS[32];
    DWORD		m_dwTime;
};

