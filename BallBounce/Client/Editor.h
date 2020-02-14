#pragma once
#include "Scene.h"
class Block;
class Editor :
	public CScene
{
private:
	Editor();
public:
	~Editor();
public:
	// CScene��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;


public:
	static Editor* Create();
	void Input();
	void GetMousePos();


public:
	CKeyMgr* m_pKeyMgr;
	CDeviceMgr* m_pDeviceMgr;
	CObjectMgr* m_pObjectMgr;


	vector<Block*> m_vecBlock;
	HRESULT hr;
	POINT m_ptMousePos;
	int m_iSelector;
};

