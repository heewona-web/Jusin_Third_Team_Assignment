#pragma once
#include "CBU_Object.h"

class CBU_Actor : public CBU_Object
{
public:
	explicit CBU_Actor();
	virtual ~CBU_Actor();

	void Initialize(void) override;
	void Update(void) override;
	void LateUpdate(void) override;
	void Render(HDC hDC) const override;
	//void Free(void) override;

protected:

};

