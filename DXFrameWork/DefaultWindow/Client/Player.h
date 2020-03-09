#pragma once
#include "Character.h"

class CPlayer : public CCharacter
{
private:
	CPlayer();

public:
	~CPlayer();

public:
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CPlayer* Create();

private:
	CKeyMgr*		m_pKeyMgr;
	PLAYER_STATE	m_eState;
};

