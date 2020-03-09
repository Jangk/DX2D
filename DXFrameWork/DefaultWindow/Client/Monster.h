#pragma once
#include "Character.h"

class CMonster : public CCharacter
{
private:
	CMonster();
public:
	virtual ~CMonster();


public:
	// CGameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CMonster* Create();

private:
};

