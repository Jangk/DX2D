#include "pch.h"
#include "MultiTexture.h"

MultiTexture::MultiTexture()
{
}

MultiTexture::~MultiTexture()
{
}

const TEX_INFO* MultiTexture::GetTexInfo(
	const wstring& wstrStateKey, 
	const WORD& wIndex)
{
	auto iter_find = m_mapMulti.find(wstrStateKey);

	if (m_mapMulti.end() == iter_find)
		return nullptr;

	if (iter_find->second.size() <= wIndex)
		return nullptr;

	return iter_find->second[wIndex];
}

HRESULT MultiTexture::LoadTexture(
	LPDIRECT3DDEVICE9 pGraphicDev, 
	const wstring& wstrFilePath, 
	const wstring& wstrStateKey, 
	const WORD& wCnt)
{
	auto iter_find = m_mapMulti.find(wstrStateKey);

	if (m_mapMulti.end() != iter_find)
		return E_FAIL;

	D3DXIMAGE_INFO	tImgInfo; // 이미지 정보를 보관하기 위한 구조체 변수.
	ZeroMemory(&tImgInfo, sizeof(D3DXIMAGE_INFO));

	LPDIRECT3DTEXTURE9 pTexture = nullptr;
	HRESULT hr = 0;

	TCHAR szFullPath[MAX_STR] = L"";
	TEX_INFO* pTexInfo = nullptr;

	for (WORD i = 0; i < wCnt; ++i)
	{
		swprintf_s(szFullPath, wstrFilePath.c_str(), i);

		// 이미지 정보 얻어오는 함수.
		hr = D3DXGetImageInfoFromFile(szFullPath, &tImgInfo);
		FAILED_CHECK_MSG_RETURN(hr, L"D3DXGetImageInfoFromFile Failed", E_FAIL);

		// 텍스처 Com객체 생성 함수
		hr = D3DXCreateTextureFromFileEx(
			pGraphicDev, /* 장치 */
			szFullPath, /* 텍스처 경로 */
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

		pTexInfo = new TEX_INFO;
		pTexInfo->pTexture = pTexture;
		pTexInfo->tImgInfo = tImgInfo;

		m_mapMulti[wstrStateKey].push_back(pTexInfo);
	}
	return S_OK;
}

MultiTexture* MultiTexture::Create(
	LPDIRECT3DDEVICE9 pGraphicDev, 
	const wstring& wstrFilePath, 
	const wstring& wstrStateKey, 
	const WORD& wCnt)
{
	MultiTexture* pInstance = new MultiTexture;
	if (FAILED(pInstance->LoadTexture(pGraphicDev, wstrFilePath, wstrStateKey, wCnt)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void MultiTexture::Release()
{
	for (auto& MyPair : m_mapMulti)
	{
		for (auto& pTexInfo : MyPair.second)
		{
			pTexInfo->pTexture->Release();
			SafeDelete(pTexInfo);
		}

		MyPair.second.clear();
	}
	m_mapMulti.clear();
}
