#include "stdafx.h"
#include "CollisionMgr.h"
#include "GameObject.h"
#include "Player.h";
#include "Block.h"
#include "Player.h"

IMPLEMENT_SINGLETON(CollisionMgr)

CollisionMgr::CollisionMgr()
{

}

CollisionMgr::~CollisionMgr()
{
}


//void CollisionMgr::CollisionBlock(OBJECT_LIST& dstList)
//{
//	CPlayer* src = CObjectMgr::GetInstance()->GetPlayer();
//	if (src == nullptr)
//		return;
//	RECT rc;
//	TOTAL_INFO destInfo;
//	TOTAL_INFO srcInfo;
//	for (auto pDest : dstList)
//	{
//		destInfo = pDest->GetTotalInfo();
//		srcInfo = src->GetTotalInfo();
//		if (IntersectRect(&rc, &destInfo.m_Rect, &srcInfo.m_Rect))
//		{
//			src->SetPos(srcInfo.vPos.x - (rc.right - rc.left),
//				srcInfo.vPos.y - (rc.bottom - rc.top), 0);
//		}
//	}
//}


void CollisionMgr::CollisionBlock(OBJECT_LIST& dstList)
{
	CPlayer* src = CObjectMgr::GetInstance()->GetPlayer();
	if (src == nullptr)
		return;
	float fMoveX;
	float fMoveY;
	BLOCK_TYPE bType;
	for (auto pDest : dstList)
	{
		if (IntersectRectEx(pDest, src, &fMoveX, &fMoveY))
		{	// 비어있는 블럭이면 예외
			if (dynamic_cast<Block*>(pDest)->GetBlockType() == BLOCK_EMPTY)
				continue;

			float fX = src->GetTotalInfo().vPos.x;
			float fY = src->GetTotalInfo().vPos.y;

			if (fMoveX+7 > fMoveY) // Y축으로 밀어냄
			{
				if (pDest->GetTotalInfo().vPos.y < fY)
					src->SetPos(fX, fY + fMoveY, 0);
				else
				{
					src->SetPos(fX, fY - fMoveY, 0);
					bType = dynamic_cast<Block*>(pDest)->GetBlockType();
					if (bType == BLOCK_BROKEN)
						pDest->IsDead();
					src->SetColY(bType);
				}
			}
			else // X축으로 밀어냄
			{
				if (pDest->GetTotalInfo().vPos.x < fX)
					src->SetPos(fX + fMoveX, fY, 0);
				else
					src->SetPos(fX - fMoveX, fY, 0);
				src->SetColX();
			}
		}
	}
}


bool CollisionMgr::IntersectRectEx(CGameObject* pDest, CGameObject* pSource, float* pMoveX, float* pMoveY)
{
	// x축의 반지름 합과 거리를 구한다.
	// 이 때 x축의 반지름 합이 x축의 거리보다 크면 x쪽으로 겹쳤다.
	float fSumX = pDest->GetTotalInfo().fCX * 0.5f + pSource->GetTotalInfo().fCX * 0.5f;
	float fDistX = fabs(pDest->GetTotalInfo().vPos.x - pSource->GetTotalInfo().vPos.x);

	// y축의 반지름 합과 거리를 구한다.
	// 이 때 y축의 반지름 합이 y축의 거리보다 크면 y쪽으로 겹쳤다.
	float fSumY = pDest->GetTotalInfo().fCY * 0.5f + pSource->GetTotalInfo().fCY * 0.5f;
	float fDistY = fabs(pDest->GetTotalInfo().vPos.y - pSource->GetTotalInfo().vPos.y);

	if (fSumX >= fDistX && fSumY >= fDistY)
	{
		// 겹친영역의 크기 구하기.
		*pMoveX = fSumX - fDistX;
		*pMoveY = fSumY - fDistY;

		return true;
	}
	return false;
}


