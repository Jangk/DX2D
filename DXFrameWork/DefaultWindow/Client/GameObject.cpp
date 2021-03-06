#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	: m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()),
	m_pTimeMgr(CTimeMgr::GetInstance()),
	m_pObjectMgr(CObjectMgr::GetInstance()),
	m_pGameMgr(CGameMgr::GetInstance()),
	m_pKeyMgr(CKeyMgr::GetInstance())
{
	D3DXMatrixIdentity(&m_tInfo.matScale);		// 스케일
	D3DXMatrixIdentity(&m_tInfo.matRotate);		// 자전
	D3DXMatrixIdentity(&m_tInfo.matTrans);		// 이동
	D3DXMatrixIdentity(&m_tInfo.matGRotate);	// 공전
	D3DXMatrixIdentity(&m_tInfo.matParents);	// 부모행렬
	D3DXMatrixIdentity(&m_tInfo.matWorld);		// 다이렉트 항등행렬 함수

	m_tInfo.vPos		= { 400.f, 300.f, 0.f };	// x, y, z
	m_tInfo.vDir		= { 0.f, 0.f, 0.f };
	m_tInfo.vLook		= { 0.f, -1.f, 0.f };		// 위로 보는 방향
	m_tInfo.vSize		= { 1.f, 1.f, 0.f };
	m_tInfo.fCenterX	= 0;
	m_tInfo.fCenterY	= 0;
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

D3DXVECTOR3  CGameObject::GetScale()
{
	return D3DXVECTOR3(m_tInfo.matScale.m[0][0], m_tInfo.matScale.m[1][1], m_tInfo.matScale.m[2][2]);
}

void CGameObject::MoveTo(D3DXVECTOR3 vecTarget, float fSpeed)
{	// 러프
	m_tInfo.vPos = MyLerp(m_tInfo.vPos,vecTarget, fSpeed);
}

D3DXVECTOR3 CGameObject::MyLerp(D3DXVECTOR3 start, D3DXVECTOR3 end, float fSpeed)
{
	return start + (end - start) * fSpeed;
}