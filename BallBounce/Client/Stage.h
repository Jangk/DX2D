#pragma once
#include "Scene.h"
class CPlayer;
class Block;
class CStage : public CScene
{
private:
	CStage();

public:
	virtual ~CStage();

public:
	// CScene을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CStage* Create();

private:
	vector<Block*> m_vecMap;
	D3DXVECTOR3 m_vStartPos;
	CPlayer* m_Player;
	HRESULT hr;

	CObjectMgr*	m_pObjectMgr;
	int m_iLevel;
};

