#pragma once
#include "GameObject.h"
class CTomb :
	public CGameObject
{
private:
	CTomb();
public:
	virtual ~CTomb();

	// CGameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;
};

