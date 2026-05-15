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
	void CheckBoundary();
	void SetDirection(_vec3 normal );

private:
	_vec3 m_vOriginScale;	// 크기
	_vec3 m_vVelocity;		// 속도

	float m_fSpeed;



};

