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
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

protected:
	D3DXVECTOR3 vBodyVertex[5];

	float m_fBodyLength;
	float m_fBeakLength;
};