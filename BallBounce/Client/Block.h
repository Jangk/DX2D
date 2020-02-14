#pragma once
#include "GameObject.h"
class Block : public CGameObject
{
public:
	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void UpdateTotalInfo() override;
	virtual void SetPos(float x, float y, float z) override;
	
private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	void SetBlock(BLOCK_TYPE eType);
	BLOCK_TYPE GetBlockType();
	TILE_INFO GetInfo();
	void SetSaveInfo(SAVE_INFO saveinfo);
	static Block* Create();



private:
	BLOCK_TYPE m_eBlockType;
	TILE_INFO m_tInfo;
};

