#pragma once
#include "GameObject.h"

class CHPBar;
class CCharacter : public CGameObject
{
protected:
	CCharacter();
public:
	~CCharacter();

public:
	const CHARACTER_INFO& GetCharacterInfo();
	void SetDamage(int iDamage);

protected:
	FRAME			m_tFrame;
	CHARACTER_INFO	m_CharacterInfo;
	CHPBar*			m_HPBar;
};

