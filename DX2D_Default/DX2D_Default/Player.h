#pragma once
#include "GameObject.h"
class Player : public GameObject
{
private:
	Player();

public:
	~Player();

public:
	void Update();
	void LateUpdate();
	void Render();

private:
	HRESULT Initialize();
	void Release();

public:
	static Player* Create();

	D3DXVECTOR3 m_vOrigin[4];
	D3DXVECTOR3 m_vConvert[4];
	
	
	
	CKeyMgr* m_pKeyMgr;
};

