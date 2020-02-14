#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	: m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance())
{
}


CGameObject::~CGameObject()
{
}

const TOTAL_INFO& CGameObject::GetTotalInfo()
{
	return m_TotalInfo;
}

void CGameObject::IsDead()
{
	m_bIsDead = true;
}
