#include "stdafx.h"
#include "HPBar.h"
#include "Player.h"
#include "Character.h"


CHPBar::CHPBar()
{
}


CHPBar::~CHPBar()
{
	Release();
}

int CHPBar::Update()
{
	return 0;
}

void CHPBar::LateUpdate()
{
}

void CHPBar::Render()
{
	D3DXMATRIX matScale, matTrans,matWorld;
	const TEX_INFO* pTexInfo;

	// 최대체력바
	pTexInfo = m_pTextureMgr->GetTexInfo(L"UI", L"MaxHP", 1);
	NULL_CHECK(pTexInfo);

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(0, m_tInfo.fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	// 현재 체력바
	pTexInfo = m_pTextureMgr->GetTexInfo(L"UI", L"CurHP", 1);
	NULL_CHECK(pTexInfo);

	matWorld = m_tInfo.matWorld;
	D3DXMatrixScaling(
		&matScale, 
		m_fRatio * (float)m_Target->GetCharacterInfo().iCurHP,
		1.5,
		1);
	matWorld = matScale * m_tInfo.matTrans;
	m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(0, m_tInfo.fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	// 쉴드 체력바
	pTexInfo = m_pTextureMgr->GetTexInfo(L"UI", L"SheildHP", 1);
	NULL_CHECK(pTexInfo);

	matWorld = m_tInfo.matWorld;
	D3DXMatrixScaling(
		&matScale,
		m_fRatio * (float)m_Target->GetCharacterInfo().iSheild,
		1.5,
		1);
	matWorld = matScale * m_tInfo.matTrans;
	m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(0, m_tInfo.fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	// 체력 폰트
	swprintf_s(m_szHPText, L"%d/%d", m_Target->GetCharacterInfo().iCurHP, m_Target->GetCharacterInfo().iMaxHP);
	D3DXMatrixScaling(&matScale, 0.8f, 0.8f, 1.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + 100, m_tInfo.vPos.y- 10, 0.8f);
	matWorld = matScale * matTrans;
	m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
	m_pDeviceMgr->GetFont()->DrawText(
		m_pDeviceMgr->GetSprite(),
		m_szHPText,
		lstrlen(m_szHPText),
		nullptr,
		0,
		D3DCOLOR_ARGB(255, 0, 0, 0));
}

HRESULT CHPBar::Initialize()
{
	const TEX_INFO* pTexInfo	= m_pTextureMgr->GetTexInfo(L"UI", L"MaxHP", 1);
	m_tInfo.fCenterX			= pTexInfo->tImgInfo.Width  * 0.5f;
	m_tInfo.fCenterY			= pTexInfo->tImgInfo.Height * 0.5f;
	m_tInfo.vPos				= { m_Target->GetInfo().vPos.x -130,  m_Target->GetInfo().vPos.y + 150, 1};
	m_vecDefaultScale			= { 2, 1.5, 1 };
	D3DXMatrixScaling(&m_tInfo.matScale, m_vecDefaultScale.x, m_vecDefaultScale.y, m_vecDefaultScale.z);
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.9f);
	m_tInfo.matWorld			= m_tInfo.matScale * m_tInfo.matTrans;
	m_fRatio					= m_tInfo.matScale.m[0][0] / (float)m_Target->GetCharacterInfo().iMaxHP;
	return S_OK;
}

void CHPBar::Release()
{
	
}

CHPBar* CHPBar::Create(CCharacter* target)
{
	CHPBar* pInstance = new CHPBar;
	pInstance->m_Target = target;
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}