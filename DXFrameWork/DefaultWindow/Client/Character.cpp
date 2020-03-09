#include "stdafx.h"
#include "Character.h"


CCharacter::CCharacter()
{
}


CCharacter::~CCharacter()
{
}


const CHARACTER_INFO& CCharacter::GetCharacterInfo()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_CharacterInfo;
}

void CCharacter::SetDamage(int iDamage)
{
	m_CharacterInfo.m_iCurHP -= iDamage;
}
