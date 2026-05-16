#pragma once

#include "JW_Obj.h"

class JW_CollsionMgr
{
public:
	static bool Check_Wall_Collsion(JW_Obj* pPlayer, const list<JW_Obj*>& rWallList);
};