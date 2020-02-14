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
	virtual void UpdateTotalInfo() PURE;
	virtual void SetPos(float x, float y, float z)PURE;
	const TOTAL_INFO& GetTotalInfo();
	void IsDead();

protected:
	virtual HRESULT Initialize() PURE;
	virtual void Release() PURE;

protected:
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;	
	TOTAL_INFO		m_TotalInfo;
	bool m_bIsDead = false;
};

