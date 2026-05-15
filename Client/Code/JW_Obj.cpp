#include "pch.h"
#include "JW_Obj.h"

JW_Obj::JW_Obj() : m_fSpeed(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(tagInfo));
}

JW_Obj::~JW_Obj()
{

}