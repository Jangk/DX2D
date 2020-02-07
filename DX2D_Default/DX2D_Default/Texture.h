#pragma once
class Texture
{
protected:
	Texture();

public:
	virtual ~Texture();

public:
	virtual const TEX_INFO* GetTexInfo(
		const wstring& wstrStateKey = L"",
		const WORD& wCnt = 0) PURE;


	virtual HRESULT LoadTexture(
		LPDIRECT3DDEVICE9 pGraphicDev,
		const wstring& wstrFilePath, /* 텍스처 경로 */
		const wstring& wstrStateKey = L"", /* 상태 키 */
		const WORD& wCnt = 0 /* 텍스처 카운트 */) PURE;
	virtual void Release() PURE;

protected:
		TEX_INFO* m_pTexInfo;
};

