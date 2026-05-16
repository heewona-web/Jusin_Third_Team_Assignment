#include "CHW_CollisionMgr.h"

CHW_CollisionMgr* CHW_CollisionMgr::m_pInstance = nullptr;

CHW_CollisionMgr::CHW_CollisionMgr()
{
}

CHW_CollisionMgr::~CHW_CollisionMgr()
{
	//Release();
}