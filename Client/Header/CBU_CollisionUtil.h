#pragma once
#include "CBU_Object.h"

class CBU_CollisionUtil
{
public:
    static bool CheckObjAndObj(CBU_Object* pSrCBU_Object, CBU_Object* pDstObj);
    //static bool CheckLineInObjBox(CBU_Object* pObj, CLine* pLine);
    //static bool CheckLineInObjCircle(CBU_Object* pObj, CLine* pLine);

private:
    //static bool CheckObjIsSideOfLine(CBU_Object* pObj, CLine* pLine);
    //static bool CheckObjInLineXRange(CBU_Object* pObj, CLine* pLine);
    //static bool CheckObjInLineYRange(CBU_Object* pObj, CLine* pLine);
    //static bool CheckObjIsOnLine(CBU_Object* pObj, CLine* pLine);
    //static bool CheckObjIsUnderLine(CBU_Object* pObj, CLine* pLine);

    static bool CheckRectAndRect(const RECT& pSrcRect, const RECT& pDstRect, RECT* pIntersection);
    static bool CheckCircleAndCircle(const INFO& tSrcCircle, const INFO& tDstCircle, const float& fAdditionalDistance = 0.f);
    static bool CheckRectAndCircle(const INFO& tRectInfo, const INFO& tCircleInfo);

    static bool IsCollide_SAT(const CBU_Object* Obj1, const CBU_Object* Obj2);
    static void Project(const CBU_Object* obj, const D3DXVECTOR3 vAxis, float& fOutMin, float& fOutMax);
};

