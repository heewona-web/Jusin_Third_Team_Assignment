#pragma once

#include "JW_Obj.h"

class JW_Player : public JW_Obj
{
public:
	JW_Player();
	virtual ~JW_Player();

public:
	// JW_Obj을(를) 통해 상속됨
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void Key_Input();

private:
	void Jump();
	void Body_Rotate();

protected:
	D3DXVECTOR3 vBodyVertex[5];
	D3DXVECTOR3 vLocalBodyVertex[5];

	float m_fBodyLength;
	float m_fBeakLength;
	float m_fRotateSpeed;

	float m_fAngle;
	float m_fMaxAngle;
	float m_fMinAngle;

	bool m_bJump;
	float m_fJumpPower;
	float m_fGravity;
	float m_fMaxFallSpeed;
};