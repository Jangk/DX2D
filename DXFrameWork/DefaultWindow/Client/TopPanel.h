#pragma once
#include "GameObject.h"
class CPlayer;
class CTopPanel : public CGameObject
{
private:
	CTopPanel();
public:
	~CTopPanel();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CTopPanel* Create();
private:
	CPlayer* m_Player;
	CHARACTER_INFO m_PlayerInfo;
	D3DXVECTOR3 m_vecHeart;
	D3DXVECTOR3 m_vecGoldBag;
	TCHAR m_wstrUI[MIN_STR];
};

