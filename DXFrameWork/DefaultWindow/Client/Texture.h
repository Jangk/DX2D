#pragma once
class CTexture
{
protected:
	CTexture();

public:
	virtual ~CTexture();

public:
	virtual const TEX_INFO* GetTexInfo(
		const wstring& wstrStateKey = L"",
		const WORD& wIndex = 0) const PURE;

public:
	virtual HRESULT LoadTexture(
		LPDIRECT3DDEVICE9 pGraphicDev,
		const wstring& wstrFilePath, /* �ؽ�ó ��� */
		const wstring& wstrStateKey = L"", /* ���� Ű */
		const WORD& wCnt = 0 /* �ؽ�ó ī��Ʈ */) PURE;
	virtual void Release() PURE;
};

