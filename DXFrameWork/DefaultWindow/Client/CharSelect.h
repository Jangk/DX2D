#pragma once
#include "Scene.h"
class CCharSelect :
	public CScene
{
public:
	CCharSelect();
	~CCharSelect();

	// CScene을(를) 통해 상속됨
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual HRESULT Initialize() override;
	virtual void Release() override;


public:
	static CCharSelect* Create();
	void LoadTextureCharacter(LPDIRECT3DDEVICE9& dev, PLAYABLE_CHARACTER eChar);
	void IsPicking();


private:
	PLAYABLE_CHARACTER m_eCurSelChar;
	D3DVECTOR m_Mouse;

	vector<BUTTON_INFO*> m_vecButton;
};

