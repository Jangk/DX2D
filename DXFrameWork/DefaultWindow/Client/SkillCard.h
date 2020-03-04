#pragma once
#include "Card.h"
class CSkillCard : public CCard
{
private:
	CSkillCard();
public:
	~CSkillCard();

	// CCard을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CSkillCard* Create();
	void SetCard(SKILL_CARD_TYPE type);
private:
	SKILL_CARD_TYPE m_eSkillCardType;
};

