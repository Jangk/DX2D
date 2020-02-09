#pragma once
#include "Texture.h"
class MultiTexture : public Texture
{
private:
public:
	MultiTexture();
	virtual ~MultiTexture();

public:
	// Texture을(를) 통해 상속됨
	virtual const TEX_INFO* GetTexInfo(
		const wstring& wstrStateKey = L"", 
		const WORD& wCnt = 0) override;

	virtual HRESULT LoadTexture(LPDIRECT3DDEVICE9 pGraphicDev, 
		const wstring& wstrFilePath, 
		const wstring& wstrStateKey, 
		const WORD& wCnt) override;

	static MultiTexture* Create(
		LPDIRECT3DDEVICE9 pGraphicDev,
		const wstring& wstrFilePath,
		const wstring& wstrStateKey,
		const WORD& wCnt);

	virtual void Release() override;

private:
	map<wstring, vector<TEX_INFO*>>	 m_mapMulti;
};

