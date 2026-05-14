#pragma once

class  _declspec(dllexport) CBase
{
protected:
	inline explicit CBase();
	inline virtual ~CBase();

public:
	inline unsigned long AddRef();			// 레퍼런스 카운트 증가 함수
	inline unsigned long Release();			// 레퍼런스 카운트 감소 및 메모리 해제 함수

private:
	unsigned	long			m_dwRefCnt;

public:
	inline virtual void	Free() = 0;
};

#include "CBase.inl"