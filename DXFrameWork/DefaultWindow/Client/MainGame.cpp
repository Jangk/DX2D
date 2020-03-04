#include "stdafx.h"
#include "MainGame.h"



/* 해야할것
1. 월드맵이랑 스테이지 씬을 합칠것
 - 월드맵에서는 화면 스크롤이 적용되지만 전투씬이나 이벤트 씬에서는 스크롤이 적용되지않게

 2. 전투씬에서 카드가 Selected상태일때 올바른 대상을 클릭하면 작동하게 할것.

 3. 위에 UI 띄울것.
*/

CMainGame::CMainGame()
	: m_pKeyMgr(CKeyMgr::GetInstance()),
	m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance()),
	m_pObjectMgr(CObjectMgr::GetInstance()),
	m_pTimeMgr(CTimeMgr::GetInstance()),
	m_pSceneMgr(CSceneMgr::GetInstance()),
	m_pFrameMgr(CFrameMgr::GetInstance()),
	m_iEvent(NO_EVENT)
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Update()
{
	m_pTimeMgr->Update();
	m_pKeyMgr->Update();	
	m_iEvent = m_pSceneMgr->Update();
}

void CMainGame::LateUpdate()
{
	if (CHANGE_SCENE == m_iEvent)
		return;

	m_pSceneMgr->LateUpdate();
}

void CMainGame::Render()
{
	if (CHANGE_SCENE == m_iEvent)
		return;

	m_pDeviceMgr->Render_Begin();

	// 앞으로 모든 오브젝트들을 이 사이에서 렌더 호출!		
	m_pSceneMgr->Render();
	m_pFrameMgr->RenderFPS();

	m_pDeviceMgr->Render_End();
}

HRESULT CMainGame::Initialize()
{	
	HRESULT hr = m_pDeviceMgr->InitDevice(MODE_WIN);
	FAILED_CHECK_MSG_RETURN(hr, L"InitDevice Failed", E_FAIL);	

	// 게임시작시 카드 전부 로드. 디바이스가 초기화 된후 수행해야됨.
	if (LoadImageResource() == E_FAIL)
		return E_FAIL;

	hr = m_pSceneMgr->SceneChange(SCENE_END, SCENE_STAGE);
	FAILED_CHECK_MSG_RETURN(hr, L"Logo Change Failed", E_FAIL);

	return S_OK;
}


void CMainGame::Release()
{
	m_pFrameMgr->DestroyInstance();
	m_pSceneMgr->DestroyInstance();
	m_pTimeMgr->DestroyInstance();
	m_pObjectMgr->DestroyInstance();
	m_pKeyMgr->DestroyInstance();
	m_pTextureMgr->DestroyInstance();
	m_pDeviceMgr->DestroyInstance();
}


CMainGame* CMainGame::Create()
{
	CMainGame* pInstance = new CMainGame;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}


HRESULT CMainGame::LoadImageResource()
{
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);
	HRESULT hr;

	// 카드 이미지 
	{
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Card/Silent/Attack/Attack_%02d.png",
			L"Card",
			L"Attack",
			10);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Card/Silent/Skill/Skill_%02d.png",
			L"Card",
			L"Skill",
			13);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Card/Silent/Power/Power_%02d.png",
			L"Card",
			L"Power",
			3);


		// 카드 테두리
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Card/CardUI/AttackOutline_%d.png",
			L"Card",
			L"AttackOutline",
			3);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Card/CardUI/SkillOutline_%d.png",
			L"Card",
			L"SkillOutline",
			3);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Card/CardUI/PowerOutline_%d.png",
			L"Card",
			L"PowerOutline",
			3);


		// 카드 이름
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Card/CardUI/CardName_%d.png",
			L"Card",
			L"CardName",
			3);

		// 카드 배경
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_SINGLE,
			L"../Resource/Card/CardUI/AttackBackground.png",
			L"AttackBackground");

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_SINGLE,
			L"../Resource/Card/CardUI/SkillBackground.png",
			L"SkillBackground");

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_SINGLE,
			L"../Resource/Card/CardUI/PowerBackground.png",
			L"PowerBackground");
	}


	// ------------------------------------ 플레이어
	{
		hr = m_pTextureMgr->LoadTexture(
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
	}


	// 몬스터 Cultist
	{
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Monster/Cultist/Idle/Cultist_Idle_%02d.png",
			L"Cultist",
			L"Idle",
			40);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Monster/Cultist/Attack/Cultist_Attack_%02d.png",
			L"Cultist",
			L"Attack",
			20);
	}

	// 스테이지 백그라운드
	{
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Stage/Background.png",
			L"Stage",
			L"Background",
			1);
	}
}