#include "CBU_RenderUtil.h"
#include "CBU_ObjectManager.h"

void CBU_RenderUtil::RenderCommonUI(HDC hDC)
{
	_int iIngredientSize = CBU_ObjectManager::GetInstance()->GetObjectVector(BU_OBJID::INGREDIENT).size();
	//wstring szMessage = L"재료 수 : " + iIngredientSize;
	wchar_t buffer[100];
	const wchar_t* format = L"재료 수 : %d";
	swprintf(buffer, 100, format, iIngredientSize);
	TextOut(hDC, 0, 0, buffer, lstrlen(buffer));
}
