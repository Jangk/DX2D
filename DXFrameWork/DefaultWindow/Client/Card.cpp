#include "stdafx.h"
#include "Card.h"


CCard::CCard()
	: m_eCardType(CARD_TYPE_ATTACK),
	m_fImageSacle(0.25f),		// ����ũ�Ⱑ �ʹ� Ŀ�� 4���� 1�� ����Ұ���.
	m_bIsSelect(false)
{
}


CCard::~CCard()
{
}