#pragma once
#include "Scene.h"
class CLogo : public CScene
{
private:
	CLogo();

public:
	virtual ~CLogo();


public:
	// CScene��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CLogo* Create();

private:
	CKeyMgr*	m_pKeyMgr;
};

