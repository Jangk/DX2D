#pragma once
#include "GameObject.h"
class CPlayer;
class CCost :
	public CGameObject
{
private:
	CCost();
public:
	~CCost();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CCost* Create();

private:
	CPlayer*		m_Player;
	TCHAR			m_szCost[MIN_STR];
};

