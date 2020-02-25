#pragma once
#include "GameObject.h"
class CCard :
	public CGameObject
{
protected:
	CCard();
public:
	~CCard();

public:
	CARD_TYPE m_eCardType;
};

