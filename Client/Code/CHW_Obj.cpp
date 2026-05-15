#include "CHW_Obj.h"

CHW_Obj::CHW_Obj()
{
	ZeroMemory(&m_tInfo, sizeof(tagInfo));
}

void CHW_Obj::MoveToOrigin()
{
	//vOriginPoints와 vWorldPoints의 사이즈는 같을 것임. => Initilize()에서 그렇게 되게끔해줬음

	for (size_t i = 0; i < m_vOriginPoints.size(); ++i) {
		m_vWorldPoints[i] = m_vOriginPoints[i];
	}
}

void CHW_Obj::MakeWorldMatrix()
{
	D3DXMATRIX		matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixIdentity(&matRotZ);
	if (fabsf(m_tInfo.vDir.x) > 1e-4f) {
		const float fAngle = atanf(m_tInfo.vDir.y / m_tInfo.vDir.x);
		D3DXMatrixRotationZ(&matRotZ, fAngle);

	}
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;
}


void CHW_Obj::AdjustWorldMatrix()
{

	for (auto& v : m_vWorldPoints) {
		D3DXVec3TransformCoord(&v, &v, &m_tInfo.matWorld);
	}
}

