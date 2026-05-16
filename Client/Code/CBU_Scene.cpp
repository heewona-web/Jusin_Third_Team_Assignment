#include "CBU_Scene.h"
#include "CBU_KeyManager.h"
#include "CBU_ObjectManager.h"
#include "CBU_CollisionUtil.h"
#include "CBU_Player.h"
#include "CBU_Spawner.h"

void CBU_Scene::Initialize(void)
{
	CBU_Player* pPlayer = new CBU_Player;
	pPlayer->Initialize();
	CBU_ObjectManager::GetInstance()->AddObject(BU_OBJID::PLAYER, pPlayer);

	CBU_Spawner* pSpawner = new CBU_Spawner;
	pSpawner->Initialize();
	CBU_ObjectManager::GetInstance()->AddObject(BU_OBJID::SPAWNER, pSpawner);

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
	for (auto pPlayer : CBU_ObjectManager::GetInstance()->GetObjectVector(BU_OBJID::PLAYER))
	{
		for (auto pIngredient : CBU_ObjectManager::GetInstance()->GetObjectVector(BU_OBJID::INGREDIENT))
		{
			if (CBU_CollisionUtil::CheckObjAndObj(pPlayer, pIngredient))
			{
				pPlayer->OnCollision(pIngredient);
				pIngredient->OnCollision(pPlayer);
			}
		}
	}
	for (auto pSrcIngredient : CBU_ObjectManager::GetInstance()->GetObjectVector(BU_OBJID::INGREDIENT))
	{
		// 부모 오브젝트가 있는 녀석들만 충돌 검사
		if (pSrcIngredient->GetParentObjectP())
		{
			for (auto pDstIngredient : CBU_ObjectManager::GetInstance()->GetObjectVector(BU_OBJID::INGREDIENT))
			{
				if (!pDstIngredient->GetParentObjectP() & CBU_CollisionUtil::CheckObjAndObj(pSrcIngredient, pDstIngredient))
				{
					pSrcIngredient->OnCollision(pDstIngredient);
					pDstIngredient->OnCollision(pSrcIngredient);
				}
			}
		}
	}

	// 사망 오브젝트 회수
	CBU_ObjectManager::GetInstance()->DeleteDeadObj();
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
