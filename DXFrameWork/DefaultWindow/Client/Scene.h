#pragma once

class CScene
{
protected:
	CScene();

public:
	virtual ~CScene();

public:
	virtual int Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;

protected:
	virtual HRESULT Initialize() PURE;
	virtual void Release() PURE;

protected:
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;
	CTimeMgr*		m_pTimeMgr;
	CSceneMgr*		m_pSceneMgr;
	CObjectMgr*		m_pObjectMgr;
	CKeyMgr*		m_pKeyMgr;
	CScrollMgr*		m_pScrollMgr;
};

