#include "stdafx.h"
#include "Card.h"


CCard::CCard()
	: m_eCardType(CARD_TYPE_ATTACK),
	m_fImageSacle(0.25f),		// 사진크기가 너무 커서 4분의 1로 출력할거임.
	m_bIsSelect(false)
{
}


CCard::~CCard()
{
}