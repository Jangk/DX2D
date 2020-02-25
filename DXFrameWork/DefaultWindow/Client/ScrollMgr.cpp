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
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_vScrollPos;
}

void CScrollMgr::MoveScrollPos(const D3DXVECTOR3& vMove)
{
	m_vScrollPos += vMove;

	// x   // ���� ����ʸ� ��ũ�� ������ְ� y�����θ� �̵���.
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
