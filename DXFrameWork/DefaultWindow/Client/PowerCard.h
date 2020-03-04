#pragma once
#include "Card.h"
class CPowerCard : public CCard
{
private:
	CPowerCard();
public:
	~CPowerCard();

	// CCard��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CPowerCard* Create();
	void SetCard(POWER_CARD_TYPE type);
private:
	POWER_CARD_TYPE m_ePowerCardType;
};

