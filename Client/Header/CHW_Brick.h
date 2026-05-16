#pragma once
#include "CHW_Obj.h"
class CHW_Brick :
    public CHW_Obj
{
public:
    CHW_Brick();
    CHW_Brick(float fX, float fY);
    ~CHW_Brick();
public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    _vec3 m_vOriginScale;	// Å©±â
};

