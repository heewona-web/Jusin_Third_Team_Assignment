#include "CBU_CollisionUtil.h"
#include "CBU_Ingredient.h"

bool CBU_CollisionUtil::CheckObjAndObj(CBU_Object* pSrcObj, CBU_Object* pDstObj)
{
    //switch (pSrcObj->GetObjType())
    //{
    //case BU_OBJID::PLAYER:
    //case BU_OBJID::INGREDIENT:
    //    CBU_Ingredient* pIngredient = static_cast<CBU_Ingredient*>(pSrcObj);
    //    return CheckRectAndRect(pSrcObj->GetRect(), pDstObj->GetRect(), nullptr);
    //    return CheckRectAndCircle(pDstObj->GetCollisionInfo(), pSrCBU_Object->GetCollisionInfo());
    //case BU_OBJID::SPAWNER:
    //default:
    //    return CheckRectAndCircle(pDstObj->GetCollisionInfo(), pSrCBU_Object->GetCollisionInfo());
    //}

	return IsCollide_SAT(pSrcObj, pDstObj);
}
bool CBU_CollisionUtil::IsCollide_SAT(const CBU_Object* pSrcObj, const CBU_Object* pDstObj)
{
	const auto& vecVertexs1 = pSrcObj->GetRenderVertices();
	const auto& vecVertexs2 = pDstObj->GetRenderVertices();

	vector<_vec3> edges;
	edges.reserve(vecVertexs1.size() + vecVertexs2.size());

	//CObj1의 모서리
	for (size_t i = 0; i < vecVertexs1.size(); ++i) {

		edges.push_back(vecVertexs1[i] - vecVertexs1[(i + 1) % vecVertexs1.size()]);
	}
	//CObj2의 모서리
	for (size_t i = 0; i < vecVertexs2.size(); ++i) {

		edges.push_back(vecVertexs2[i] - vecVertexs2[(i + 1) % vecVertexs2.size()]);
	}

	// 모서리 => 법선 벡터 ( 축 ) 
	for (const auto& e : edges) {

		D3DXVECTOR3 vAxis;
		vAxis = { -e.y , e.x, 0.f };
		D3DXVec3Normalize(&vAxis, &vAxis);
		float fOutMin1, fOutMax1;
		float fOutMin2, fOutMax2;
		Project(pSrcObj, vAxis, fOutMin1, fOutMax1);
		Project(pDstObj, vAxis, fOutMin2, fOutMax2);

		if (fOutMax1 < fOutMin2 || fOutMax2 < fOutMin1)
			return false;

	}

	//MFV 추가해보기



	return true;
}

void CBU_CollisionUtil::Project(const CBU_Object* pObj, const D3DXVECTOR3 vAxis, float& fOutMin, float& fOutMax)
{

	const auto& vecVertexs = pObj->GetRenderVertices();
	fOutMin = fOutMax = D3DXVec3Dot(&vecVertexs[0], &vAxis);


	for (int i = 1; i < vecVertexs.size(); ++i) {

		float fDot = D3DXVec3Dot(&vecVertexs[i], &vAxis);
		fOutMin = min(fOutMin, fDot);
		fOutMax = max(fOutMax, fDot);


	}
}