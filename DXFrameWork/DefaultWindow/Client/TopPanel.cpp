#include "stdafx.h"
#include "TopPanel.h"
#include "Player.h"


CTopPanel::CTopPanel()
{
}


CTopPanel::~CTopPanel()
{
}

int CTopPanel::Update()
{
	return 0;
}

void CTopPanel::LateUpdate()
{
}

void CTopPanel::Render()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"UI", L"TopPanel", 1);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CTopPanel::Initialize()
{
	m_Player			= CObjectMgr::GetInstance()->GetPlayer();
	m_tInfo.vPos		= {WINCX*0.5f, 0, 0};
	D3DXMatrixScaling(&m_tInfo.matScale, 1, 1, 1);
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 1);
	m_tInfo.matWorld	= m_tInfo.matScale * m_tInfo.matTrans;
	return S_OK;
}

void CTopPanel::Release()
{
}
