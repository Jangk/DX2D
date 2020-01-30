#include "pch.h"
#include "GameObject.h"

void GameObject::UpdateRect()
{
	m_Rect.left		= LONG(m_tInfo.vPos.x - m_tInfo.fCX / 2);
	m_Rect.top		= LONG(m_tInfo.vPos.y - m_tInfo.fCY / 2);
	m_Rect.right	= LONG(m_tInfo.vPos.x + m_tInfo.fCX / 2);
	m_Rect.bottom	= LONG(m_tInfo.vPos.y + m_tInfo.fCY / 2);
}
