#pragma once

#include "JW_Obj.h"

class JW_Wall : public JW_Obj
{
public:
	JW_Wall();
	virtual ~JW_Wall();

public:
	// JW_Obj을(를) 통해 상속됨
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	float m_fWidth;
	float m_fGapSize;
	float m_fGapY;
};