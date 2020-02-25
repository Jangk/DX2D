#include "stdafx.h"
#include "AttackCard.h"

// 해야할것 
// 카드 테두리 3장 (스킬, 공격, 파워)
// 카드 리본 글씨 폰트 


CAttackCard::CAttackCard()
{
}

CAttackCard::~CAttackCard()
{
}

int CAttackCard::Update()
{
	return NO_EVENT;
}

void CAttackCard::LateUpdate()
{
}

void CAttackCard::Render()
{
	const TEX_INFO* pTexInfo;
	float fCenterX;
	float fCenterY;
	
	D3DXMATRIX matScale, matWorld;
	// 카드 이미지
	pTexInfo = m_pTextureMgr->GetTexInfo(L"Card", L"Attack", 0);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
	
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.1);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans * m_tInfo.matGRotate * m_tInfo.matParents;
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	// 카드 배경
	pTexInfo = m_pTextureMgr->GetTexInfo(L"AttackBackground");
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 1);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans * m_tInfo.matGRotate * m_tInfo.matParents;
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	// 카드 이름표
	pTexInfo = m_pTextureMgr->GetTexInfo(L"Card", L"CardName", 0);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans * m_tInfo.matGRotate * m_tInfo.matParents;
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	

	// 카드 외곽선
	pTexInfo = m_pTextureMgr->GetTexInfo(L"Card", L"AttackOutline", 0);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.1);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans * m_tInfo.matGRotate * m_tInfo.matParents;
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CAttackCard::Initialize()
{
	m_tInfo.vPos	= { 800.f, 300.f, 0.f }; // x, y, z
	D3DXMatrixScaling(&m_tInfo.matScale, 0.5, 0.5, 1);
	SetRotate(20.f);

	return S_OK;
}

void CAttackCard::Release()
{
}

CAttackCard * CAttackCard::Create()
{
	CAttackCard* pInstance = new CAttackCard;
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CAttackCard::SetRotate(float fAngle)
{
	D3DXMatrixRotationZ(&m_tInfo.matRotate, D3DXToRadian(fAngle));
}
