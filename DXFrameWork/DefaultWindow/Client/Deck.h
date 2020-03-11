#pragma once
#include "GameObject.h"
class CDeck :
	public CGameObject
{
private:
	CDeck();
public:
	virtual ~CDeck();

	// CGameObject을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;
};

