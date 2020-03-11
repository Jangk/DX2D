#include "stdafx.h"
#include "AttackCard.h"
#include "Character.h"

CAttackCard::CAttackCard():
	m_eAttackCardType(ATTACK_CARD_1)
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
	if (m_CardInfo.bIsSelect)
	{
		SetRotate(0);
		SetScale(m_CardInfo.fImageSacle * 2, m_CardInfo.fImageSacle * 2, 0);
	}
}

void CAttackCard::Render()
{
	if (!m_CardInfo.bIsRender)
		return;
	const TEX_INFO* pTexInfo;
	
	// 카드 렌더
	{	// 카드 이미지
		pTexInfo = m_pTextureMgr->GetTexInfo(L"Card", L"Attack", m_eAttackCardType);
		NULL_CHECK(pTexInfo);

		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z + (float)0.01);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans * m_tInfo.matGRotate * m_tInfo.matParents;
		m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(m_tInfo.fCenterX, m_tInfo.fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


		// 카드 배경
		pTexInfo = m_pTextureMgr->GetTexInfo(L"AttackBackground");
		NULL_CHECK(pTexInfo);

		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z + (float)0.02);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans * m_tInfo.matGRotate * m_tInfo.matParents;
		m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(m_tInfo.fCenterX, m_tInfo.fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


		// 카드 이름표
		pTexInfo = m_pTextureMgr->GetTexInfo(L"Card", L"CardName", 0);
		NULL_CHECK(pTexInfo);

		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z + (float)0.01);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans * m_tInfo.matGRotate * m_tInfo.matParents;
		m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(m_tInfo.fCenterX, m_tInfo.fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


		// 카드 외곽선
		pTexInfo = m_pTextureMgr->GetTexInfo(L"Card", L"AttackOutline", 0);
		NULL_CHECK(pTexInfo);

		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z + (float)0.01);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matRotate * m_tInfo.matTrans * m_tInfo.matGRotate * m_tInfo.matParents;
		m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(m_tInfo.fCenterX, m_tInfo.fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}


	// 폰트 
	{
		D3DXMATRIX matScale, matTrans, matWorld;
		// 카드 이름
		D3DXMatrixScaling(&matScale, m_CardInfo.fImageSacle * 10, m_CardInfo.fImageSacle * 10, 1);
		D3DXMatrixTranslation(&matTrans, -(float)m_CardInfo.iNamePositionFix, -(float)375, (float)0.01);
		matWorld = matScale * matTrans * m_tInfo.matWorld;
		m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
		m_pDeviceMgr->GetFont()->DrawText(
			m_pDeviceMgr->GetSprite(),
			m_CardInfo.szHead,
			lstrlen(m_CardInfo.szHead),
			nullptr,
			0,
			D3DCOLOR_ARGB(255, 0, 0, 0));

		// 카드 타입
		D3DXMatrixScaling(&matScale, m_CardInfo.fImageSacle * 8, m_CardInfo.fImageSacle * 8, 1);
		D3DXMatrixTranslation(&matTrans, -40, 20, (float)0.01);
		matWorld = matScale * matTrans * m_tInfo.matWorld;
		m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
		m_pDeviceMgr->GetFont()->DrawText(
			m_pDeviceMgr->GetSprite(),
			m_CardInfo.szType,
			lstrlen(m_CardInfo.szType),
			nullptr,
			0,
			D3DCOLOR_ARGB(255, 0, 0, 0));

		// 카드 내용
		D3DXMatrixScaling(&matScale, m_CardInfo.fImageSacle * 8, m_CardInfo.fImageSacle * 8, 1);
		D3DXMatrixTranslation(&matTrans, -220, 120, (float)0.01);
		matWorld = matScale * matTrans * m_tInfo.matWorld;
		m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
		m_pDeviceMgr->GetFont()->DrawText(
			m_pDeviceMgr->GetSprite(),
			m_CardInfo.szInfo,
			lstrlen(m_CardInfo.szInfo),
			nullptr,
			0,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

HRESULT CAttackCard::Initialize()
{
	const TEX_INFO* pTexInfo	= m_pTextureMgr->GetTexInfo(L"AttackBackground");
	m_CardInfo.eCardType		= CARD_TYPE_ATTACK;
	m_tInfo.fCenterX			= (float)pTexInfo->tImgInfo.Width  * 0.5f;
	m_tInfo.fCenterY			= (float)pTexInfo->tImgInfo.Height * 0.5f;
	m_tInfo.vPos				= { 800.f, 300.f, 0.f }; // x, y, z
	D3DXMatrixScaling(&m_tInfo.matScale, m_CardInfo.fImageSacle, m_CardInfo.fImageSacle, 1);
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

void CAttackCard::SetCard(ATTACK_CARD_TYPE type)
{
	m_eAttackCardType = type;
	FontInit();
}

void CAttackCard::FontInit()
{
	swprintf_s(m_CardInfo.szType, L"공격");
	switch (m_eAttackCardType)
	{
	case ATTACK_CARD_1:	
		m_CardInfo.eTargetType		= TARGET_MONSTER;
		m_CardInfo.iCost			= 1;
		m_CardInfo.iAtt				= 6;
		swprintf_s(m_CardInfo.szHead, L"타격");
		swprintf_s(m_CardInfo.szInfo, L"피해를 %d 줍니다.", m_CardInfo.iAtt);
		break;
	case ATTACK_CARD_2:		// 마무리
		m_CardInfo.eTargetType		= TARGET_MONSTER;
		m_CardInfo.iCost				= 1;
		m_CardInfo.iAtt				= 6;
		swprintf_s(m_CardInfo.szHead, L"마무리");
		swprintf_s(m_CardInfo.szInfo, L"이번 턴에 사용한 공격 카드 \n1장당 피해를 %d 줍니다.", m_CardInfo.iAtt);
		break;
	case ATTACK_CARD_3:			
		m_CardInfo.eTargetType		= TARGET_MONSTER;
		m_CardInfo.iCost				= 1;
		m_CardInfo.iAtt				= 9;
		swprintf_s(m_CardInfo.szHead, L"단검 투척");
		swprintf_s(m_CardInfo.szInfo, L"피해를 %d 줍니다. \n카드를 1장 뽑습니다. \n카드를 1장 버립니다.", m_CardInfo.iAtt);
		break;
	case ATTACK_CARD_4:	
		m_CardInfo.eTargetType		= TARGET_ALL;
		m_CardInfo.iCost			= 1;
		m_CardInfo.iAtt				= 4;
		m_CardInfo.iAttCount		= 2;
		swprintf_s(m_CardInfo.szHead, L"단검 분사");
		swprintf_s(m_CardInfo.szInfo, L"적 전체에게 피해를 %d 만큼 \n2번 줍니다.", m_CardInfo.iAtt);
		break;
	case ATTACK_CARD_5:	
		m_CardInfo.eTargetType		= TARGET_MONSTER;
		m_CardInfo.iCost			= 1;
		m_CardInfo.iAtt				= 6;
		m_CardInfo.iSpecial			= 3;
		swprintf_s(m_CardInfo.szHead, L"독 찌르기");
		swprintf_s(m_CardInfo.szInfo, L"피해를 %d 줍니다. \n중독을 %d부여합니다.", m_CardInfo.iAtt, m_CardInfo.iSpecial);
		break;
	case ATTACK_CARD_6:
		m_CardInfo.eTargetType		= TARGET_MONSTER;
		m_CardInfo.iCost			= 1;
		m_CardInfo.iAtt				= 7;
		swprintf_s(m_CardInfo.szHead, L"파멸");
		swprintf_s(m_CardInfo.szInfo, L"피해를 %d 줍니다. \n적이 중독된 상태면 다시 \n피해를 %d 줍니다.", m_CardInfo.iAtt, m_CardInfo.iAtt);
		break;
	case ATTACK_CARD_7:
		m_CardInfo.eTargetType		= TARGET_MONSTER;
		m_CardInfo.iCost			= 0;
		m_CardInfo.iAtt				= 12;
		swprintf_s(m_CardInfo.szHead, L"능숙한 찌르기");
		swprintf_s(m_CardInfo.szInfo, L"이번 전투 중 체력을 \n잃을 때마다 이 카드의 \n비용이 %d 증가합니다. \n피해를 %d 줍니다.", 1, m_CardInfo.iAtt);
		break;
	case ATTACK_CARD_8:
		m_CardInfo.eTargetType		= TARGET_MONSTER;
		m_CardInfo.iCost				= 0;
		m_CardInfo.iAtt				= 3;
		m_CardInfo.iSpecial			= 1;
		swprintf_s(m_CardInfo.szHead, L"무력화");
		swprintf_s(m_CardInfo.szInfo, L"피해를 %d 줍니다. \n약화를 %d 부여합니다.", m_CardInfo.iAtt, m_CardInfo.iSpecial);
		break;
	case ATTACK_CARD_9:		
		m_CardInfo.eTargetType		= TARGET_MONSTER;
		m_CardInfo.iCost				= 2;
		m_CardInfo.iAtt				= 10;
		m_CardInfo.iDef				= 10;
		swprintf_s(m_CardInfo.szHead, L"돌진");
		swprintf_s(m_CardInfo.szInfo, L"피해를 %d 줍니다. \n뽑을 카드 더미에 \n*어지러움을 섞어 넣습니다.", m_CardInfo.iAtt);
		break;
	case ATTACK_CARD_10:	
		m_CardInfo.eTargetType		= TARGET_ALL;
		m_CardInfo.iCost			= 1;
		m_CardInfo.iAtt				= 13;
		swprintf_s(m_CardInfo.szHead, L"죽어 죽어 죽어");
		swprintf_s(m_CardInfo.szInfo, L"적 전체에게 피해를 %d줍니다. \n소멸.", m_CardInfo.iAtt);
		break;
	}
	m_CardInfo.iNamePositionFix = lstrlen(m_CardInfo.szHead) * 20;
}

bool CAttackCard::ActivateCard(CCharacter * target)
{
	if (!CCard::IsUseCard(target))
		return false;

	// 대미지 및 쉴드 CCard::IsUseCard로 옴김
	if (m_CardInfo.iSpecial > 0)
	{
		// 이제 특수 기술이 먼지 확인할것.
	}
		
		
	return true;
}
