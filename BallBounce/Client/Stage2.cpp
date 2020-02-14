#include "stdafx.h"
#include "Stage2.h"
#include "Terrain.h"
#include "Player.h"
#include "Block.h"

CStage2::CStage2()
	: m_pObjectMgr(CObjectMgr::GetInstance())
{
}


CStage2::~CStage2()
{
	Release();
}

int CStage2::Update()
{
	m_Player = m_pObjectMgr->GetPlayer();
	if (nullptr != m_Player && m_Player->GetIsDead())
	{
		m_Player->SetPos(m_vStartPos.x, m_vStartPos.y, m_vStartPos.z);
		m_Player->SetRespawn(m_vStartPos);
	}
	m_pObjectMgr->Update();
	if (WINCX <= m_Player->GetTotalInfo().vPos.x)
		CSceneMgr::GetInstance()->SceneChange(SCENE_STAGE2, SCENE_STAGE3);

	return NO_EVENT;
}

void CStage2::LateUpdate()
{
	m_pObjectMgr->LateUpdate();
}

void CStage2::Render()
{
	m_pObjectMgr->Render();
}

HRESULT CStage2::Initialize()
{
	m_Player = m_pObjectMgr->GetPlayer();
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);

	FileIOMgr::GetInstance()->LoadStage(L"../Data/Stage2.dat", m_vecMap);
	m_vStartPos = { 100, 100, 0 };

	CPlayer* temp2;
	temp2 = CPlayer::Create();
	temp2->SetPos(m_vStartPos.x, m_vStartPos.y, m_vStartPos.z);
	hr = m_pObjectMgr->AddObject(OBJECT_PLAYER, temp2);
	FAILED_CHECK_MSG_RETURN(hr, L"Ball Create Failed", E_FAIL);
	return S_OK;
	return S_OK;
}

void CStage2::Release()
{
	m_pObjectMgr->DeleteGroup(OBJECT_TERRAIN);
	m_pObjectMgr->DeleteGroup(OBJECT_PLAYER);
}

CStage2* CStage2::Create()
{
	CStage2* pInstance = new CStage2();

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}