#pragma once
#include "CBase.h"
#include "Define.h"

class CBU_Object : public CBase
{
public:
	explicit CBU_Object() {}
	virtual ~CBU_Object() {}

	virtual void Initialize(void) PURE;
	virtual void Update(void) PURE;
	virtual void LateUpdate(void) PURE;
	virtual void Render(HDC hDC) const PURE;
	virtual void Release(void) PURE;

protected:
	INFO m_tInfo;
};

