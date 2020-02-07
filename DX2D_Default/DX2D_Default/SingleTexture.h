#pragma once
#include "Texture.h"
class SingleTexture : public Texture
{
private: 
	SingleTexture();
public:
	~SingleTexture();
	// Texture을(를) 통해 상속됨
	virtual HRESULT LoadTexture(LPDIRECT3DDEVICE9 pGraphicDev, 
							    const wstring& wstrFilePath, 
							    const wstring& wstrStateKey = L"", 
							    const WORD& wCnt = 0) override;
	virtual void Release() override;

public:
	static SingleTexture* Create(
		LPDIRECT3DDEVICE9 pGraphicDev,
		const wstring& wstrFilePath,
		const wstring& wstrStateKey = L"",
		const WORD& wCnt = 0);

	// Texture을(를) 통해 상속됨
	virtual const TEX_INFO* GetTexInfo(
		const wstring& wstrStateKey = L"", 
		const WORD& wCnt = 0) override;

private:
	TEX_INFO* m_pTexInfo;


};

