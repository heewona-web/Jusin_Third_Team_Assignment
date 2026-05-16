#pragma once
#include "CBase.h"
#include "Define.h"

class CBU_Object : public CBase
{
public:
	explicit CBU_Object() : m_pParentObject(nullptr), m_fSpeed(0.f), m_fAngle(0.f) { ZeroMemory(&m_tInfo, sizeof(tagInfo)); }
	virtual ~CBU_Object() {}

	virtual void Initialize(void) PURE;
	virtual void Update(void) PURE;
	virtual void LateUpdate(void) PURE;
	virtual void Render(HDC hDC) const PURE;
	virtual void Free(void);

	static const _vec3 UPVEC;
	static const _vec3 DOWNVEC;

protected:
	void SetSpeed(const _float& fSpeed) { this->m_fSpeed = fSpeed; }
	const _float& GetSpeed(void) const { return this->m_fSpeed; }
	void SetParentObject(CBU_Object* pObj) { this->m_pParentObject = pObj; pObj->AddRef(); }
	CBU_Object* GetParentObjectP(void) const { return this->m_pParentObject; }

	tagInfo m_tInfo; // 위치, 이동방향, 시선방향, 월드변환행렬
	_float m_fSpeed; // 이동 속도(이동방향으로)
	_float m_fAngle;
	vector<_vec3*> m_pVecOriginalVertices; // 원래 버텍스 리스트
	vector<_vec3*> m_pVecRenderVertices; // 렌더링할 버텍스 리스트
	list<INDEX32*> m_pIndicesList; // 버텍스 인덱스 목록(폴리곤 3개씩)

private:
	CBU_Object* m_pParentObject;
};

