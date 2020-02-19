#include "stdafx.h"
#include "ScrollMgr.h"

IMPLEMENT_SINGLETON(CScrollMgr)

D3DXVECTOR3 CScrollMgr::m_vScrollPos = { 0.f, 0.f, 0.f };

CScrollMgr::CScrollMgr()
{
}


CScrollMgr::~CScrollMgr()
{
}

const D3DXVECTOR3& CScrollMgr::GetScrollPos()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_vScrollPos;
}

void CScrollMgr::MoveScrollPos(const D3DXVECTOR3& vMove)
{
	m_vScrollPos += vMove;
}
