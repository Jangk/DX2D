#pragma once
#include "Texture.h"
class CMultiTexture :	public CTexture
{
public:
	CMultiTexture();
	virtual ~CMultiTexture();

public:
	virtual const TEX_INFO* GetTexInfo(
		const wstring& wstrStateKey,
		const WORD& wIndex) const override;

public:
	// CTexture을(를) 통해 상속됨
	virtual HRESULT LoadTexture(
		LPDIRECT3DDEVICE9 pGraphicDev,
		const wstring& wstrFilePath,
		const wstring& wstrStateKey,
		const WORD& wCnt) override;
	virtual void Release() override;

public:
	static CMultiTexture* Create(
		LPDIRECT3DDEVICE9 pGraphicDev,
		const wstring& wstrFilePath,
		const wstring& wstrStateKey,
		const WORD& wCnt);

private:
	map<wstring, vector<TEX_INFO*>>	 m_mapMulti;
};

