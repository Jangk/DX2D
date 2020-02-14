#include "stdafx.h"
#include "Stage.h"
#include "Terrain.h"
#include "Player.h"
#include "Block.h"

CStage::CStage()
	: m_pObjectMgr(CObjectMgr::GetInstance())
{

	//case 1:
	//	FileIOMgr::GetInstance()->LoadStage(L"../Data/Stage1.dat", m_vecMap);
	//	m_vStartPos = { 250, 450, 0 };
	//	break;
	//case 2:
	//	FileIOMgr::GetInstance()->LoadStage(L"../Data/Stage2.dat", m_vecMap);
	//	m_vStartPos = { 0, 0, 0 };
	//	break;
	//case 3:
	//	FileIOMgr::GetInstance()->LoadStage(L"../Data/Stage3.dat", m_vecMap);
	//	m_vStartPos = { 0, 0, 0 };
	//	break;
}


CStage::~CStage()
{
	Release();
}

int CStage::Update()
{
	m_Player = m_pObjectMgr->GetPlayer();
	if (nullptr != m_Player && m_Player->GetIsDead())
	{
		m_Player->SetPos(m_vStartPos.x, m_vStartPos.y, m_vStartPos.z);
		m_Player->SetRespawn(m_vStartPos);
	}
	m_pObjectMgr->Update();
	if (WINCX <= m_Player->GetTotalInfo().vPos.x)
		CSceneMgr::GetInstance()->SceneChange(SCENE_STAGE1, SCENE_STAGE2);

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
	m_Player = m_pObjectMgr->GetPlayer();
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);


	 Block Object;
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_MULTI,
		L"../Texture/Block/Block%d.png",
		L"Terrain",
		L"Block",
		5);
	
	FAILED_CHECK_MSG_RETURN(hr, L"Block LoadTexture Failed", E_FAIL);

	FileIOMgr::GetInstance()->LoadStage(L"../Data/Stage1.dat", m_vecMap);
	m_vStartPos = { 250, 450, 0 };


	// Player
	hr = m_pTextureMgr->LoadTexture(
		pGraphicDev,
		TEXTURE_SINGLE,
		L"../Texture/Block/ball.png",
		L"Ball");
	FAILED_CHECK_MSG_RETURN(hr, L"Ball LoadTexture Failed", E_FAIL);

	CPlayer* temp2;
	temp2 = CPlayer::Create();
	temp2->SetPos(m_vStartPos.x, m_vStartPos.y , m_vStartPos.z);
	hr = m_pObjectMgr->AddObject(OBJECT_PLAYER, temp2);
	FAILED_CHECK_MSG_RETURN(hr, L"Ball Create Failed", E_FAIL);
	return S_OK;
}

void CStage::Release()
{
	m_pObjectMgr->DeleteGroup(OBJECT_TERRAIN);
	m_pObjectMgr->DeleteGroup(OBJECT_PLAYER);
}

CStage* CStage::Create()
{
	CStage* pInstance = new CStage();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}