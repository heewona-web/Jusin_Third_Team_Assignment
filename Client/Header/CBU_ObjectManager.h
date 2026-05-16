#pragma once
#include "Engine_Define.h"
#include "BU_Define.h"
#include "CBU_Object.h"

class CBU_ObjectManager
{
private:
	CBU_ObjectManager() {}
	~CBU_ObjectManager() { Release(); }
	DECLARE_SINGLETON(CBU_ObjectManager)

public:
	void Update(void);
	void LateUpdate(void);
	void Render(HDC hDC) const;
	void Release(void);

	void AddObject(BU_OBJID eObjId, CBU_Object* pObj);
	const vector<CBU_Object*>& GetObjectVector(BU_OBJID eObjId) const;

private:
	vector<CBU_Object*> m_vecObject[BU_OBJID::OBJEND];

};

