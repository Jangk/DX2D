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
		const wstring& wstrFilePath,		/* �ؽ�ó ��� */
		const wstring& wstrObjectKey, /* ������Ʈ Ű */
		const wstring& wstrStateKey = L"", /* ���� Ű */
		const WORD& wCnt = 0 /* �ؽ�ó ī��Ʈ */);

public:
	HRESULT Initialize();

private:
	void Release();

private:
	map<wstring, Texture*>	m_mapTexture;

	DeviceMgr* m_pDeviceMgr;
};

