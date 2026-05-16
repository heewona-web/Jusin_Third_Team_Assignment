#include "CHW_CollisionMgr.h"

#include "CHW_CBall.h"


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

			_vec3 vMTVNormal = { 0.f ,0.f, 0.f }; //SAT충돌을 한다면 MTV정보 받아오기
			float fMTVValue = 0.f;

			if (IsCollide_SAT(Src, Dst, vMTVNormal, fMTVValue)) {
				//Src가 반드시 Wall을 가정하고 수행중...
				dynamic_cast<CHW_CBall*>(Src)->SetDirection_UseNormal(vMTVNormal);
				dynamic_cast<CHW_CBall*>(Src)->SetPosion_UseMTV(vMTVNormal, fMTVValue);
				// 충돌 직후는 잘 감지 그런데 내부에서 체류하면 계속 충돌충돌충돌 .. 
				// 임시로 MTV 밀어주기 .. 근데 방향 들어오는 방향 나가는 방향 생각해야하는데 일단 해봄
				

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

bool CHW_CollisionMgr::IsCollide_SAT(const CHW_Obj* pObj1, const CHW_Obj* pObj2, _vec3& vOutMTVDir, float& fOutMTVValue)
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

	float fMTVMin = 0x3f3f3f3f; 
	_vec3 vMTVNormal = { 0.f, 0.f, 0.f };

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

		float temp = min(fOutMax1 - fOutMin2, fOutMax2 - fOutMin1); // 겹치치 않게 밀어내기 위한 최소값
		if (temp < fMTVMin) {
			fMTVMin = temp;
			vMTVNormal = vAxis;
		}

	}
	//충돌이 일어남
	
	//MTV 방향 설정
	//https://kwonvector.tistory.com/59 방향 설정 (이해는 못함)
	_vec3 Obj1_To_2 = pObj1->GetINFO().vPos - pObj2->GetINFO().vPos;
	float fDot = D3DXVec3Dot(&Obj1_To_2, &vMTVNormal);

	vMTVNormal *= (fDot < 0 ? -1 : 1);
	
	


	//MTV 값 전달
	fOutMTVValue = fMTVMin;
	vOutMTVDir = vMTVNormal;



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
