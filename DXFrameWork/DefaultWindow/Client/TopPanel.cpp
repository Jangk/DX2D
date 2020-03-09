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
	m_PlayerInfo = m_Player->GetCharacterInfo();
	return 0;
}

void CTopPanel::LateUpdate()
{
}

void CTopPanel::Render()
{
	D3DXMATRIX matTextTrans;
	const TEX_INFO* pTexInfo;
	float fCenterX;
	float fCenterY;

	// �гι�
	pTexInfo = m_pTextureMgr->GetTexInfo(L"UI", L"Bar", 1);
	NULL_CHECK(pTexInfo);
	
	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
	
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	// ������
	pTexInfo = m_pTextureMgr->GetTexInfo(L"UI", L"panelHeart", 1);
	NULL_CHECK(pTexInfo);
	
	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
	
	D3DXMatrixTranslation(&matTextTrans, m_vecHeart.x, m_vecHeart.y, 0);
	m_pDeviceMgr->GetSprite()->SetTransform(&matTextTrans);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	D3DXMatrixTranslation(&matTextTrans, m_vecHeart.x + 30, m_vecHeart.y - 10, 0);
	m_pDeviceMgr->GetSprite()->SetTransform(&matTextTrans);
	swprintf_s(m_wstrUI, L"%d / %d", m_PlayerInfo.m_iCurHP, m_PlayerInfo.m_iMaxHP);
	m_pDeviceMgr->GetFont()->DrawText(
		m_pDeviceMgr->GetSprite(), /* ��������Ʈ COM ��ü */
		m_wstrUI, /* ����� ���ڿ� */
		lstrlen(m_wstrUI), /* ���ڿ� ���� */
		nullptr, /* �簢�� ���� */
		0,
		D3DCOLOR_ARGB(255, 255, 0, 0));


	// ���
	pTexInfo = m_pTextureMgr->GetTexInfo(L"UI", L"panelGoldBag", 0);
	NULL_CHECK(pTexInfo);
	
	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
	
	D3DXMatrixTranslation(&matTextTrans, m_vecGoldBag.x, m_vecGoldBag.y, 0);
	m_pDeviceMgr->GetSprite()->SetTransform(&matTextTrans);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	
	
	D3DXMatrixTranslation(&matTextTrans, m_vecGoldBag.x + 30, m_vecGoldBag.y -10, 0);
	m_pDeviceMgr->GetSprite()->SetTransform(&matTextTrans);
	swprintf_s(m_wstrUI, L"%d", m_PlayerInfo.m_iGold);
	m_pDeviceMgr->GetFont()->DrawText(
		m_pDeviceMgr->GetSprite(), 
		m_wstrUI, 
		lstrlen(m_wstrUI),
		nullptr,
		0,
		D3DCOLOR_ARGB(255, 255, 255, 0));
}

HRESULT CTopPanel::Initialize()
{
	m_Player			= CObjectMgr::GetInstance()->GetPlayer();
	m_tInfo.vPos		= {WINCX*0.5f, 40, 0};
	m_vecHeart			= { 200, 20, 0 };
	m_vecGoldBag		= { 350, 20, 0 };
	D3DXMatrixScaling(&m_tInfo.matScale, 1, 1, 1);
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0);
	m_tInfo.matWorld	= m_tInfo.matScale * m_tInfo.matTrans;
	return S_OK;
}

void CTopPanel::Release()
{
}

CTopPanel* CTopPanel::Create()
{
	CTopPanel* pInstance = new CTopPanel;
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}