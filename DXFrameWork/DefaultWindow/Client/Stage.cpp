#include "stdafx.h"
#include "Stage.h"
#include "Terrain.h"
#include "Player.h"
#include "Card.h"
#include "AttackCard.h"

CStage::CStage()
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
	

	HRESULT hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../Resource/Player/Idle/Player_Idle_%02d.png",
		L"Player",
		L"Idle",
		53);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../Resource/Player/Hit/Player_Hit_%d.png",
		L"Player",
		L"Hit",
		9);

	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../Resource/Player/Dead/Player_Dead_%d.png",
		L"Player",
		L"Dead",
		1);
	

	m_pObjectMgr->AddObject(OBJECT_PLAYER, CPlayer::Create());
	// 테스트용
	m_pObjectMgr->AddObject(OBJECT_CARD, CAttackCard::Create());
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