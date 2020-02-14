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
		{	// ����ִ� ���̸� ����
			if (dynamic_cast<Block*>(pDest)->GetBlockType() == BLOCK_EMPTY)
				continue;

			float fX = src->GetTotalInfo().vPos.x;
			float fY = src->GetTotalInfo().vPos.y;

			if (fMoveX+7 > fMoveY) // Y������ �о
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
			else // X������ �о
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
	// x���� ������ �հ� �Ÿ��� ���Ѵ�.
	// �� �� x���� ������ ���� x���� �Ÿ����� ũ�� x������ ���ƴ�.
	float fSumX = pDest->GetTotalInfo().fCX * 0.5f + pSource->GetTotalInfo().fCX * 0.5f;
	float fDistX = fabs(pDest->GetTotalInfo().vPos.x - pSource->GetTotalInfo().vPos.x);

	// y���� ������ �հ� �Ÿ��� ���Ѵ�.
	// �� �� y���� ������ ���� y���� �Ÿ����� ũ�� y������ ���ƴ�.
	float fSumY = pDest->GetTotalInfo().fCY * 0.5f + pSource->GetTotalInfo().fCY * 0.5f;
	float fDistY = fabs(pDest->GetTotalInfo().vPos.y - pSource->GetTotalInfo().vPos.y);

	if (fSumX >= fDistX && fSumY >= fDistY)
	{
		// ��ģ������ ũ�� ���ϱ�.
		*pMoveX = fSumX - fDistX;
		*pMoveY = fSumY - fDistY;

		return true;
	}
	return false;
}


