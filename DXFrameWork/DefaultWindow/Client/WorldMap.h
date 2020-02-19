#pragma once
#include "Scene.h"
class CWorldMap :
	public CScene
{
public:
	CWorldMap();
	~CWorldMap();

public:
	// CScene을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CWorldMap* Create();


public:
	CScrollMgr* m_pScrollMgr;
	vector<D3DVECTOR*> m_vecWorldMap;
	
	float m_fImageScaleX;
	float m_fImageScaleY;
	float m_fWorldMapCX;
	float m_fWorldMapCY;
};

