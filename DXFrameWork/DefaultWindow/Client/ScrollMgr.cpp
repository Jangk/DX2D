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

	// x   // 현재 월드맵만 스크롤 적용되있고 y축으로만 이동함.
	//if (m_vScrollPos.x < 0)
	//	m_vScrollPos.x = 0;
	//if (m_vScrollPos.x > WORLDCX)
	//	m_vScrollPos.x = WORLDCX;
	// y
	if (m_vScrollPos.y < 0)
		m_vScrollPos.y = 0;
	if (m_vScrollPos.y > WORLDCY)
		m_vScrollPos.y = WORLDCY;
}
