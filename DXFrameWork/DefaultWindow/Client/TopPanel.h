#pragma once
#include "GameObject.h"
class CPlayer;
class CTopPanel : public CGameObject
{
private:
	CTopPanel();
	~CTopPanel();

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:

private:
	CPlayer* m_Player;
};

