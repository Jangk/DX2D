#include "stdafx.h"
#include "Logo.h"
#include "Player.h"


CLogo::CLogo()
	: m_pKeyMgr(CKeyMgr::GetInstance()),
	m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pObjectMgr(CObjectMgr::GetInstance())
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
		m_pSceneMgr->SceneChange(SCENE_LOGO, SCENE_STAGE1);
		return CHANGE_SCENE;
	}
	if (m_pKeyMgr->KeyDown(KEY_SPACE))
	{
		m_pSceneMgr->SceneChange(SCENE_LOGO, SCENE_EDITOR);
		return CHANGE_SCENE;
	}

	return NO_EVENT;
}

void CLogo::LateUpdate()
{
}

void CLogo::Render()
{
	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Logo", L"", 0);
	NULL_CHECK(pTexInfo);
	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;


	D3DXMatrixScaling(&matScale, 1, 1, 1);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		m_tInfo.vPos.z);
	m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matTrans));
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CLogo::Initialize()
{
	D3DXMatrixIdentity(&m_tInfo.matWorld); // 다이렉트 항등행렬 함수
	m_tInfo.vPos = { WINCX/2, WINCY/2, 0.f }; // x, y, z
	m_tInfo.vDir = { 0.f, 0.f, 0.f };
	m_tInfo.vLook = { 0.f, -1.f, 0.f };
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);
	
	HRESULT hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_SINGLE,
		L"../Texture/Block/Logo.png",
		L"Logo");
	FAILED_CHECK_MSG_RETURN(hr, L"Logo LoadTexture Failed", E_FAIL);


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
