#pragma once
#include "GameObject.h"
class Tile : public GameObject
{
private:
	Tile();
public:
	~Tile();
public: 
	void ChangeImage(int iImageIndex);

public:
	// GameObject을(를) 통해 상속됨
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static Tile* Create();

	TextureMgr* m_pTextureMgr;
	DeviceMgr* m_pDeviceMgr;

	int m_iImageIndex;
};

