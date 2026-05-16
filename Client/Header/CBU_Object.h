#pragma once
#include "CBase.h"
#include "Define.h"
#include "BU_Define.h"

class CBU_Object : public CBase
{
public:
	explicit CBU_Object() : 
		m_ecType(BU_OBJID::OBJEND), m_bDead(false), m_pParentObject(nullptr), m_fSpeed(0.f), m_fAngle(0.f), m_fOrbitOffset(0.f),
		m_bAffectGravity(false), m_fGravitySpeed(0.f), m_ullFallingStartTime(0) 
	{ ZeroMemory(&m_vecScale, sizeof(_vec3));  ZeroMemory(&m_tInfo, sizeof(tagInfo)); }

	explicit CBU_Object(BU_OBJID ecType) :
		m_ecType(ecType), m_bDead(false), m_pParentObject(nullptr), m_fSpeed(0.f), m_fAngle(0.f), m_fOrbitOffset(0.f),
		m_bAffectGravity(false), m_fGravitySpeed(0.f), m_ullFallingStartTime(0) 
	{ ZeroMemory(&m_vecScale, sizeof(_vec3));  ZeroMemory(&m_tInfo, sizeof(tagInfo)); }

	virtual ~CBU_Object() {}

	virtual void Initialize(void) PURE;
	virtual void Update(void);
	virtual void LateUpdate(void) PURE;
	virtual void Render(HDC hDC) const;
	virtual void Free(void);

	static const _vec3 UPVEC;
	static const _vec3 DOWNVEC;
	static const float MAX_GRAVITY;

	virtual void UpdateGravity(void);
	virtual void OnCollision(CBU_Object* pObj) PURE;

	const BU_OBJID& GetObjType(void) const { return this->m_ecType; }
	const bool& IsDead(void) const { return this->m_bDead; }
	void SetDead(void) { this->m_bDead = true; }
	const _vec3& GetScale(void) const { return this->m_vecScale; }
	const tagInfo& GetInfo(void) const { return this->m_tInfo; }
	void SetPos(const _vec3& vecPos) { this->m_tInfo.vPos = vecPos; }
	void SetSpeed(const _float& fSpeed) { this->m_fSpeed = fSpeed; }
	const _float& GetSpeed(void) const { return this->m_fSpeed; }
	void SetAngle(const _float& fAngle) { this->m_fAngle = fAngle; }
	const _float& GetAngle(void) const { return this->m_fAngle; }
	const vector<_vec3>& GetRenderVertices(void) const { return this->m_vecRenderVertices; }
	void SetParentObject(CBU_Object* pObj) { this->m_pParentObject = pObj; pObj->AddRef(); }
	CBU_Object* GetParentObjectP(void) const { return this->m_pParentObject; }
	void ToggleGravity() { this->m_bAffectGravity = !this->m_bAffectGravity; m_ullFallingStartTime = GetTickCount64(); }
	const bool& IsAffectedByGravity(void) const { return this->m_bAffectGravity; }

protected:
	BU_OBJID m_ecType;
	bool m_bDead;
	_vec3 m_vecScale; // 크기
	tagInfo m_tInfo; // 위치, 이동방향, 시선방향, 월드변환행렬
	_float m_fSpeed; // 이동 속도(이동방향으로)
	_float m_fAngle;
	vector<_vec3> m_vecOriginalVertices; // 원래 버텍스 리스트(로컬버텍스)
	vector<_vec3> m_vecRenderVertices; // 렌더링할 버텍스 리스트(월드버텍스)
	list<INDEX32*> m_pIndicesList; // 버텍스 인덱스 목록(폴리곤 3개씩)
	CBU_Object* m_pParentObject;
	float m_fOrbitOffset;

private:
	bool m_bAffectGravity;
	float m_fGravitySpeed;
	ULONGLONG m_ullFallingStartTime;
};

