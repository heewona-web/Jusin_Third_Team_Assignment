#pragma once
#include "CHW_Obj.h"
class CHW_Stick :
    public CHW_Obj
{
public:
    CHW_Stick();
    ~CHW_Stick();
public:
    void Initialize() override;
    void Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    void KeyInput();
public:
    _vec3 m_vOriginScale;	// 크기

    float m_fCurAngle; //라이안 값
    const float m_fRotAngle = 0.3f;
    float m_fSpeed;
};

