#include "stdafx.h"
#include "SkillCard.h"

// 해야할것 


CSkillCard::CSkillCard():
	m_eSkillCardType(SKILL_CARD_1)
{
}

CSkillCard::~CSkillCard()
{
}

int CSkillCard::Update()
{
	return NO_EVENT;
}

void CSkillCard::LateUpdate()
{
	if (m_bIsSelect)
	{
		SetPos(m_tInfo.vPos.x, 600, 0);
		SetRotate(0);
		SetScale(m_fImageSacle * 2, m_fImageSacle * 2, 0);
	}
}

void CSkillCard::Render()
{
	const TEX_INFO* pTexInfo;
	float fCenterX;
	float fCenterY;
	
	D3DXMATRIX matScale, matWorld;
	// 카드 이미지
	pTexInfo = m_pTextureMgr->GetTexInfo(L"Card", L"Skill", m_eSkillCardType);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
	
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z + 0.01);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans * m_tInfo.matGRotate * m_tInfo.matParents;
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	// 카드 배경
	pTexInfo = m_pTextureMgr->GetTexInfo(L"SkillBackground");
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z + 0.02);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans * m_tInfo.matGRotate * m_tInfo.matParents;
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	// 카드 이름표
	pTexInfo = m_pTextureMgr->GetTexInfo(L"Card", L"CardName", 1);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z + 0);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans * m_tInfo.matGRotate * m_tInfo.matParents;
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	

	// 카드 외곽선
	pTexInfo = m_pTextureMgr->GetTexInfo(L"Card", L"SkillOutline", 0);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height* 0.5f;

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z + 0.01);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans * m_tInfo.matGRotate * m_tInfo.matParents;
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CSkillCard::Initialize()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"SkillBackground");
	m_eCardType		= CARD_TYPE_SKILL;
	m_fCardX		= pTexInfo->tImgInfo.Width;
	m_fCardY		= pTexInfo->tImgInfo.Height;
	m_tInfo.vPos	= { 800.f, 300.f, 0.f }; // x, y, z
	D3DXMatrixScaling(&m_tInfo.matScale, m_fImageSacle, m_fImageSacle, 1);

	return S_OK;
}

void CSkillCard::Release()
{
}

CSkillCard * CSkillCard::Create()
{
	CSkillCard* pInstance = new CSkillCard;
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CSkillCard::SetCard(SKILL_CARD_TYPE type)
{
	m_eSkillCardType = type;
}
