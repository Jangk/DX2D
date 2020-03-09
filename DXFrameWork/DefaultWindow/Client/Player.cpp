#include "stdafx.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "HPBar.h"

CPlayer::CPlayer()
	: m_pKeyMgr(CKeyMgr::GetInstance()),
	m_eState(PLAYER_IDLE)
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
	m_HPBar->Update();
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta()* 0.25f;

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
		m_tFrame.fCurFrame = 0.f;
	return NO_EVENT;
}

void CPlayer::LateUpdate()
{
	m_HPBar->LateUpdate();
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
	m_HPBar->Render();
	wstring strState;
	switch (m_eState)
	{
	case PLAYER_IDLE:
		strState = L"Idle";
		break;
	case PLAYER_HIT:
		strState = L"Hit";
		break;
	case PLAYER_DEAD:
		strState = L"Dead";
		break;
	// PLAYER_CAMPFIRE는 휴식씬에서만 사용
	}

	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Player", strState, (int)m_tFrame.fCurFrame);
	NULL_CHECK(pTexInfo);

	D3DXMatrixScaling(&m_tInfo.matScale, 1, 1, 1);
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 1);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(m_CharacterInfo.m_fCenterX, m_CharacterInfo.m_fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CPlayer::Initialize()
{	// m_tInfo 초기화는 CGameObject 생성자에서 처리함.
	m_tInfo.vPos		= { 300.f, 550.f, 0 };
	m_tFrame.fCurFrame	= 0.f;
	m_tFrame.fMaxFrame	= 53.f;
	

	// 캐릭터
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Player", L"Idle", 0);
	NULL_CHECK_RETURN(pTexInfo, E_FAIL);

	m_CharacterInfo.m_iMaxHP	= 70;
	m_CharacterInfo.m_iCurHP	= m_CharacterInfo.m_iMaxHP;
	m_CharacterInfo.m_fCenterX	= pTexInfo->tImgInfo.Width * 0.5f;
	m_CharacterInfo.m_fCenterY	= pTexInfo->tImgInfo.Height * 0.5f;

	// 플레이가 사라지면 자동으로 사라지게
	m_HPBar = CHPBar::Create(this);
	return S_OK;
}

void CPlayer::Release()
{
	SafeDelete<CHPBar*>(m_HPBar);
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