#include "pch.h"
#include "TextureMgr.h"
#include "SingleTexture.h"
#include "MultiTexture.h"

IMPLEMENT_SINGLETON(TextureMgr)

TextureMgr::TextureMgr() : m_pDeviceMgr(DeviceMgr::GetInstance())
{
}

TextureMgr::~TextureMgr()
{
}

const TEX_INFO* TextureMgr::GetTexInfo(
	const wstring& wstrObjectKey, 
	const wstring& wstrStateKey, 
	const WORD& wIndex) const
{
	auto iter_find = m_mapTexture.find(wstrObjectKey);

	if (m_mapTexture.end() == iter_find)
		return nullptr;

	return iter_find->second->GetTexInfo(wstrStateKey, wIndex);
}

HRESULT TextureMgr::LoadTexture(
	LPDIRECT3DDEVICE9 pGrahicDev, 
	TEXTURE_TYPE eTextureType, 
	const wstring& wstrFilePath, 
	const wstring& wstrObjectKey, 
	const wstring& wstrStateKey, 
	const WORD& wCnt)
{
	Texture* pTexture = nullptr;

	auto iter_find = m_mapTexture.find(wstrObjectKey);

	if (m_mapTexture.end() == iter_find)
	{
		switch (eTextureType)
		{
		case TEXTURE_SINGLE:
			pTexture = SingleTexture::Create(pGrahicDev, wstrFilePath);
			break;
		case TEXTURE_MULTI:
			pTexture = MultiTexture::Create(pGrahicDev, wstrFilePath, wstrStateKey, wCnt);
			break;
		}

		NULL_CHECK_RETURN(pTexture, E_FAIL);
		m_mapTexture.insert(make_pair(wstrObjectKey, pTexture));
	}
	else
	{
		HRESULT hr = 0;

		switch (eTextureType)
		{
		case TEXTURE_SINGLE:
			return E_FAIL;
		case TEXTURE_MULTI:
			hr = m_mapTexture[wstrObjectKey]->LoadTexture(pGrahicDev, wstrFilePath, wstrStateKey, wCnt);
			FAILED_CHECK_RETURN(hr, E_FAIL);
			break;
		}
	}
	return S_OK;
}

HRESULT TextureMgr::Initialize()
{
	// 이미지 로드때만 쓰임
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);


	// Terrain Tile Texture
	HRESULT hr = LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../Texture/Stage/Terrain/Tile/Tile%d.png",
		L"Terrain",
		L"Tile",
		38);
	FAILED_CHECK_MSG_RETURN(hr, L"Terrain Tile LoadTexture Failed", E_FAIL);
}

void TextureMgr::Release()
{
	for (auto& MyPair : m_mapTexture)
		SafeDelete(MyPair.second);
	m_mapTexture.clear();
}
