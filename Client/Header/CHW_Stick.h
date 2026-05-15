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
};

