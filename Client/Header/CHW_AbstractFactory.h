#pragma once
#include "CHW_Obj.h"

template<typename T>
class CHW_AbstractFactory {
public:
	CHW_AbstractFactory() {}
	~CHW_AbstractFactory() {}
public:
	static CHW_Obj* CreateObj() {
		CHW_Obj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CHW_Obj* CreateObj(float fX, float fY) {
		CHW_Obj* pObj = new T(fX,fY);
		pObj->Initialize();

		return pObj;
	}
};