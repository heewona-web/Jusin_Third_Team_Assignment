#pragma once

#include "Define.h"

class JW_Obj
{
public:
	JW_Obj();
	virtual ~JW_Obj();

public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

public:
	void Set_PosX(float _x) { m_tInfo.vPos.x = _x; }

protected:
	tagInfo m_tInfo;

	float m_fSpeed;
};