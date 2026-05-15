#pragma once

#include "Engine_Define.h"

extern HWND g_hWnd;

typedef struct tagInfo
{
	_vec3		vPos;	// ¿ßƒ° ∫§≈Õ

	_vec3		vDir;	// πÊ«‚ ∫§≈Õ
	_vec3		vLook;

	_vec3		vNormal;	// π˝º± ∫§≈Õ(πÊ«‚ ∫§≈Õ)

	_matrix		matWorld;


}_INFO;

static _vec3		GetMouse()
{
	POINT ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	return _vec3((float)ptMouse.x, (float)ptMouse.y, 0.f);
}

enum SCENEID {

	LOGO,
	HW_SCENE,
	BU_SCENE,
	TG_SCENE,
	JW_SCENE

};
