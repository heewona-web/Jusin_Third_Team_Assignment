#pragma once

#include "Define.h"

class JW_Obj
{
public:
	JW_Obj();
	virtual ~JW_Obj();

public:
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

protected:
	tagInfo m_tInfo;

	float m_fSpeed;
};