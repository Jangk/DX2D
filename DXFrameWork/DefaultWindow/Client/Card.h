#pragma once
#include "GameObject.h"
class CCard :
	public CGameObject
{
protected:
	CCard();
public:
	~CCard();

	// Getter Inline
public:
	inline bool IsSelect() 	{
		return m_bIsSelect;
	}
	inline float GetCardX()	{
		return m_fCardX;
	}
	inline float GetCardY()	{
		return m_fCardY;
	}
	inline float GetImageScale(){
		return m_fImageSacle;
	}


	// Setter Inline
public :
	inline void SetSelect(bool bSet) {
		m_bIsSelect = bSet;
	}
	inline void SetRender(bool bSet) {
		m_bIsRender = bSet;
	}


public:
	CARD_TYPE m_eCardType;
	bool m_bIsSelect;
	bool m_bIsRender;
	float m_fCardX;
	float m_fCardY;
	float m_fImageSacle;

};

