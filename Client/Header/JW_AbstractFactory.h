#pragma once

#include "JW_Obj.h"

template<typename T>
class JW_AbstractFactory
{
public:
	static JW_Obj* Create_Obj()
	{
		JW_Obj* pObj = new T;

		pObj->Initialize();

		return pObj;
	}

	static JW_Obj* Create_Obj(float _x)
	{
		JW_Obj* pObj = new T;

		pObj->Initialize();
		pObj->Set_PosX(_x);

		return pObj;
	}
};