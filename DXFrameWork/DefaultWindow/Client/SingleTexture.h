#pragma once
#include "Texture.h"
class CSingleTexture : public CTexture
{
private:
	CSingleTexture();

public:
	virtual ~CSingleTexture();

public:
	virtual const TEX_INFO* GetTexInfo(
		const wstring& wstrStateKey = L"",
		const WORD& wIndex = 0) const override;

public:
	// CTexture을(를) 통해 상속됨
	virtual HRESULT LoadTexture(
		LPDIRECT3DDEVICE9 pGraphicDev,
		const wstring& wstrFilePath, 
		const wstring& wstrStateKey = L"", 
		const WORD& wCnt = 0) override;
	virtual void Release() override;

public:
	static CSingleTexture* Create(
		LPDIRECT3DDEVICE9 pGraphicDev,
		const wstring& wstrFilePath,
		const wstring& wstrStateKey = L"",
		const WORD& wCnt = 0);

private:
	TEX_INFO*	m_pTexInfo;
};

