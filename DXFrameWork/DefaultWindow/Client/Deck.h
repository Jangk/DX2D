#pragma once
#include "GameObject.h"
class CDeck :
	public CGameObject
{
private:
	CDeck();
public:
	virtual ~CDeck();

	// CGameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;
};

