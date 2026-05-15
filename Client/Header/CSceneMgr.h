#pragma once
#pragma once
#include "Define.h"
#include "HW_Scene.h"
#include "JW_Scene.h"
//#include "BU_Scene.h"
//#include "TG_Scene.h"
//#include "JW_Scene.h"

class CSceneMgr
{
private:
	CSceneMgr();
	CSceneMgr(const CSceneMgr& rhs) = delete;
	CSceneMgr operator=(CSceneMgr& rSceneMgr) = delete;
	~CSceneMgr();

public:
	void SetScene(SCENEID eID);
	int	 Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

public:
	SCENEID		Get_SceneID() { return m_eCurScene; }

public:
	static CSceneMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CSceneMgr;
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
	static CSceneMgr* m_pInstance;
	CScene* m_pScene;

	SCENEID	m_eCurScene;
	SCENEID m_ePreScene;

};



