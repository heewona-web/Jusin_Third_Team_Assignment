#include "HW_Scene.h"

#include "CHW_Obj.h"
#include "CHW_BmpMgr.h"
#include "CHW_KeyMgr.h"
#include "CHW_ObjMgr.h"
#include "CHW_AbstractFactory.h"

#include "CHW_CBall.h"
#include "CHW_Stick.h"

HW_Scene::HW_Scene() {
}

HW_Scene::~HW_Scene()
{
    Release();
}

void HW_Scene::Initialize()
{

    CHW_BmpMgr::Get_Instance()->Insert_Bmp(L"../Data/Back.bmp", L"Back");

    CHW_ObjMgr::Get_Instance()->AddObject(OBJ_BALL, CHW_AbstractFactory<CHW_CBall>::CreateObj());

    CHW_ObjMgr::Get_Instance()->AddObject(OBJ_STICK, CHW_AbstractFactory<CHW_Stick>::CreateObj());
    

}

int HW_Scene::Update()
{

    CHW_KeyMgr::Get_Instance()->Update();

    CHW_ObjMgr::Get_Instance()->Update();

    return 0;
}

void HW_Scene::Late_Update()
{
    CHW_ObjMgr::Get_Instance()->LateUpdate();
}

void HW_Scene::Render(HDC hDC)
{

    CHW_ObjMgr::Get_Instance()->Render(hDC);
    //Rectangle(hDC, 0, 0, 300, 300);
}

void HW_Scene::Release()
{
    CHW_ObjMgr::Get_Instance()->Release();
    //Safe_Delete< CHW_Obj*>(m_pBall);
    //Safe_Delete< CHW_Obj*>(m_pStick);
}
