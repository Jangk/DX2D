#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	: m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()),
	m_pTimeMgr(CTimeMgr::GetInstance())
{
	D3DXMatrixIdentity(&m_tInfo.matScale);		// ������
	D3DXMatrixIdentity(&m_tInfo.matRotate);		// ����
	D3DXMatrixIdentity(&m_tInfo.matTrans);		// �̵�
	D3DXMatrixIdentity(&m_tInfo.matGRotate);	// ����
	D3DXMatrixIdentity(&m_tInfo.matParents);	// �θ����
	D3DXMatrixIdentity(&m_tInfo.matWorld);		// ���̷�Ʈ �׵���� �Լ�

	m_tInfo.vPos	= { 400.f, 300.f, 0.f };	// x, y, z
	m_tInfo.vDir	= { 0.f, 0.f, 0.f };
	m_tInfo.vLook	= { 0.f, -1.f, 0.f };		// ���� ���� ����
	m_tInfo.vSize	= { 1.f, 1.f, 0.f };
}


CGameObject::~CGameObject()
{
}

void CGameObject::SetPos(float x, float y, float z)
{
	m_tInfo.vPos = {x, y ,z };
}

void CGameObject::SetRotate(float fAngle)
{
	D3DXMatrixRotationZ(&m_tInfo.matRotate, D3DXToRadian(fAngle));
}

void CGameObject::SetScale(float x, float y, float z)
{
	D3DXMatrixScaling(&m_tInfo.matScale, x, y, z);
}

const INFO & CGameObject::GetInfo()
{
	return m_tInfo;
}
