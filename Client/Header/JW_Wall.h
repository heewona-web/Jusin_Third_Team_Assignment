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

public:
	void Set_Player_Pass() { m_bPlayerPass = true; }

public:
	const float Get_Width() const { return m_fWidth; }
	const float Get_GapSize() const { return m_fGapSize; }
	const float Get_GapY() const { return m_fGapY; }
	const bool Get_Player_Pass() const { return m_bPlayerPass; }

private:
	float m_fWidth;
	float m_fGapSize;
	float m_fGapY;

	bool m_bPlayerPass;
};