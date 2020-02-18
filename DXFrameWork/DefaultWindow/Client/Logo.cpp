#include "stdafx.h"
#include "Logo.h"


CLogo::CLogo()
	: m_pKeyMgr(CKeyMgr::GetInstance())
{
}


CLogo::~CLogo()
{
	Release();
}

int CLogo::Update()
{
	if (m_pKeyMgr->KeyDown(KEY_RETURN))
	{
		m_pSceneMgr->SceneChange(SCENE_LOGO, SCENE_CHARECTER_SELECTE);
		return CHANGE_SCENE;
	}

	return NO_EVENT;
}

void CLogo::LateUpdate()
{
}

void CLogo::Render()
{
	D3DXMATRIX scale, translation, matWorld;
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"LogoBackGround");
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&scale, 1, 1, 1);
	D3DXMatrixTranslation(&translation, WINCX* 0.5f, WINCY*0.5, 0);
	matWorld = scale * translation;
	m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CLogo::Initialize()
{
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);

	// Cube Texture
	HRESULT hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_SINGLE,
		L"../Resource/Logo/BackGround.png",
		L"LogoBackGround");
	FAILED_CHECK_MSG_RETURN(hr, L"BackGround1 LoadTexture Failed", E_FAIL);
	return S_OK;
}

void CLogo::Release()
{
}

CLogo* CLogo::Create()
{
	CLogo* pInstance = new CLogo;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
