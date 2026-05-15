#include "HW_Scene.h"
#include "CHW_CBall.h"
#include "CHW_Stick.h"

HW_Scene::HW_Scene() : m_pBall(nullptr), m_pStick(nullptr)
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

    if (nullptr == m_pStick) {
        m_pStick = new CHW_Stick;
    }
    m_pStick->Initialize();
 
    CHW_BmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Back.bmp", L"Back");

}

int HW_Scene::Update()
{
    m_pBall->Update();
    m_pStick->Update();
    return 0;
}

void HW_Scene::Late_Update()
{
    m_pBall->LateUpdate();
    m_pStick->LateUpdate();
}

void HW_Scene::Render(HDC hDC)
{
    m_pBall->Render(hDC);
    m_pStick->Render(hDC);
    //Rectangle(hDC, 0, 0, 300, 300);
}

void HW_Scene::Release()
{
    Safe_Delete< CHW_Obj*>(m_pBall);
    Safe_Delete< CHW_Obj*>(m_pStick);
}
