#pragma once
#include "Engine_Define.h"

class CBU_VectorUtil
{
public:
	static _vec3 GetXZProjectedVector(const _vec3& vDir)
	{
		_vec3 normVec = { vDir.x, 0.f, vDir.z };
		D3DXVec3Normalize(&normVec, &vDir);

		return normVec;
	}
};

