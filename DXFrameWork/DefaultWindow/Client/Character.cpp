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
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_CharacterInfo;
}

void CCharacter::SetDamage(int iDamage)
{
	m_CharacterInfo.m_iCurHP -= iDamage;
}
