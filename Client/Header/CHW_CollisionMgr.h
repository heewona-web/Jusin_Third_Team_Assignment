#pragma once

#include "CHW_ObjMgr.h"


class CHW_CollisionMgr
{
private:
	CHW_CollisionMgr();
	CHW_CollisionMgr(const CHW_CollisionMgr& rhs) = delete;
	CHW_CollisionMgr& operator=(CHW_CollisionMgr& rCollision) = delete;
	~CHW_CollisionMgr();



public:
	void CheckCollision_SAT(HW_OBJ_TYPE TYPE1, HW_OBJ_TYPE TYPE2);
	bool IsCollide_SAT(const CHW_Obj* pObj1, const CHW_Obj* pObj2, _vec3& vOutMTVDir, float &fOutMTVValue);
	void Project(const CHW_Obj* pObj, const D3DXVECTOR3 vAxis, float& fOutMin, float& fOutMax);



public:
	static CHW_CollisionMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CHW_CollisionMgr;
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

	static CHW_CollisionMgr* m_pInstance;
};

