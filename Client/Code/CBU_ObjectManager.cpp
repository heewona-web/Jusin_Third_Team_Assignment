#include "CBU_ObjectManager.h"

IMPLEMENT_SINGLETON(CBU_ObjectManager)

void CBU_ObjectManager::AddObject(BU_OBJID eObjId, CBU_Object* pObj)
{
	if (pObj != nullptr && eObjId < BU_OBJID::OBJEND)
	{
		m_vecObject[eObjId].push_back(pObj);
	}
}

const vector<CBU_Object*>& CBU_ObjectManager::GetObjectVector(BU_OBJID eObjId) const
{
	if (eObjId < BU_OBJID::OBJEND)
	{
		return m_vecObject[eObjId];
	}
	else
	{
		return m_vecObject[BU_OBJID::OBJEND];
	}
}

void CBU_ObjectManager::Update(void)
{
	for (int eObjId = 0; eObjId < BU_OBJID::OBJEND; ++eObjId)
	{
		for (auto& pObj : m_vecObject[eObjId])
		{
			pObj->Update();
		}
	}
}

void CBU_ObjectManager::LateUpdate(void)
{
	for (int eObjId = 0; eObjId < BU_OBJID::OBJEND; ++eObjId)
	{
		for (auto& pObj : m_vecObject[eObjId])
		{
			pObj->LateUpdate();
		}
	}
}

void CBU_ObjectManager::Render(HDC hDC) const
{
	for (int eObjId = 0; eObjId < BU_OBJID::OBJEND; ++eObjId)
	{
		for (auto& pObj : m_vecObject[eObjId])
		{
			pObj->Render(hDC);
		}
	}
}

void CBU_ObjectManager::Release(void)
{
	for (int eObjId = 0; eObjId < BU_OBJID::OBJEND; ++eObjId)
	{
		for (auto iter = m_vecObject[eObjId].begin(); iter != m_vecObject[eObjId].end();)
		{
			if (*iter != nullptr)
			{
				Safe_Release(*iter);
				iter = m_vecObject[eObjId].erase(iter);
			}
		}
	}
}

void CBU_ObjectManager::DeleteDeadObj(void)
{
	for (int i = 0; i < static_cast<int>(BU_OBJID::OBJEND); ++i)
	{
		//if (i == static_cast<int>(OBJID::PLAYER))
		//	continue;
		for (auto iter = m_vecObject[i].begin(); iter != m_vecObject[i].end();)
		{
			if ((*iter)->IsDead())
			{
				Safe_Release(*iter);
				iter = m_vecObject[i].erase(iter);
			}
			else
				++iter;
		}
	}
}