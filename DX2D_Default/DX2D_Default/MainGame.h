#pragma once
class Player;
class SingleTexture;
class MultiTexture;


class Tile;
class MainGame
{
private:
	MainGame();

public:
	~MainGame();

public :
	void ColMouse();

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
	CKeyMgr* m_pKeyMgr;
	DeviceMgr* m_pDeviceMgr;
	TextureMgr* m_pTextureMgr;
	
	
	int m_iIndex = 0;


	vector<Tile*> m_VecTile;


	// TestOnly;
	Tile* Test;
	HDC hdc;
};

