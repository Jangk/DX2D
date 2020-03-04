#include "stdafx.h"
#include "PowerCard.h"


CPowerCard::CPowerCard():
	m_ePowerCardType(POWER_CARD_1)
{
}

CPowerCard::~CPowerCard()
{
}

int CPowerCard::Update()
{
	return NO_EVENT;
}

void CPowerCard::LateUpdate()
{
	if (m_bIsSelect)
	{
		SetPos(m_tInfo.vPos.x, 600, 0);
		SetRotate(0);
		SetScale(m_fImageSacle * 2, m_fImageSacle * 2, 0);
	}
}

void CPowerCard::Render()
{
	const TEX_INFO* pTexInfo;
	float fCenterX;
	float fCenterY;
	
	D3DXMATRIX matScale, matWorld;
	// 카드 이미지
	pTexInfo = m_pTextureMgr->GetTexInfo(L"Card", L"Power", m_ePowerCardType);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
	
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z + 0.01);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans * m_tInfo.matGRotate * m_tInfo.matParents;
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	// 카드 배경
	pTexInfo = m_pTextureMgr->GetTexInfo(L"PowerBackground");
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z + 0.02);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans * m_tInfo.matGRotate * m_tInfo.matParents;
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	// 카드 이름표
	pTexInfo = m_pTextureMgr->GetTexInfo(L"Card", L"CardName", 2);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z + 0);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans * m_tInfo.matGRotate * m_tInfo.matParents;
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	

	// 카드 외곽선
	pTexInfo = m_pTextureMgr->GetTexInfo(L"Card", L"PowerOutline", 0);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height* 0.5f;

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z + 0.01);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans * m_tInfo.matGRotate * m_tInfo.matParents;
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CPowerCard::Initialize()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"PowerBackground");
	m_eCardType		= CARD_TYPE_POWER;
	m_fCardX		= pTexInfo->tImgInfo.Width;
	m_fCardY		= pTexInfo->tImgInfo.Height;
	m_tInfo.vPos	= { 800.f, 300.f, 0.f }; // x, y, z
	D3DXMatrixScaling(&m_tInfo.matScale, m_fImageSacle, m_fImageSacle, 1);

	return S_OK;
}

void CPowerCard::Release()
{
}

CPowerCard * CPowerCard::Create()
{
	CPowerCard* pInstance = new CPowerCard;
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CPowerCard::SetCard(POWER_CARD_TYPE type)
{
	m_ePowerCardType = type;
}
