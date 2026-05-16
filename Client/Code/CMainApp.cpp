#include "pch.h"
#include "CMainApp.h"

#include "CSceneMgr.h"
#include "CHW_BmpMgr.h"

CMainApp::CMainApp()
{
}

CMainApp::~CMainApp()
{
}

HRESULT CMainApp::Ready_MainApp()
{
	if (FAILED(CGraphicDev::GetInstance()->Ready_GraphicDev(g_hWnd, MODE_WIN, WINCX, WINCY, &m_pDeviceClass)))
		return E_FAIL;

	//return E_FAIL;
	CSceneMgr::Get_Instance()->SetScene(JW_SCENE);
	return S_OK;
}

int CMainApp::Update_MainApp(const _float& fTimeDelta)
{
	CSceneMgr::Get_Instance()->Update();
	return 0;
}

void CMainApp::LateUpdate_MainApp(const _float& fTimeDelta)
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainApp::Render_MainApp()
{
	//m_pDeviceClass->Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));

	HDC m_hDC = GetDC(g_hWnd);

	HDC m_BackDC = CHW_BmpMgr::Get_Instance()->Find_Image(L"Back");
	Rectangle(m_BackDC, 0, 0, WINCX, WINCY);

	CSceneMgr::Get_Instance()->Render(m_BackDC);
	BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_BackDC, 0, 0, SRCCOPY);

	//m_pDeviceClass->Render_End();
}

CMainApp* CMainApp::Create()
{
	CMainApp* pMainApp = new CMainApp;

	if (FAILED(pMainApp->Ready_MainApp()))
	{
		delete pMainApp;
		pMainApp = nullptr;
	}

	return pMainApp;
}

void CMainApp::Free()
{
	m_pDeviceClass->DestroyInstance();
}
