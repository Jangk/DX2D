#pragma once

class CTexture;
class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr)

private:
	CTextureMgr();
	~CTextureMgr();

public:
	const TEX_INFO* GetTexInfo(
		const wstring& wstrObjectKey,
		const wstring& wstrStateKey = L"",
		const WORD& wIndex = 0) const;

public:
	HRESULT LoadTexture(
		LPDIRECT3DDEVICE9 pGrahicDev,
		TEXTURE_TYPE eTextureType,		
		const wstring& wstrFilePath, /* 텍스처 경로 */
		const wstring& wstrObjectKey, /* 오브젝트 키 */
		const wstring& wstrStateKey = L"", /* 상태 키 */
		const WORD& wCnt = 0 /* 텍스처 카운트 */);

private:
	void Release();

private:
	map<wstring, CTexture*>	m_mapTexture;
};

