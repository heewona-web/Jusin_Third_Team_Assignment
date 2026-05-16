#include "pch.h"
#include "JW_CollsionMgr.h"
#include "JW_Wall.h"
#include "JW_Player.h"

bool JW_CollsionMgr::Check_Wall_Collsion(JW_Obj* pPlayer, const list<JW_Obj*>& rWallList)
{
	float fPlayerX = pPlayer->Get_Info().vPos.x;
	float fPlayerY = pPlayer->Get_Info().vPos.y;	
	float fPlayerSize = static_cast<JW_Player*>(pPlayer)->Get_BodyLength();

	for (auto& pWall : rWallList) {
		float fWallX = pWall->Get_Info().vPos.x;
		float fWallWidth = static_cast<JW_Wall*>(pWall)->Get_Width();
		float fWallGapY = static_cast<JW_Wall*>(pWall)->Get_GapY();
		float fWallGapSize = static_cast<JW_Wall*>(pWall)->Get_GapSize();

		float fWallLeft = fWallX - (fWallWidth * 0.5f);
		float fWallRight = fWallX + (fWallWidth * 0.5f);

		if (fPlayerX + fPlayerSize > fWallLeft && fPlayerX - fPlayerSize < fWallRight) {
			
			float fTopWall = fWallGapY - (fWallGapSize * 0.5f);
			if (fPlayerY - fPlayerSize < fTopWall)
				return true;

			float fBottomWall = fWallGapY + (fWallGapSize * 0.5f);
			if (fPlayerY + fPlayerSize > fBottomWall)
				return true;
		}
	}

	return false;
}
