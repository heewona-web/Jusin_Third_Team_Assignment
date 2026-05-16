#pragma once

#include "JW_Define.h"
#include "JW_Obj.h"

class JW_ObjMgr
{
private:
	JW_ObjMgr();
	JW_ObjMgr(const JW_ObjMgr& rhs) = delete;
	JW_ObjMgr& operator=(JW_ObjMgr& rObjMgr) = delete;
	~JW_ObjMgr();

public:
	void AddObj(OBJID eID, JW_Obj* pObj);
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();

public:
	const list<JW_Obj*>& Get_ObjList(OBJID eID) { return m_ObjList[eID]; }

public:
	static JW_ObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new JW_ObjMgr;

		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static JW_ObjMgr* m_pInstance;
	list<JW_Obj*> m_ObjList[OBJ_END];
};