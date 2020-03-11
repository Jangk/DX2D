#pragma once
#include "GameObject.h"
class CCharacter;
class CCard :
	public CGameObject
{
protected:
	CCard();
public:
	~CCard();

	// Getter Inline
public:
	inline const CARD_INFO& GetCardInfo() {
		return m_CardInfo;
	}


	// Setter Inline
public :
	inline void SetSelect(bool bSet) {
		m_CardInfo.bIsSelect = bSet;
		SetPicking(bSet);
	}
	inline void SetRender(bool bSet) {
		m_CardInfo.bIsRender = bSet;
	}
	inline void SetPicking(bool bSet) {
		if (bSet)
		{
			SetPos(m_tInfo.vPos.x, 600, 0);
			SetRotate(0);
			SetScale(m_CardInfo.fImageSacle * 2, m_CardInfo.fImageSacle * 2, 0);
		}
		else
			SetScale(m_CardInfo.fImageSacle, m_CardInfo.fImageSacle, 0);
	}


	// 추상 함수
public:
	virtual bool ActivateCard(CCharacter* target) =0;

	// 공용함수
public:
	bool IsUseCard(CCharacter* target);

protected:
	CARD_INFO m_CardInfo;
};

