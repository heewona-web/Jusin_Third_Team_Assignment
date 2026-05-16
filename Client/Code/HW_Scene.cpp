#include "HW_Scene.h"
#include "CHW_CBall.h"

HW_Scene::HW_Scene() : m_pBall(nullptr)
{
}

HW_Scene::~HW_Scene()
{
    Release();
}

void HW_Scene::Initialize()
{
    if (nullptr == m_pBall) {
        m_pBall = new CHW_CBall;
    }
    m_pBall->Initialize();
 
    CHW_BmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Back.bmp", L"Back");

}

int HW_Scene::Update()
{
    m_pBall->Update();
    return 0;
}

void HW_Scene::Late_Update()
{
    m_pBall->LateUpdate();
}

void HW_Scene::Render(HDC hDC)
{
    m_pBall->Render(hDC);
    //Rectangle(hDC, 0, 0, 300, 300);
}

void HW_Scene::Release()
{
    Safe_Delete< CHW_Obj*>(m_pBall);
}
