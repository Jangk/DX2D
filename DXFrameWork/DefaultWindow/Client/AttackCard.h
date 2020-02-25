#pragma once
#include "Card.h"
class CAttackCard : public CCard
{
private:
	CAttackCard();
public:
	~CAttackCard();

	// CCard��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CAttackCard* Create();
	void SetRotate(float fAngle);
private:
	D3DXMATRIX m_matCardUI;
};

