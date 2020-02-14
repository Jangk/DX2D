#pragma once
#include "GameObject.h"
class CPlayer : public CGameObject
{
private:
	CPlayer();

public:
	~CPlayer();

public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void Render() override;
	virtual void LateUpdate()override;
	virtual void UpdateTotalInfo() override;
	virtual void SetPos(float x, float y, float z) override;


private:
	HRESULT Initialize();
	void Release();


public:
	void Input();
	void Bounce();
	void AfterImage();
	void SetColX();
	void SetColY(BLOCK_TYPE type);
	void SetRespawn(D3DXVECTOR3 respawnPos);
	bool GetIsDead();

public:
	static CPlayer* Create();

private:
	INFO			m_tInfo;
	D3DVECTOR		m_vAfterimage[10];
	bool			m_bIsCol;
	bool			m_bIsMachine;
	bool			m_bIsJump;
	float			m_fAngle;
	float			m_fSpeed;
	float			m_fJumpForce;
	float			m_fJumpAcc;
	float			m_fMoveAcc;
	int				m_vAfterImageIndex;
	int				m_iCount;

	CKeyMgr*		m_pKeyMgr;
	CTimeMgr*		m_pTimeMgr;
	CSoundMgr*		m_pSoundMgr;
};

