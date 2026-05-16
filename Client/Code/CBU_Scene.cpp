#include "CBU_Scene.h"
#include "CBU_KeyManager.h"
#include "CBU_ObjectManager.h"
#include "CBU_Player.h"

void CBU_Scene::Initialize(void)
{
	CBU_Player* pPlayer = new CBU_Player;
	pPlayer->Initialize();
	CBU_ObjectManager::GetInstance()->AddObject(BU_OBJID::PLAYER, pPlayer);
}

int CBU_Scene::Update(void) 
{
	CBU_ObjectManager::GetInstance()->Update();
	CBU_KeyManager::GetInstance()->Update();
	//RECT rectWindow = {};
	//GetClientRect(g_hWnd, &rectWindow);
	//ClientToScreen(g_hWnd, (LPPOINT)&rectWindow.left);
	//ClientToScreen(g_hWnd, (LPPOINT)&rectWindow.right);
	//SetCursorPos((rectWindow.right + rectWindow.left) / 2, (rectWindow.bottom + rectWindow.top) / 2);
	return 0;
}

void CBU_Scene::Late_Update(void) 
{
	CBU_ObjectManager::GetInstance()->LateUpdate();
}

void CBU_Scene::Render(HDC hDC) 
{
	CBU_ObjectManager::GetInstance()->Render(hDC);
}

void CBU_Scene::Release(void) 
{
	CBU_ObjectManager::DestroyInstance();
	CBU_KeyManager::DestroyInstance();
}
