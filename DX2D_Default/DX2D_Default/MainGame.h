#pragma once
class Player;
class SingleTexture;
class MainGame
{
private:
	MainGame();

public:
	~MainGame();

public:
	void Update();
	void LateUpdate();
	void Render();

private:
	HRESULT Initialize();
	void Release();

public:
	static MainGame* Create();

private:
	HDC m_hDC;

	Player* m_pPlayer;
	CKeyMgr* m_pKeyMgr;
	DeviceMgr* m_pDeviceMgr;
	SingleTexture* m_pSingleTex;
};

