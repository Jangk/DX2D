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
		const wstring& wstrFilePath, /* �ؽ�ó ��� */
		const wstring& wstrStateKey = L"", /* ���� Ű */
		const WORD& wCnt = 0 /* �ؽ�ó ī��Ʈ */) PURE;
	virtual void Release() PURE;

protected:
		TEX_INFO* m_pTexInfo;
};

