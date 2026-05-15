#pragma once
#include "CHW_Obj.h"


enum OBJ_TYPE { OBJ_BALL, OBJ_WALL , OBJ_STICK, OBJ_END };


class CHW_ObjMgr
{
private:
	CHW_ObjMgr();
	CHW_ObjMgr(const CHW_ObjMgr& rhs) = delete;
	CHW_ObjMgr& operator=(CHW_ObjMgr& rObj) = delete;
	~CHW_ObjMgr();



public:
	void AddObject(OBJ_TYPE eID, CHW_Obj* pObj);
	void Update();
	void LateUpdate();
	void Render(HDC hDC);
	void Release();


public:
	static CHW_ObjMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CHW_ObjMgr;
		}

		return m_pInstance;
	}
	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	list<CHW_Obj*>			m_ObjList[OBJ_END];

	static CHW_ObjMgr* m_pInstance;

};

