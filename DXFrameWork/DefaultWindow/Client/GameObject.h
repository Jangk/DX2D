#pragma once

class CGameObject
{
protected:
	CGameObject();

public:
	virtual ~CGameObject();

public:
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;

protected:
	virtual HRESULT Initialize() PURE;
	virtual void Release() PURE;


public:
	void SetPos(float x, float y, float z);
	void SetRotate(float angle);
	void SetScale(float x, float y, float z);
	const INFO& GetInfo();
	D3DXVECTOR3 GetScale();
	void MoveTo(D3DXVECTOR3 vecTarget, float fSpeed);
	D3DXVECTOR3 MyLerp(D3DXVECTOR3 start, D3DXVECTOR3 end, float fSpeed);
	

protected:
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;	
	CTimeMgr*		m_pTimeMgr;
	CObjectMgr*     m_pObjectMgr;
	CGameMgr*		m_pGameMgr;
	CKeyMgr*		m_pKeyMgr;

	INFO			m_tInfo;
};

