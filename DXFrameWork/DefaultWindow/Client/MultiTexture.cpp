#include "stdafx.h"
#include "MultiTexture.h"


CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	Release();
}

const TEX_INFO* CMultiTexture::GetTexInfo(
	const wstring& wstrStateKey, 
	const WORD& wIndex) const
{
	auto iter_find = m_mapMulti.find(wstrStateKey);

	if (m_mapMulti.end() == iter_find)
		return nullptr;

	if (iter_find->second.size() <= wIndex)
		//return nullptr;
		return iter_find->second[iter_find->second.size()-1];			// ����� ���� �ε������� �̹��� �纸�� ũ�� ������ �̹��� ���

	return iter_find->second[wIndex];
}

HRESULT CMultiTexture::LoadTexture(
	LPDIRECT3DDEVICE9 pGraphicDev, 
	const wstring& wstrFilePath, /* ..\Texture\Stage\Player\Attack\AKIHA_AKI01_%d.png */
	const wstring& wstrStateKey, 
	const WORD& wCnt)
{
	auto iter_find = m_mapMulti.find(wstrStateKey);

	if (m_mapMulti.end() != iter_find)
		return E_FAIL;

	D3DXIMAGE_INFO	tImgInfo; // �̹��� ������ �����ϱ� ���� ����ü ����.
	ZeroMemory(&tImgInfo, sizeof(D3DXIMAGE_INFO));

	LPDIRECT3DTEXTURE9 pTexture = nullptr;
	HRESULT hr = 0;

	TCHAR szFullPath[MAX_STR] = L"";
	TEX_INFO* pTexInfo = nullptr;

	for (WORD i = 0; i < wCnt; ++i)
	{
		swprintf_s(szFullPath, wstrFilePath.c_str(), i);

		// �̹��� ���� ������ �Լ�.
		hr = D3DXGetImageInfoFromFile(szFullPath, &tImgInfo);
		FAILED_CHECK_MSG_RETURN(hr, L"D3DXGetImageInfoFromFile Failed", E_FAIL);

		// �ؽ�ó Com��ü ���� �Լ�
		hr = D3DXCreateTextureFromFileEx(
			pGraphicDev, /* ��ġ */
			szFullPath, /* �ؽ�ó ��� */
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

		pTexInfo = new TEX_INFO;
		pTexInfo->pTexture = pTexture;
		pTexInfo->tImgInfo = tImgInfo;
		pTexInfo->iImageMax = wCnt;

		m_mapMulti[wstrStateKey].push_back(pTexInfo);
	}

	return S_OK;
}

void CMultiTexture::Release()
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


	///////////////////////////////////////////////////////////////

	/*for_each(m_mapMulti.begin(), m_mapMulti.end(), 
		[](auto& MyPair)
	{
		for_each(MyPair.second.begin(), MyPair.end(),
			[](auto& pTexInfo)
		{
			pTexInfo->pTexture->Release();
			SafeDelete(pTexInfo);
		});

		MyPair.second.clear();
	});

	m_mapMulti.clear();*/
}

CMultiTexture* CMultiTexture::Create(
	LPDIRECT3DDEVICE9 pGraphicDev, 
	const wstring& wstrFilePath, 
	const wstring& wstrStateKey, 
	const WORD& wCnt)
{
	CMultiTexture* pInstance = new CMultiTexture;

	if (FAILED(pInstance->LoadTexture(pGraphicDev, wstrFilePath, wstrStateKey, wCnt)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
