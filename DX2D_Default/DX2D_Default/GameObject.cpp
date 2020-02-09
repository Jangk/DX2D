#include "pch.h"
#include "GameObject.h"

void GameObject::UpdateRect()
{
	m_Rect.left		= LONG(m_tInfo.vPos.x - m_tInfo.fCX / 2);
	m_Rect.top		= LONG(m_tInfo.vPos.y - m_tInfo.fCY / 2);
	m_Rect.right	= LONG(m_tInfo.vPos.x + m_tInfo.fCX / 2);
	m_Rect.bottom	= LONG(m_tInfo.vPos.y + m_tInfo.fCY / 2);
}

void GameObject::SetPos(float x, float y, float z)
{
	m_tInfo.vPos.x = x;
	m_tInfo.vPos.y = y;
	m_tInfo.vPos.z = z;
}

const INFO GameObject::GetInfo()
{
	return m_tInfo;
}
