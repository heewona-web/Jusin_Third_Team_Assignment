#include "pch.h"
#include "JW_ObjMgr.h"

JW_ObjMgr* JW_ObjMgr::m_pInstance = nullptr;

JW_ObjMgr::JW_ObjMgr()
{

}

JW_ObjMgr::~JW_ObjMgr()
{
	Release();
}

void JW_ObjMgr::AddObj(OBJID eID, JW_Obj* pObj)
{
	if (eID > OBJ_END || !pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

void JW_ObjMgr::Update()
{
	for (int i = 0; i < OBJ_END; ++i) {
		for (auto& pObj : m_ObjList[i]) {
			pObj->Update();
		}
	}
}

void JW_ObjMgr::LateUpdate()
{
	for (int i = 0; i < OBJ_END; ++i) {
		for (auto& pObj : m_ObjList[i]) {
			pObj->LateUpdate();
		}
	}
}

void JW_ObjMgr::Render(HDC hDC)
{
	for (int i = 0; i < OBJ_END; ++i) {
		for (auto& pObj : m_ObjList[i]) {
			pObj->Render(hDC);
		}
	}
}

void JW_ObjMgr::Release()
{
	for (int i = 0; i < OBJ_END; ++i) {
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), DeleteObj());
		m_ObjList[i].clear();
	}
}