#pragma once
#include "CHW_Obj.h"
class CHW_CBall : public CHW_Obj
{
public:
	CHW_CBall();
	~CHW_CBall();
public:
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void MoveToOrigin();
	void MakeWorldMatrix();
	void AdjustWorldMatrix();

	void CheckBoundary();
	void SetDirection(_vec3 normal );

private:

	vector<_vec3> m_vOriginPoints; //로컬
	vector<_vec3> m_vWorldPoints;  //월드

	_vec3 m_vOriginScale;	// 크기
	_vec3 m_vVelocity;		// 속도

	float m_fSpeed;



};

