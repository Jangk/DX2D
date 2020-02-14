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
		const wstring& wstrFilePath, /* �ؽ�ó ��� */
		const wstring& wstrObjectKey, /* ������Ʈ Ű */
		const wstring& wstrStateKey = L"", /* ���� Ű */
		const WORD& wCnt = 0 /* �ؽ�ó ī��Ʈ */);

private:
	void Release();

private:
	map<wstring, CTexture*>	m_mapTexture;
};

