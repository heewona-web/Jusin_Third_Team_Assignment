#include "CBU_Cheese.h"

CBU_Cheese::CBU_Cheese()
{

}
CBU_Cheese::~CBU_Cheese()
{

}

void CBU_Cheese::Initialize(void)
{
	// 크기 정보 초기화
	m_vecScale = { 40.f, 11.f, 40.f };
	// 위치 정보 초기화
	m_tInfo.vPos = { float(WINCX) / 2.f, 50.f, 0.f };
	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, 0.f, 1.f };

	// 버텍스 정보 초기화
	// 얇은 사각형 2층. 직육면체
	// 위층
	m_vecOriginalVertices.push_back({ -2.f, -0.5f, 2.f }); // 0
	m_vecOriginalVertices.push_back({ 2.f, -0.5f, 2.f }); // 1
	m_vecOriginalVertices.push_back({ 2.f, -0.5f, -2.f }); // 2
	m_vecOriginalVertices.push_back({ -2.f, -0.5f, -2.f }); // 3
	// 아래층
	m_vecOriginalVertices.push_back({ -2.f, 0.5f, 2.f }); // 0
	m_vecOriginalVertices.push_back({ 2.f, 0.5f, 2.f }); // 1
	m_vecOriginalVertices.push_back({ 2.f, 0.5f, -2.f }); // 2
	m_vecOriginalVertices.push_back({ -2.f, 0.5f, -2.f }); // 3

	// 렌더 정보 버텍스에 같은 크기만큼 복사
	for (size_t idx = 0; idx < m_vecOriginalVertices.size(); ++idx)
	{
		m_vecRenderVertices.push_back({ 0.f, 0.f, 0.f });
	}

	// 인덱스 정보 초기화
	m_pIndicesList.push_back(new INDEX32({ 0, 1, 2 }));
	m_pIndicesList.push_back(new INDEX32({ 2, 3, 0 }));

	m_pIndicesList.push_back(new INDEX32({ 0, 1, 5 }));
	m_pIndicesList.push_back(new INDEX32({ 5, 4, 0 }));
	m_pIndicesList.push_back(new INDEX32({ 1, 2, 6 }));
	m_pIndicesList.push_back(new INDEX32({ 6, 5, 1 }));
	m_pIndicesList.push_back(new INDEX32({ 2, 3, 7 }));
	m_pIndicesList.push_back(new INDEX32({ 7, 6, 2 }));
	m_pIndicesList.push_back(new INDEX32({ 3, 0, 4 }));
	m_pIndicesList.push_back(new INDEX32({ 4, 7, 3 }));

	m_pIndicesList.push_back(new INDEX32({ 4, 5, 6 }));
	m_pIndicesList.push_back(new INDEX32({ 6, 7, 4 }));

	m_fSpeed = 10.f;
	ToggleGravity();
}
