#pragma once

extern HWND g_hWnd;

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;	// ¿ßƒ° ∫§≈Õ

	D3DXVECTOR3		vDir;	// πÊ«‚ ∫§≈Õ
	D3DXVECTOR3		vLook;

	D3DXVECTOR3		vNormal;	// π˝º± ∫§≈Õ(πÊ«‚ ∫§≈Õ)

	D3DXMATRIX		matWorld;


}INFO;

static D3DXVECTOR3		GetMouse()
{
	POINT ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	return D3DXVECTOR3((float)ptMouse.x, (float)ptMouse.y, 0.f);
}
