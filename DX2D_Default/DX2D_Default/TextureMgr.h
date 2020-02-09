#pragma once
class Texture;
class TextureMgr
{
	DECLARE_SINGLETON(TextureMgr)
private:
	TextureMgr();
	~TextureMgr();

public:
	const TEX_INFO* GetTexInfo(
		const wstring& wstrObjectKey,
		const wstring& wstrStateKey = L"",
		const WORD& wIndex = 0) const;

public:
	HRESULT LoadTexture(
		LPDIRECT3DDEVICE9 pGrahicDev,
		TEXTURE_TYPE eTextureType,
		const wstring& wstrFilePath,		/* 텍스처 경로 */
		const wstring& wstrObjectKey, /* 오브젝트 키 */
		const wstring& wstrStateKey = L"", /* 상태 키 */
		const WORD& wCnt = 0 /* 텍스처 카운트 */);

public:
	HRESULT Initialize();

private:
	void Release();

private:
	map<wstring, Texture*>	m_mapTexture;

	DeviceMgr* m_pDeviceMgr;
};

