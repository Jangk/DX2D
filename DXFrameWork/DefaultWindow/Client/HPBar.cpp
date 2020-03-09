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
	D3DXMATRIX matScale;
	D3DXMATRIX matWorld;
	const TEX_INFO* pTexInfo;
	float fCenterX;
	float fCenterY;

	// ÆÐ³Î¹Ù
	pTexInfo = m_pTextureMgr->GetTexInfo(L"UI", L"MaxHP", 1);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(0, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));



	pTexInfo = m_pTextureMgr->GetTexInfo(L"UI", L"CurHP", 1);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	matWorld = m_tInfo.matWorld;
	D3DXMatrixScaling(
		&matScale, 
		m_fRatio * (float)m_Target->GetCharacterInfo().m_iCurHP,
		1.5,
		1);
	matWorld = matScale * m_tInfo.matTrans;
	m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(0, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CHPBar::Initialize()
{
	m_tInfo.vPos		= { m_Target->GetInfo().vPos.x -130,  m_Target->GetInfo().vPos.y + 150, 1};
	m_vecDefaultScale	= { 2, 1.5, 1 };
	D3DXMatrixScaling(&m_tInfo.matScale, m_vecDefaultScale.x, m_vecDefaultScale.y, m_vecDefaultScale.z);
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0);
	m_tInfo.matWorld	= m_tInfo.matScale * m_tInfo.matTrans;
	m_fRatio			= m_tInfo.matScale.m[0][0] / (float)m_Target->GetCharacterInfo().m_iMaxHP;
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