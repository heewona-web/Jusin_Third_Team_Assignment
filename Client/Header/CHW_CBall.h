#pragma once
#include "CHW_Obj.h"
class CHW_CBall : public CHW_Obj
{
public:
	CHW_CBall();
	~CHW_CBall();
public:
	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void CheckBoundary();
	void SetDirection_UseNormal(_vec3 normal );
	void SetPosion_UseMTV(_vec3 normal, float value);
	void MakeWorldMatrix() override;

private:
	float m_fRadius;
	_vec3 m_vOriginScale;	// 크기
	_vec3 m_vVelocity;		// 속도

	float m_fCurAngle; //라이안 값
	const float m_fRotAngle = 0.005f;



	float m_fSpeed;



};

