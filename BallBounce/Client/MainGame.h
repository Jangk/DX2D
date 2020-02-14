#pragma once

class CMainGame
{
private:
	CMainGame();

public:
	~CMainGame();

public:	
	void Update();
	void LateUpdate();
	void Render();

private:
	HRESULT Initialize();
	void Release();

public:
	static CMainGame* Create();

private:
	HDC m_hDC;

	CKeyMgr*			m_pKeyMgr;
	CDeviceMgr*			m_pDeviceMgr;
	CTextureMgr*		m_pTextureMgr;
	CObjectMgr*			m_pObjectMgr;
	CTimeMgr*			m_pTimeMgr;
	CSceneMgr*			m_pSceneMgr;
	CSoundMgr*			m_pSoundMgr;


	int					m_iEvent;
};

