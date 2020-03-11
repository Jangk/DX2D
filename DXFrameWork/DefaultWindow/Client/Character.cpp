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
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_CharacterInfo;
}

void CCharacter::SetDamege(int i)
{	// ���⿡ Ÿ�� ����Ʈ ���� �� �ǰ� ��� �߻���Ű��.
	int iDamege = m_CharacterInfo.iSheild - i;
	m_CharacterInfo.iCurHP += iDamege;
	if (iDamege <= 0)
	{
		// ���п� ������ �Ҹ�
	}
	else
	{
		// �ǰ���.
	}
}

void CCharacter::SetSheild(int i)
{
	m_CharacterInfo.iSheild += i;
	// ���� �Ҹ�.
}