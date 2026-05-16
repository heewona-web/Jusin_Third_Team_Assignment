#include "CHW_CollisionMgr.h"

CHW_CollisionMgr* CHW_CollisionMgr::m_pInstance = nullptr;

CHW_CollisionMgr::CHW_CollisionMgr()
{
}

CHW_CollisionMgr::~CHW_CollisionMgr()
{
	//Release();
}

void CHW_CollisionMgr::CheckCollision_SAT(HW_OBJ_TYPE TYPE1, HW_OBJ_TYPE TYPE2)
{
	const auto& ObjList1 = CHW_ObjMgr::Get_Instance()->GetObjList(TYPE1);
	const auto& ObjList2 = CHW_ObjMgr::Get_Instance()->GetObjList(TYPE2);

	for (auto& Src : ObjList1) {
		for (auto& Dst : ObjList2) {
			//충돌 처리  ( 임시 )
			//D3DXVECTOR3 vAxis = { 0, 0, 0 };
			//float fMinOverlapped = static_cast<float>(INF);
			//if (IsCollide_SAT(Src, Dst, &vAxis, &fMinOverlapped)) {
			if (IsCollide_SAT(Src, Dst)) {

				Src->SetCollide(true);
				Dst->SetCollide(true);
			}
			else {
				Src->SetCollide(false);
				Dst->SetCollide(false);

			}
		}
	}
}

bool CHW_CollisionMgr::IsCollide_SAT(const CHW_Obj* pObj1, const CHW_Obj* pObj2)
{
	const auto& vecVertexs1 = pObj1->GetWorldPoints();
	const auto& vecVertexs2 = pObj2->GetWorldPoints();

	vector<D3DXVECTOR3> edges;
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
		Project(pObj1, vAxis, fOutMin1, fOutMax1);
		Project(pObj2, vAxis, fOutMin2, fOutMax2);

		if (fOutMax1 < fOutMin2 || fOutMax2 < fOutMin1)
			return false;

	}

	//MFV 추가해보기



	return true;
}

void CHW_CollisionMgr::Project(const CHW_Obj* pObj, const D3DXVECTOR3 vAxis, float& fOutMin, float& fOutMax)
{
	const auto& vecVertexs = pObj->GetWorldPoints();
	fOutMin = fOutMax = D3DXVec3Dot(&vecVertexs[0], &vAxis);


	for (int i = 1; i < vecVertexs.size(); ++i) {

		float fDot = D3DXVec3Dot(&vecVertexs[i], &vAxis);
		fOutMin = min(fOutMin, fDot);
		fOutMax = max(fOutMax, fDot);


	}

}
