#include "stdafx.h"
#include "SingleTexture.h"


CSingleTexture::CSingleTexture()
	: m_pTexInfo(nullptr)
{
}


CSingleTexture::~CSingleTexture()
{
	Release();
}

const TEX_INFO* CSingleTexture::GetTexInfo(
	const wstring& wstrStateKey, 
	const WORD& wIndex) const
{
	return m_pTexInfo;
}

HRESULT CSingleTexture::LoadTexture(
	LPDIRECT3DDEVICE9 pGraphicDev,
	const wstring& wstrFilePath, 
	const wstring& wstrStateKey/* = L""*/, 
	const WORD& wCnt/* = 0*/)
{
	D3DXIMAGE_INFO	tImgInfo; // �̹��� ������ �����ϱ� ���� ����ü ����.
	ZeroMemory(&tImgInfo, sizeof(D3DXIMAGE_INFO));

	// �̹��� ���� ������ �Լ�.
	HRESULT hr = D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &tImgInfo);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXGetImageInfoFromFile Failed", E_FAIL);

	// IDirect3DTexture9�� ������
	// IDirect3DTexture9: �ؽ�ó ���ҽ��� ���� �ִ� COM��ü.
	LPDIRECT3DTEXTURE9 pTexture = nullptr;

	// �ؽ�ó Com��ü ���� �Լ�
	hr = D3DXCreateTextureFromFileEx(
		pGraphicDev, /* ��ġ */
		wstrFilePath.c_str(), /* �ؽ�ó ��� */
		tImgInfo.Width, /* ������ �ؽ�ó ���� ũ�� */
		tImgInfo.Height, /* ������ �ؽ�ó ���� ũ�� */
		tImgInfo.MipLevels,
		0,
		tImgInfo.Format,
		D3DPOOL_MANAGED, /* �޸� ���� ��� */
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr,
		nullptr,
		&pTexture);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateTextureFromFileEx Failed", E_FAIL);

	m_pTexInfo = new TEX_INFO;
	m_pTexInfo->pTexture = pTexture;
	m_pTexInfo->tImgInfo = tImgInfo;

	return S_OK;
}

void CSingleTexture::Release()
{

	m_pTexInfo->pTexture->Release();
	SafeDelete(m_pTexInfo);
}

CSingleTexture* CSingleTexture::Create(
	LPDIRECT3DDEVICE9 pGraphicDev, 
	const wstring& wstrFilePath, 
	const wstring& wstrStateKey, 
	const WORD& wCnt)
{
	CSingleTexture* pInstance = new CSingleTexture;

	if (FAILED(pInstance->LoadTexture(pGraphicDev, wstrFilePath, wstrStateKey, wCnt)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
