#include "stdafx.h"
#include "Character.h"
#include "Card.h"


CCharacter::CCharacter()
{
	m_CharacterInfo.bIsPlayer = false;
	m_CharacterInfo.iSheild = 0;
}

CCharacter::~CCharacter()
{
}

const CHARACTER_INFO& CCharacter::GetCharacterInfo()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_CharacterInfo;
}

void CCharacter::SetDamege(int i)
{	// 여기에 타격 이펙트 설정 및 피격 모션 발생시키게.
	int iDamege = m_CharacterInfo.iSheild - i;
	m_CharacterInfo.iCurHP += iDamege;
	if (iDamege <= 0)
	{
		// 방패에 막히는 소리
	}
	else
	{
		// 피격음.
	}
}

void CCharacter::SetSheild(int i)
{
	m_CharacterInfo.iSheild += i;
	// 방패 소리.
}