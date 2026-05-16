#include "pch.h"
#include "CHW_BmpMgr.h"

CHW_BmpMgr* CHW_BmpMgr::m_pInstance = nullptr;

CHW_BmpMgr::CHW_BmpMgr()
{
}

CHW_BmpMgr::~CHW_BmpMgr()
{
	Release();
}

void CHW_BmpMgr::Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), Engine::CTag_Finder(pImgKey));

	if (iter == m_mapBit.end())
	{
		CHW_MyBmp* pBmp = new CHW_MyBmp;

		pBmp->Load_Bmp(pFilePath);

		m_mapBit.insert({ pImgKey, pBmp });
	}

}

HDC CHW_BmpMgr::Find_Image(const TCHAR* pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), Engine::CTag_Finder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->Get_MemDC();
}

void CHW_BmpMgr::Release()
{
	for_each(m_mapBit.begin(), m_mapBit.end(), Engine::CDeleteMap());
	m_mapBit.clear();
}
