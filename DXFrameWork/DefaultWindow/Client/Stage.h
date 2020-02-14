#pragma once
#include "Scene.h"
class CStage : public CScene
{
private:
	CStage();

public:
	virtual ~CStage();

public:
	// CScene��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CStage* Create();

private:
	CObjectMgr*	m_pObjectMgr;
};

