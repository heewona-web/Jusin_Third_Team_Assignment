#include "CBU_Tomato.h"

CBU_Tomato::CBU_Tomato()
{

}
CBU_Tomato::~CBU_Tomato()
{

}

void CBU_Tomato::Initialize(void)
{
	// 크기 정보 초기화
	m_vecScale = { 40.f, 15.f, 40.f };
	// 위치 정보 초기화
	m_tInfo.vPos = { float(WINCX) / 2.f, 50.f, 0.f };
	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, 0.f, 1.f };

	// 버텍스 정보 초기화
	// 넓적한 팔각기둥...
	m_vecOriginalVertices.push_back({ -1.3065f, -0.5f, 0.f }); // 0
	m_vecOriginalVertices.push_back({ -0.923835f, -0.5f, 0.923835f }); // 1
	m_vecOriginalVertices.push_back({ 0.f, -0.5f, 1.3065f }); // 2
	m_vecOriginalVertices.push_back({ 0.923835f, -0.5f, 0.923835f }); // 3
	m_vecOriginalVertices.push_back({ 1.3065f, -0.5f, 0.f }); // 4
	m_vecOriginalVertices.push_back({ 0.923835f, -0.5f, -0.923835f }); // 5
	m_vecOriginalVertices.push_back({ 0.f, -0.5f, -1.3065f }); // 6
	m_vecOriginalVertices.push_back({ -0.923835f, -0.5f, -0.923835f }); // 7
	m_vecOriginalVertices.push_back({ -0.f, -0.5f, -0.f }); // 8 중심

	m_vecOriginalVertices.push_back({ -1.3065f, 0.5f, 0.f }); // 0
	m_vecOriginalVertices.push_back({ -0.923835f, 0.5f, 0.923835f }); // 1
	m_vecOriginalVertices.push_back({ 0.f, 0.5f, 1.3065f }); // 2
	m_vecOriginalVertices.push_back({ 0.923835f, 0.5f, 0.923835f }); // 3
	m_vecOriginalVertices.push_back({ 1.3065f, 0.5f, 0.f }); // 4
	m_vecOriginalVertices.push_back({ 0.923835f, 0.5f, -0.923835f }); // 5
	m_vecOriginalVertices.push_back({ 0.f, 0.5f, -1.3065f }); // 6
	m_vecOriginalVertices.push_back({ -0.923835f, 0.5f, -0.923835f }); // 7
	m_vecOriginalVertices.push_back({ -0.f, 0.5f, -0.f }); // 8 중심

	// 렌더 정보 버텍스에 같은 크기만큼 복사
	for (size_t idx = 0; idx < m_vecOriginalVertices.size(); ++idx)
	{
		m_vecRenderVertices.push_back({ 0.f, 0.f, 0.f });
	}

	// 인덱스 정보 초기화
	m_pIndicesList.push_back(new INDEX32({ 0, 1, 8 }));
	m_pIndicesList.push_back(new INDEX32({ 1, 2, 8 }));
	m_pIndicesList.push_back(new INDEX32({ 2, 3, 8 }));
	m_pIndicesList.push_back(new INDEX32({ 3, 4, 8 }));
	m_pIndicesList.push_back(new INDEX32({ 4, 5, 8 }));
	m_pIndicesList.push_back(new INDEX32({ 5, 6, 8 }));
	m_pIndicesList.push_back(new INDEX32({ 6, 7, 8 }));
	m_pIndicesList.push_back(new INDEX32({ 7, 0, 8 }));

	m_pIndicesList.push_back(new INDEX32({ 0, 1, 10 }));
	m_pIndicesList.push_back(new INDEX32({ 10, 9, 0 }));
	m_pIndicesList.push_back(new INDEX32({ 1, 2, 11 }));
	m_pIndicesList.push_back(new INDEX32({ 11, 10, 1 }));
	m_pIndicesList.push_back(new INDEX32({ 2, 3, 12 }));
	m_pIndicesList.push_back(new INDEX32({ 12, 11, 2 }));
	m_pIndicesList.push_back(new INDEX32({ 3, 4, 13 }));
	m_pIndicesList.push_back(new INDEX32({ 13, 12, 3 }));
	m_pIndicesList.push_back(new INDEX32({ 4, 5, 14 }));
	m_pIndicesList.push_back(new INDEX32({ 14, 13, 4 }));
	m_pIndicesList.push_back(new INDEX32({ 5, 6, 15 }));
	m_pIndicesList.push_back(new INDEX32({ 15, 14, 5 }));
	m_pIndicesList.push_back(new INDEX32({ 6, 7, 16 }));
	m_pIndicesList.push_back(new INDEX32({ 16, 15, 6 }));
	m_pIndicesList.push_back(new INDEX32({ 7, 0, 9 }));
	m_pIndicesList.push_back(new INDEX32({ 9, 16, 7 }));

	m_pIndicesList.push_back(new INDEX32({ 9, 10, 17 }));
	m_pIndicesList.push_back(new INDEX32({ 10, 11, 17 }));
	m_pIndicesList.push_back(new INDEX32({ 11, 12, 17 }));
	m_pIndicesList.push_back(new INDEX32({ 12, 13, 17 }));
	m_pIndicesList.push_back(new INDEX32({ 13, 14, 17 }));
	m_pIndicesList.push_back(new INDEX32({ 14, 15, 17 }));
	m_pIndicesList.push_back(new INDEX32({ 15, 16, 17 }));
	m_pIndicesList.push_back(new INDEX32({ 16, 9, 17 }));

	m_fSpeed = 10.f;
	ToggleGravity();
}
