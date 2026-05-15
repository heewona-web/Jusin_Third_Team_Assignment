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

private:
	_vec3 m_vOriginCenter; //로컬
	_vec3 m_vWorldCenter; //월드
	float m_fRadius;
	float m_fSpeed;



};

