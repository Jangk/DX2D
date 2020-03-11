#include "stdafx.h"
#include "Card.h"
#include "Character.h"
#include "Player.h"


CCard::CCard()
{		
	m_CardInfo.eCardType		= CARD_TYPE_ATTACK;
	m_CardInfo.eTargetType		= TARGET_MONSTER;
	m_CardInfo.fImageSacle		= 0.25f;		// ����ũ�Ⱑ �ʹ� Ŀ�� 4���� 1�� ����Ұ���.
	m_CardInfo.bIsSelect		= false;
	m_CardInfo.bIsRender		= false;
	m_CardInfo.iAtt				= 0;
	m_CardInfo.iAttCount		= 1;
	m_CardInfo.iDef				= 0;
	m_CardInfo.iCost			= 0;
	m_CardInfo.iSpecial			= 0;
	m_CardInfo.iNamePositionFix	= 0;
}

CCard::~CCard()
{
}

bool CCard::IsUseCard(CCharacter* target)
{
	CPlayer* player =dynamic_cast <CPlayer*>(m_pObjectMgr->GetGameObject(OBJECT_PLAYER).front());
	bool bIsPlayer = target->GetCharacterInfo().bIsPlayer;

	switch (m_CardInfo.eTargetType)
	{
	case TARGET_ALL:
		if (bIsPlayer)
		{
			::MessageBox(g_hWnd, L"� ���",L"dd",0);
			return false;
		}
		break;

	case TARGET_MONSTER:
		if (bIsPlayer)
		{
			::MessageBox(g_hWnd, L"� ���", L"dd", 0);
			return false;
		}
		break;

	case TARGET_SELF:
		if (!bIsPlayer)
		{
			::MessageBox(g_hWnd, L"� ���", L"dd", 0);
			return false;
		}
		break;
	}

	if (m_CardInfo.iCost > player->GetCharacterInfo().iCurCost)
	{
		::MessageBox(g_hWnd, L"�ڽ�Ʈ ����", L"dd", 0);
		return false;
	}
	
	// ī�� ����.
	player->UseCost(m_CardInfo.iCost);					// �������
	for (int i = 0; i < m_CardInfo.iAttCount; ++i)
	{	// ������ ������ �����ϴ� ��츦 ����ؼ�
		if (m_CardInfo.iAtt > 0)
			target->SetDamege(m_CardInfo.iAtt);
	}

	if (m_CardInfo.iDef > 0)
		dynamic_cast<CCharacter*>(m_pObjectMgr->GetGameObject(OBJECT_PLAYER).front())->SetSheild(m_CardInfo.iDef);
	return true;
}
