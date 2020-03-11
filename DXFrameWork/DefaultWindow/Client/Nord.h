#pragma once
#include "GameObject.h"
class CNord : public CGameObject
{
private:
	CNord();
public:
	~CNord();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;


public:
	static CNord* Create();
	void SetNord(NORD_TYPE eType);
	bool IsPicking();

private:
	CKeyMgr* m_pKeyMgr;
	NORD_TYPE m_eNord;
	bool m_bIsPicking;
};

