#pragma once
#include "Define.h"
class CHW_Obj
{
public:
	CHW_Obj();
	virtual ~CHW_Obj() {};

public:
	virtual void Initialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

public:
	//virtual void MakeWorldMatrix();
	virtual void MoveToOrigin(); //원점 기준으로 이동시키기
	virtual void MakeWorldMatrix();
	virtual void AdjustWorldMatrix(); //WorldMat 적용
	virtual void RenderVertex(HDC hDC); //WorldMat 적용

public:
	const vector<_vec3>& GetWorldPoints() const {return m_vWorldPoints;}
protected:
	_INFO m_tInfo;


	vector<_vec3> m_vOriginPoints; //로컬
	vector<_vec3> m_vWorldPoints;  //월드
};

