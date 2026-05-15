#pragma once
#include "Define.h"
class CHW_Obj
{
public:
	CHW_Obj();
	virtual ~CHW_Obj() {};

public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

protected:
	_INFO m_tInfo;
};

