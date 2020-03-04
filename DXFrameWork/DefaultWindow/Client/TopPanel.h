#pragma once
#include "GameObject.h"
class CPlayer;
class CTopPanel : public CGameObject
{
private:
	CTopPanel();
	~CTopPanel();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:

private:
	CPlayer* m_Player;
};

