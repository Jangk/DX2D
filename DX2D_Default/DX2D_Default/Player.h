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
	void Render(HDC hDC);

private:
	HRESULT Initialize();
	void Release();

public:
	static Player* Create();
	float m_Angle;
};

