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
void CHW_ObjMgr::AddObject(HW_OBJ_TYPE eID, CHW_Obj* pObj)
{
	if (eID > HW_OBJ_END || pObj == nullptr) return;

	m_ObjList[eID].push_back(pObj);

}
void CHW_ObjMgr::Update()
{
	for (size_t i = 0; i < HW_OBJ_END; ++i)
	{
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); )
		{
			

			int iResult = (*iter)->Update();
			if (-1 == iResult) {
				Safe_Delete<CHW_Obj*>(*iter);
				iter = m_ObjList[i].erase(iter);
				continue;
			}
			else
				++iter;
		}
	}
}
void CHW_ObjMgr::LateUpdate()
{
	for (size_t i = 0; i < HW_OBJ_END; ++i)
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
	for (size_t i = 0; i < HW_OBJ_END; ++i)
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
	for (size_t i = 0; i < HW_OBJ_END; ++i) {
		for (auto iter = m_ObjList[i].begin(); iter != m_ObjList[i].end();) {

			if (*iter != nullptr) {
				delete* iter;
				iter = m_ObjList[i].erase(iter);

			}
			else {
				++iter;
			}

		}
		m_ObjList[i].clear();
	}

}