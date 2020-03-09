#pragma once
#include "GameObject.h"
class CCharacter;
class CHPBar : public CGameObject
{
private:
	CHPBar();
public:
	~CHPBar();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CHPBar* Create(CCharacter* target);

private:
	CCharacter* m_Target;
	D3DXVECTOR3 m_vecDefaultScale;
	float m_fRatio;
};

