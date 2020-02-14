#include "stdafx.h"
#include "Stage.h"
#include "Terrain.h"
#include "Player.h"

CStage::CStage()
	: m_pObjectMgr(CObjectMgr::GetInstance())
{
}


CStage::~CStage()
{
	Release();
}

int CStage::Update()
{
	m_pObjectMgr->Update();

	return NO_EVENT;
}

void CStage::LateUpdate()
{
	m_pObjectMgr->LateUpdate();
}

void CStage::Render()
{
	m_pObjectMgr->Render();
}

HRESULT CStage::Initialize()
{
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);

	// Cube Texture
	HRESULT hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_SINGLE,
		L"../Texture/Cube.png",
		L"Cube");
	FAILED_CHECK_MSG_RETURN(hr, L"Cube LoadTexture Failed", E_FAIL);

	//// Player Attack Texture
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../Texture/Stage/Player/Attack/AKIHA_AKI01_%d.png",
		L"Player",
		L"Attack",
		6);
	FAILED_CHECK_MSG_RETURN(hr, L"Player Attack LoadTexture Failed", E_FAIL);

	// Player Dash Texture
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../Texture/Stage/Player/Dash/AKIHA_AKI13_00%d.png",
		L"Player",
		L"Dash",
		11);
	FAILED_CHECK_MSG_RETURN(hr, L"Player Dash LoadTexture Failed", E_FAIL);

	// Terrain Tile Texture
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../Texture/Stage/Terrain/Tile/Tile%d.png",
		L"Terrain",
		L"Tile",
		38);
	FAILED_CHECK_MSG_RETURN(hr, L"Terrain Tile LoadTexture Failed", E_FAIL);

	// Terrain Object
	hr = m_pObjectMgr->AddObject(OBJECT_TERRAIN, CTerrain::Create());
	FAILED_CHECK_MSG_RETURN(hr, L"Terrain Create Failed", E_FAIL);

	// Player Object
	hr = m_pObjectMgr->AddObject(OBJECT_PLAYER, CPlayer::Create());
	FAILED_CHECK_MSG_RETURN(hr, L"Player Create Failed", E_FAIL);

	return S_OK;
}

void CStage::Release()
{
}

CStage* CStage::Create()
{
	CStage* pInstance = new CStage;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}