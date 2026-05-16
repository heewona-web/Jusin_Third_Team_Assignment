#include "pch.h"
#include "JW_Scene.h"
#include "JW_Player.h"
#include "JW_Wall.h"
#include "JW_AbstractFactory.h"
#include "JW_ObjMgr.h"
#include "CSceneMgr.h"
#include "JW_CollsionMgr.h"

JW_Scene::JW_Scene():m_pPlayer(nullptr), m_iScore(0), m_bGameOver(false)
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

	CHW_BmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Back.bmp", L"Back");
}

int JW_Scene::Update()
{
	if (m_bGameOver)
		return 0;

	m_pPlayer->Update();
	JW_ObjMgr::Get_Instance()->Update();

	Check_GameOver();
	Scoring();

	return 0;
}

void JW_Scene::Late_Update()
{
	if (m_bGameOver)
		return;

	m_pPlayer->LateUpdate();
	JW_ObjMgr::Get_Instance()->LateUpdate();
}

void JW_Scene::Render(HDC hDC)
{
	m_pPlayer->Render(hDC);
	JW_ObjMgr::Get_Instance()->Render(hDC);
	//Rectangle(hDC, 0, 0, 200, 200);

	wchar_t szScore[32] = {};
	swprintf_s(szScore, L"SCORE: %d", m_iScore);
	TextOut(hDC, 20, 20, szScore, lstrlen(szScore));
}

void JW_Scene::Release()
{
	m_pPlayer->Release();

	JW_ObjMgr::Destroy_Instance();
}

void JW_Scene::Check_GameOver()
{
	float fPlayerBodyLength = static_cast<JW_Player*>(m_pPlayer)->Get_BodyLength();

	if (m_pPlayer->Get_Info().vPos.y >= WINCY)
		m_bGameOver = true;

	auto& WallList = JW_ObjMgr::Get_Instance()->Get_ObjList(OBJ_WALL);

	if (JW_CollsionMgr::Check_Wall_Collsion(m_pPlayer, WallList))
		m_bGameOver = true;
}

void JW_Scene::Scoring()
{
	float fPlayerX = m_pPlayer->Get_Info().vPos.x;
	auto& WallList = JW_ObjMgr::Get_Instance()->Get_ObjList(OBJ_WALL);

	for (auto& pWall : WallList) {
		bool bIsPlayerPass = static_cast<JW_Wall*>(pWall)->Get_Player_Pass();

		if (!bIsPlayerPass && pWall->Get_Info().vPos.x < fPlayerX) {
			static_cast<JW_Wall*>(pWall)->Set_Player_Pass();
			m_iScore++;
		}
	}
}