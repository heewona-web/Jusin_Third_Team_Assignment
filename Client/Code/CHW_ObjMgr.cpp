#include "pch.h"
#include "CHW_ObjMgr.h"

CHW_ObjMgr* CHW_ObjMgr::m_pInstance = nullptr;

CHW_ObjMgr::CHW_ObjMgr()
{
}

CHW_ObjMgr::~CHW_ObjMgr()
{
	Release();
}
void CHW_ObjMgr::AddObject(OBJ_TYPE eID, CHW_Obj* pObj)
{
	if (eID > OBJ_END || pObj == nullptr) return;

	m_ObjList[eID].push_back(pObj);

}
void CHW_ObjMgr::Update()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); )
		{
			(*iter)->Update();
			++iter;
		}
	}
}
void CHW_ObjMgr::LateUpdate()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); )
		{
			(*iter)->LateUpdate();
			++iter;
		}
	}
}

void CHW_ObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); )
		{
			(*iter)->Render(hDC);
			++iter;
		}
	}
}
void CHW_ObjMgr::Release()
{
	//for (size_t i = 0; i < OBJ_END; ++i) {
	//	for (size_t j = 0; j < m_ObjList[i].size(); ++j) {

	//	}
	//	m_ObjList[i].clear();
	//}

}