#include "pch.h"
#include "JW_Scene.h"
#include "JW_Player.h"

JW_Scene::JW_Scene():m_pPlayer(nullptr)
{

}

JW_Scene::~JW_Scene()
{
	Release();
}

void JW_Scene::Initialize()
{
	if (!m_pPlayer) {
		m_pPlayer = new JW_Player;
		m_pPlayer->Initialize();
	}
}

int JW_Scene::Update()
{
	m_pPlayer->Update();

	return 0;
}

void JW_Scene::Late_Update()
{
	m_pPlayer->LateUpdate();
}

void JW_Scene::Render(HDC hDC)
{
	m_pPlayer->Render(hDC);

	//Rectangle(hDC, 0, 0, 200, 200);
}

void JW_Scene::Release()
{
	m_pPlayer->Release();
}