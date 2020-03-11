#pragma once
#include "GameObject.h"
class CEndButton : public CGameObject
{
private:
	CEndButton();
public:
	~CEndButton();

	// CGameObject��(��) ���� ��ӵ�
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;

public:
	static CEndButton* Create();

private:
	TCHAR m_szText[MIN_STR];
	bool m_bIsRender;
	bool m_bIsPicking;
};

