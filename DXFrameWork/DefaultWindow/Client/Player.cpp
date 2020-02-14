#include "stdafx.h"
#include "Player.h"
#include "ScrollMgr.h"

CPlayer::CPlayer()
	: m_pKeyMgr(CKeyMgr::GetInstance())
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CPlayer::~CPlayer()
{
	Release();
}

int CPlayer::Update()
{		
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta()/* * 20.f*/;

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
		m_tFrame.fCurFrame = 0.f;

	return NO_EVENT;
}

void CPlayer::LateUpdate()
{
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixScaling(&matScale, 
		m_tInfo.vSize.x, 
		m_tInfo.vSize.y,
		0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x - CScrollMgr::GetScrollPos().x, 
		m_tInfo.vPos.y - CScrollMgr::GetScrollPos().y,
		0.f); // 다이렉트 이동행렬 함수

	m_tInfo.matWorld = matScale * matTrans;
	
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
}

void CPlayer::Render()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Player", L"Dash", (int)m_tFrame.fCurFrame);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CPlayer::Initialize()
{
	// 행렬 초기화 -> 항등행렬(I)
	//CMathMgr::MyMatrixIdentity(&m_tInfo.matWorld);
	D3DXMatrixIdentity(&m_tInfo.matWorld); // 다이렉트 항등행렬 함수

	m_tInfo.vPos = { 400.f, 300.f, 0.f }; // x, y, z
	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	m_tInfo.vSize = { 1.f, 1.f, 0.f };

	m_tFrame.fCurFrame = 0.f;
	m_tFrame.fMaxFrame = 11.f;
	
	return S_OK;
}

void CPlayer::Release()
{
}

CPlayer* CPlayer::Create()
{
	CPlayer* pInstance = new CPlayer;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
