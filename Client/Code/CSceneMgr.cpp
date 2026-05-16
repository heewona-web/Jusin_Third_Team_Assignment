#include "pch.h"
#include "CSceneMgr.h"
#include "CBU_Scene.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr() : m_pScene(nullptr), m_eCurScene(LOGO), m_ePreScene(LOGO)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::SetScene(SCENEID eID)
{
	m_eCurScene = eID;

	if (m_ePreScene != m_eCurScene)
	{
		Safe_Delete(m_pScene);

		switch (m_eCurScene)
		{
		case LOGO:
			//m_pScene = new CLogo;
			break;

		case HW_SCENE:
			m_pScene = new HW_Scene;
			break;

		case BU_SCENE:
			m_pScene = new CBU_Scene;
			break;

		case TG_SCENE:
			//m_pScene = new TG_Scene;
			break;

		case JW_SCENE:
			//m_pScene = new JW_Scene;
			break;
		}

		m_pScene->Initialize();

		m_ePreScene = m_eCurScene;
	}
}

int CSceneMgr::Update()
{
	m_pScene->Update();

	return 0;
}

void CSceneMgr::Late_Update()
{
	m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);
}

void CSceneMgr::Release()
{
	m_pScene->Release();
	Safe_Delete<CScene*>(m_pScene);
}
