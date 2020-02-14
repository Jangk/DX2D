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
	D3DXIMAGE_INFO	tImgInfo; // 이미지 정보를 보관하기 위한 구조체 변수.
	ZeroMemory(&tImgInfo, sizeof(D3DXIMAGE_INFO));

	// 이미지 정보 얻어오는 함수.
	HRESULT hr = D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &tImgInfo);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXGetImageInfoFromFile Failed", E_FAIL);

	// IDirect3DTexture9의 포인터
	// IDirect3DTexture9: 텍스처 리소스를 갖고 있는 COM객체.
	LPDIRECT3DTEXTURE9 pTexture = nullptr;

	// 텍스처 Com객체 생성 함수
	hr = D3DXCreateTextureFromFileEx(
		pGraphicDev, /* 장치 */
		wstrFilePath.c_str(), /* 텍스처 경로 */
		tImgInfo.Width, /* 생성할 텍스처 가로 크기 */
		tImgInfo.Height, /* 생성할 텍스처 세로 크기 */
		tImgInfo.MipLevels,
		0,
		tImgInfo.Format,
		D3DPOOL_MANAGED, /* 메모리 보관 방식 */
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
