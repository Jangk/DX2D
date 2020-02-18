#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	: m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()),
	m_pTimeMgr(CTimeMgr::GetInstance())
{
}


CGameObject::~CGameObject()
{
}

void CGameObject::SetPos(float x, float y, float z)
{
	m_tInfo.vPos = {x, y ,z };
}
