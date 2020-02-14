#pragma once

#include "GameObject.h"

class CPlayer : public CGameObject
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
	INFO			m_tInfo;
	FRAME			m_tFrame;
	CKeyMgr*		m_pKeyMgr;
};

