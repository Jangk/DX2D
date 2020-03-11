#include "stdafx.h"
#include "MainGame.h"
#include "Card.h"
#include "AttackCard.h"



/* 해야할것
 2. 전투씬에서 카드가 Selected상태일때 올바른 대상을 클릭하면 작동하게 할것.

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

	InitializeCardDeck();

	hr = m_pSceneMgr->SceneChange(SCENE_END, SCENE_LOGO);
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

void CMainGame::InitializeCardDeck()
{	// 겜시작시 가지는 디폴트 카드덱
	CCard* temp;
	// 일단 공격카드 10장 넣음.
	for (int i = 0; i < DRAW_CARD_MAX; ++i)
	{
		temp = CAttackCard::Create();
		dynamic_cast<CAttackCard*>(temp)->SetCard(ATTACK_CARD_TYPE(i % ATTACK_CARD_END));
		m_pObjectMgr->AddObject(OBJECT_CARD, temp);
	}
}

HRESULT CMainGame::LoadImageResource()
{
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);
	HRESULT hr;

	// 월드맵
	{
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/WorldMap/mapTop.png",
			L"WorldMap",
			L"Top",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"월드맵 top 로드 실패", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/WorldMap/mapMid.png",
			L"WorldMap",
			L"Mid",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"월드맵 Mid 로드 실패", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/WorldMap/mapBot.png",
			L"WorldMap",
			L"Bot",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"월드맵 Bot 로드 실패", E_FAIL);


		// 상자 노드
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/WorldMap/chest.png",
			L"WorldMap",
			L"chest",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"chest", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/WorldMap/chestOutline.png",
			L"WorldMap",
			L"chestOutline",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"chestOutline", E_FAIL);

		// 엘리트 노드
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/WorldMap/elite.png",
			L"WorldMap",
			L"elite",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"elite", E_FAIL);
		
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/WorldMap/eliteOutline.png",
			L"WorldMap",
			L"eliteOutline",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"eliteOutline", E_FAIL);

		// 이벤트 노드
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/WorldMap/event.png",
			L"WorldMap",
			L"event",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"event", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/WorldMap/eventOutline.png",
			L"WorldMap",
			L"eventOutline",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"eventOutline", E_FAIL);

		// 몬스터 노드
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/WorldMap/monster.png",
			L"WorldMap",
			L"monster",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"monster", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/WorldMap/monsterOutline.png",
			L"WorldMap",
			L"monsterOutline",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"monsterOutline", E_FAIL);

		// 레스트(캠프파이어) 노드
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/WorldMap/rest.png",
			L"WorldMap",
			L"rest",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"rest", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/WorldMap/restOutline.png",
			L"WorldMap",
			L"restOutline",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"restOutline", E_FAIL);
	}


	// 카드 이미지 
	{
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Card/Silent/Attack/Attack_%02d.png",
			L"Card",
			L"Attack",
			10);
		FAILED_CHECK_MSG_RETURN(hr, L"Attack", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Card/Silent/Skill/Skill_%02d.png",
			L"Card",
			L"Skill",
			10);
		FAILED_CHECK_MSG_RETURN(hr, L"Skill", E_FAIL);


		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Card/Silent/Power/Power_%02d.png",
			L"Card",
			L"Power",
			3);
		FAILED_CHECK_MSG_RETURN(hr, L"Power", E_FAIL);


		// 카드 테두리
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Card/CardUI/AttackOutline_%d.png",
			L"Card",
			L"AttackOutline",
			3);
		FAILED_CHECK_MSG_RETURN(hr, L"AttackOutline_", E_FAIL);


		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Card/CardUI/SkillOutline_%d.png",
			L"Card",
			L"SkillOutline",
			3);
		FAILED_CHECK_MSG_RETURN(hr, L"SkillOutline_", E_FAIL);


		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Card/CardUI/PowerOutline_%d.png",
			L"Card",
			L"PowerOutline",
			3);
		FAILED_CHECK_MSG_RETURN(hr, L"PowerOutline_", E_FAIL);


		// 카드 이름
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Card/CardUI/CardName_%d.png",
			L"Card",
			L"CardName",
			3);
		FAILED_CHECK_MSG_RETURN(hr, L"CardName_", E_FAIL);


		// 카드 배경
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_SINGLE,
			L"../Resource/Card/CardUI/AttackBackground.png",
			L"AttackBackground");
		FAILED_CHECK_MSG_RETURN(hr, L"AttackBackground", E_FAIL);


		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_SINGLE,
			L"../Resource/Card/CardUI/SkillBackground.png",
			L"SkillBackground");
		FAILED_CHECK_MSG_RETURN(hr, L"SkillBackground", E_FAIL);


		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_SINGLE,
			L"../Resource/Card/CardUI/PowerBackground.png",
			L"PowerBackground");
		FAILED_CHECK_MSG_RETURN(hr, L"PowerBackground", E_FAIL);
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
		FAILED_CHECK_MSG_RETURN(hr, L"Player_Idle_", E_FAIL);


		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Player/Hit/Player_Hit_%d.png",
			L"Player",
			L"Hit",
			9);
		FAILED_CHECK_MSG_RETURN(hr, L"Player_Hit_", E_FAIL);


		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Player/Dead/Player_Dead_%d.png",
			L"Player",
			L"Dead",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"Player_Dead_", E_FAIL);
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
		FAILED_CHECK_MSG_RETURN(hr, L"Cultist_Idle_", E_FAIL);


		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Monster/Cultist/Attack/Cultist_Attack_%02d.png",
			L"Cultist",
			L"Attack",
			20);
		FAILED_CHECK_MSG_RETURN(hr, L"Cultist_Attack_", E_FAIL);
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
		FAILED_CHECK_MSG_RETURN(hr, L"Background", E_FAIL);
	}
	
	// UI
	{
		// top panel
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/TopPanel/Bar.png",
			L"UI",
			L"Bar",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"Bar", E_FAIL);


		// 생명 아이콘
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/TopPanel/panelHeart.png",
			L"UI",
			L"panelHeart",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"panelHeart", E_FAIL);


		// 돈 아이콘
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/TopPanel/panelGoldBag.png",
			L"UI",
			L"panelGoldBag",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"panelGoldBag", E_FAIL);


		// 현재 체력바
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/InGame/CurHP.png",
			L"UI",
			L"CurHP",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"CurHP", E_FAIL);


		// 최대 체력바
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/InGame/MaxHP.png",
			L"UI",
			L"MaxHP",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"MaxHP", E_FAIL);

		
		// 쉴드 체력바
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/InGame/SheildHP.png",
			L"UI",
			L"SheildHP",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"SheildHP", E_FAIL);


		// 에너지 아이콘
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/InGame/Cost.png",
			L"UI",
			L"Cost",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"Cost", E_FAIL);


		// 덱 아이콘
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/InGame/Deck.png",
			L"UI",
			L"Deck",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"Deck", E_FAIL);


		// 무덤 아이콘
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/InGame/Tomb.png",
			L"UI",
			L"Tomb",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"Tomb", E_FAIL);

		// endTurnButton
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/Button/endTurnButton.png",
			L"UI",
			L"endTurnButton",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"endTurnButton", E_FAIL);

		// endTurnButtonGlow
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/Button/endTurnButtonGlow.png",
			L"UI",
			L"endTurnButtonGlow",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"endTurnButtonGlow", E_FAIL);
	}
	return S_OK;
}