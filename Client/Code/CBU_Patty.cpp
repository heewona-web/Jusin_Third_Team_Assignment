#include "CBU_Patty.h"

CBU_Patty::CBU_Patty()
{

}
CBU_Patty::~CBU_Patty()
{

}

void CBU_Patty::Initialize(void)
{
	// 크기 정보 초기화
	m_vecScale = { 40.f, 30.f, 40.f };
	// 위치 정보 초기화
	m_tInfo.vPos = { float(WINCX) / 2.f, 50.f, 0.f };
	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, 0.f, 1.f };

	// 버텍스 정보 초기화
	// 육각형 3층건물 가운데 튀어나온
	// 위층
	m_vecOriginalVertices.push_back({ -2.f, -0.5f, 0.f }); // 0
	m_vecOriginalVertices.push_back({ -1.f, -0.5f, 1.732f }); // 1
	m_vecOriginalVertices.push_back({ 1.f, -0.5f, 1.732f }); // 2
	m_vecOriginalVertices.push_back({ 2.f, -0.5f, 0.f }); // 3
	m_vecOriginalVertices.push_back({ 1.f, -0.5f, -1.732f }); // 4
	m_vecOriginalVertices.push_back({ -1.f, -0.5f, -1.732f }); // 5
	m_vecOriginalVertices.push_back({ -0.f, -0.5f, -0.f }); // 6
	// 중앙층
	m_vecOriginalVertices.push_back({ -2.4f, 0.f, 0.f }); // 0
	m_vecOriginalVertices.push_back({ -1.2f, 0.f, 2.078f }); // 1
	m_vecOriginalVertices.push_back({ 1.2f, 0.f, 2.078f }); // 2
	m_vecOriginalVertices.push_back({ 2.4f, 0.f, 0.f }); // 3
	m_vecOriginalVertices.push_back({ 1.2f, 0.f, -2.078f }); // 4
	m_vecOriginalVertices.push_back({ -1.2f, 0.f, -2.078f }); // 5	
	m_vecOriginalVertices.push_back({ 0.f, 0.f, 0.f }); // 6
	// 아래층
	m_vecOriginalVertices.push_back({ -2.f, 0.5f, 0.f }); // 0
	m_vecOriginalVertices.push_back({ -1.f, 0.5f, 1.732f }); // 1
	m_vecOriginalVertices.push_back({ 1.f, 0.5f, 1.732f }); // 2
	m_vecOriginalVertices.push_back({ 2.f, 0.5f, 0.f }); // 3
	m_vecOriginalVertices.push_back({ 1.f, 0.5f, -1.732f }); // 4
	m_vecOriginalVertices.push_back({ -1.f, 0.5f, -1.732f }); // 5
	m_vecOriginalVertices.push_back({ -0.f, 0.5f, -0.f }); // 6(중심)

	// 렌더 정보 버텍스에 같은 크기만큼 복사
	for (size_t idx = 0; idx < m_vecOriginalVertices.size(); ++idx)
	{
		m_vecRenderVertices.push_back({ 0.f, 0.f, 0.f });
	}

	// 인덱스 정보 초기화
	m_pIndicesList.push_back(new INDEX32({ 0, 1, 6 }));
	m_pIndicesList.push_back(new INDEX32({ 1, 2, 6 }));
	m_pIndicesList.push_back(new INDEX32({ 2, 3, 6 }));
	m_pIndicesList.push_back(new INDEX32({ 3, 4, 6 }));
	m_pIndicesList.push_back(new INDEX32({ 4, 5, 6 }));
	m_pIndicesList.push_back(new INDEX32({ 5, 0, 6 }));

	m_pIndicesList.push_back(new INDEX32({ 0, 1, 8 }));
	m_pIndicesList.push_back(new INDEX32({ 8, 7, 0 }));
	m_pIndicesList.push_back(new INDEX32({ 1, 2, 9 }));
	m_pIndicesList.push_back(new INDEX32({ 9, 8, 1 }));
	m_pIndicesList.push_back(new INDEX32({ 2, 3, 10 }));
	m_pIndicesList.push_back(new INDEX32({ 10, 9, 2 }));
	m_pIndicesList.push_back(new INDEX32({ 3, 4, 11 }));
	m_pIndicesList.push_back(new INDEX32({ 11, 10, 3 }));
	m_pIndicesList.push_back(new INDEX32({ 4, 5, 12 }));
	m_pIndicesList.push_back(new INDEX32({ 12, 11, 4 }));
	m_pIndicesList.push_back(new INDEX32({ 5, 0, 7 }));
	m_pIndicesList.push_back(new INDEX32({ 7, 12, 5 }));

	m_pIndicesList.push_back(new INDEX32({ 7, 8, 13 }));
	m_pIndicesList.push_back(new INDEX32({ 8, 9, 13 }));
	m_pIndicesList.push_back(new INDEX32({ 9, 10, 13 }));
	m_pIndicesList.push_back(new INDEX32({ 10, 11, 13 }));
	m_pIndicesList.push_back(new INDEX32({ 11, 12, 13 }));
	m_pIndicesList.push_back(new INDEX32({ 12, 7, 13 }));

	m_pIndicesList.push_back(new INDEX32({ 7, 8, 15 }));
	m_pIndicesList.push_back(new INDEX32({ 15, 14, 7 }));
	m_pIndicesList.push_back(new INDEX32({ 8, 9, 16 }));
	m_pIndicesList.push_back(new INDEX32({ 16, 15, 8 }));
	m_pIndicesList.push_back(new INDEX32({ 9, 10, 17 }));
	m_pIndicesList.push_back(new INDEX32({ 17, 16, 9 }));
	m_pIndicesList.push_back(new INDEX32({ 10, 11, 18 }));
	m_pIndicesList.push_back(new INDEX32({ 18, 17, 10 }));
	m_pIndicesList.push_back(new INDEX32({ 11, 12, 19 }));
	m_pIndicesList.push_back(new INDEX32({ 19, 18, 11 }));
	m_pIndicesList.push_back(new INDEX32({ 12, 13, 20 }));
	m_pIndicesList.push_back(new INDEX32({ 20, 19, 12 }));
	m_pIndicesList.push_back(new INDEX32({ 13, 7, 14 }));
	m_pIndicesList.push_back(new INDEX32({ 14, 20, 13 }));

	m_pIndicesList.push_back(new INDEX32({ 14, 15, 20 }));
	m_pIndicesList.push_back(new INDEX32({ 15, 16, 20 }));
	m_pIndicesList.push_back(new INDEX32({ 16, 17, 20 }));
	m_pIndicesList.push_back(new INDEX32({ 17, 18, 20 }));
	m_pIndicesList.push_back(new INDEX32({ 18, 19, 20 }));
	m_pIndicesList.push_back(new INDEX32({ 19, 14, 20 }));

	m_fSpeed = 10.f;
	ToggleGravity();
}
