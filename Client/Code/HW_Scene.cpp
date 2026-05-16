#include "HW_Scene.h"

#include "CHW_AbstractFactory.h"
#include "CHW_BmpMgr.h"
#include "CHW_KeyMgr.h"
#include "CHW_ObjMgr.h"
#include "CHW_CollisionMgr.h"

#include "CHW_Obj.h"
#include "CHW_CBall.h"
#include "CHW_Stick.h"
#include "CHW_Brick.h"

HW_Scene::HW_Scene() : m_iFPS(0), m_dwTime(GetTickCount()) {
    ZeroMemory(m_szFPS, sizeof(m_szFPS));
}

HW_Scene::~HW_Scene()
{
    Release();
}

void HW_Scene::Initialize()
{

    CHW_BmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Back.bmp", L"Back");

    CHW_ObjMgr::Get_Instance()->AddObject(HW_OBJ_BALL, CHW_AbstractFactory<CHW_CBall>::CreateObj());

    CHW_ObjMgr::Get_Instance()->AddObject(HW_OBJ_STICK, CHW_AbstractFactory<CHW_Stick>::CreateObj());


    for (size_t i = 0; i < 8;++i) {
        for (size_t j = 0; j < 3; ++j) {
            CHW_ObjMgr::Get_Instance()->AddObject(HW_OBJ_BRICK, CHW_AbstractFactory<CHW_Brick>::CreateObj(50 + i * 100, 15 + j * 30));
        }
    }

    

}

int HW_Scene::Update()
{

    CHW_KeyMgr::Get_Instance()->Update();

    CHW_ObjMgr::Get_Instance()->Update();

    return 0;
}

void HW_Scene::Late_Update()
{
    CHW_CollisionMgr::Get_Instance()->CheckCollision_SAT(HW_OBJ_BALL, HW_OBJ_STICK);
    CHW_CollisionMgr::Get_Instance()->CheckCollision_SAT(HW_OBJ_BALL, HW_OBJ_BRICK);
    CHW_ObjMgr::Get_Instance()->LateUpdate();
}

void HW_Scene::Render(HDC hDC)
{

    CHW_ObjMgr::Get_Instance()->Render(hDC);

    ++m_iFPS;

    if (m_dwTime + 1000 < GetTickCount())
    {
        swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

        SetWindowText(g_hWnd, m_szFPS);

        m_iFPS = 0;
        m_dwTime = GetTickCount();
    }



}

void HW_Scene::Release()
{

    CHW_CollisionMgr::Destroy_Instance();
    CHW_KeyMgr::Destroy_Instance();
    CHW_ObjMgr::Destroy_Instance();

}
