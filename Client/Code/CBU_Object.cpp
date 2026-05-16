#include "CBU_Object.h"

const _vec3 CBU_Object::UPVEC = { 0.f, -1.f, 0.f };
const _vec3 CBU_Object::DOWNVEC = { 0.f, 1.f, 0.f };

void CBU_Object::Free(void)
{
	for (auto iter = m_pVecOriginalVertices.begin(); iter != m_pVecOriginalVertices.end();)
	{
		if (*iter != nullptr)
		{
			delete* iter;
			iter = m_pVecOriginalVertices.erase(iter);
		}
	}
	m_pVecOriginalVertices.clear();
	for (auto iter = m_pVecRenderVertices.begin(); iter != m_pVecRenderVertices.end();)
	{
		if (*iter != nullptr)
		{
			delete* iter;
			iter = m_pVecRenderVertices.erase(iter);
		}
	}
	m_pVecRenderVertices.clear();
	for (auto iter = m_pIndicesList.begin(); iter != m_pIndicesList.end();)
	{
		if (*iter != nullptr)
		{
			delete* iter;
			iter = m_pIndicesList.erase(iter);
		}
	}
	Safe_Release(m_pParentObject);
}
