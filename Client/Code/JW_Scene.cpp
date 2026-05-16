#include "pch.h"
#include "JW_Scene.h"
#include "JW_Player.h"
#include "JW_Wall.h"
#include "JW_AbstractFactory.h"
#include "JW_ObjMgr.h"

JW_Scene::JW_Scene():m_pPlayer(nullptr)
{

}

JW_Scene::~JW_Scene()
{
	Release();
}

void JW_Scene::Initialize()
{
	srand((unsigned)time(NULL));

	if (!m_pPlayer) {
		m_pPlayer = new JW_Player;
		m_pPlayer->Initialize();
	}

	for (int i = 0; i < 3; ++i) {
		JW_ObjMgr::Get_Instance()->AddObj(OBJ_WALL, JW_AbstractFactory<JW_Wall>::Create_Obj(WINCX + (i * 300.f)));
	}
}

int JW_Scene::Update()
{
	m_pPlayer->Update();

	JW_ObjMgr::Get_Instance()->Update();

	return 0;
}

void JW_Scene::Late_Update()
{
	m_pPlayer->LateUpdate();

	JW_ObjMgr::Get_Instance()->LateUpdate();
}

void JW_Scene::Render(HDC hDC)
{
	m_pPlayer->Render(hDC);

	JW_ObjMgr::Get_Instance()->Render(hDC);
	//Rectangle(hDC, 0, 0, 200, 200);
}

void JW_Scene::Release()
{
	m_pPlayer->Release();

	JW_ObjMgr::Destroy_Instance();
}