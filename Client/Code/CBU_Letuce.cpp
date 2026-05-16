#include "CBU_Letuce.h"

CBU_Letuce::CBU_Letuce()
{

}
CBU_Letuce::~CBU_Letuce()
{

}

void CBU_Letuce::Initialize(void)
{
	// 크기 정보 초기화
	m_vecScale = { 30.f, 10.f, 30.f };
	// 위치 정보 초기화
	m_tInfo.vPos = { float(WINCX) / 2.f, 50.f, 0.f };
	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, 0.f, 1.f };

	// 버텍스 정보 초기화
	// 울퉁불퉁 구름모양
	m_vecOriginalVertices.push_back({ -1.2f, -0.f, 0.f }); // 0
	m_vecOriginalVertices.push_back({ -1.f, -0.5f, 0.f }); // 1
	m_vecOriginalVertices.push_back({ 1.f, -0.5f, 0.f }); // 2
	m_vecOriginalVertices.push_back({ 1.2f, -0.f, 0.f }); // 3
	m_vecOriginalVertices.push_back({ 1.f, 0.5f, 0.f }); // 4
	m_vecOriginalVertices.push_back({ -1.f, 0.5f, 0.f }); // 5

	// 렌더 정보 버텍스에 같은 크기만큼 복사
	for (size_t idx = 0; idx < m_vecOriginalVertices.size(); ++idx)
	{
		m_vecRenderVertices.push_back({ 0.f, 0.f, 0.f });
	}

	// 인덱스 정보 초기화
	m_pIndicesList.push_back(new INDEX32({ 0, 1, 3 }));
	m_pIndicesList.push_back(new INDEX32({ 1, 2, 3 }));
	m_pIndicesList.push_back(new INDEX32({ 3, 4, 5 }));
	m_pIndicesList.push_back(new INDEX32({ 5, 0, 3 }));

	m_fSpeed = 10.f;
	ToggleGravity();
}
