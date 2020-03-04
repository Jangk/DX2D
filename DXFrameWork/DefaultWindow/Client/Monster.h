#pragma once
#include "GameObject.h"
class CMonster : public CGameObject
{
public:
	CMonster();
	~CMonster();


public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CMonster* Create();

private:
	FRAME			m_tFrame;
};

