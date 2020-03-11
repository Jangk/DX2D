#include "stdafx.h"
#include "MainGame.h"
#include "Card.h"
#include "AttackCard.h"



/* �ؾ��Ұ�
 2. ���������� ī�尡 Selected�����϶� �ùٸ� ����� Ŭ���ϸ� �۵��ϰ� �Ұ�.

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

	// ������ ��� ������Ʈ���� �� ���̿��� ���� ȣ��!		
	m_pSceneMgr->Render();
	m_pFrameMgr->RenderFPS();

	m_pDeviceMgr->Render_End();
}

HRESULT CMainGame::Initialize()
{	
	HRESULT hr = m_pDeviceMgr->InitDevice(MODE_WIN);
	FAILED_CHECK_MSG_RETURN(hr, L"InitDevice Failed", E_FAIL);	

	// ���ӽ��۽� ī�� ���� �ε�. ����̽��� �ʱ�ȭ ���� �����ؾߵ�.
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
{	// �׽��۽� ������ ����Ʈ ī�嵦
	CCard* temp;
	// �ϴ� ����ī�� 10�� ����.
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

	// �����
	{
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/WorldMap/mapTop.png",
			L"WorldMap",
			L"Top",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"����� top �ε� ����", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/WorldMap/mapMid.png",
			L"WorldMap",
			L"Mid",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"����� Mid �ε� ����", E_FAIL);

		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/WorldMap/mapBot.png",
			L"WorldMap",
			L"Bot",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"����� Bot �ε� ����", E_FAIL);


		// ���� ���
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

		// ����Ʈ ���
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

		// �̺�Ʈ ���
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

		// ���� ���
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

		// ����Ʈ(ķ�����̾�) ���
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


	// ī�� �̹��� 
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


		// ī�� �׵θ�
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


		// ī�� �̸�
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/Card/CardUI/CardName_%d.png",
			L"Card",
			L"CardName",
			3);
		FAILED_CHECK_MSG_RETURN(hr, L"CardName_", E_FAIL);


		// ī�� ���
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


	// ------------------------------------ �÷��̾�
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


	// ���� Cultist
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

	// �������� ��׶���
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


		// ���� ������
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/TopPanel/panelHeart.png",
			L"UI",
			L"panelHeart",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"panelHeart", E_FAIL);


		// �� ������
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/TopPanel/panelGoldBag.png",
			L"UI",
			L"panelGoldBag",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"panelGoldBag", E_FAIL);


		// ���� ü�¹�
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/InGame/CurHP.png",
			L"UI",
			L"CurHP",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"CurHP", E_FAIL);


		// �ִ� ü�¹�
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/InGame/MaxHP.png",
			L"UI",
			L"MaxHP",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"MaxHP", E_FAIL);

		
		// ���� ü�¹�
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/InGame/SheildHP.png",
			L"UI",
			L"SheildHP",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"SheildHP", E_FAIL);


		// ������ ������
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/InGame/Cost.png",
			L"UI",
			L"Cost",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"Cost", E_FAIL);


		// �� ������
		hr = m_pTextureMgr->LoadTexture(
			pGraphicDev,
			TEXTURE_MULTI,
			L"../Resource/UI/InGame/Deck.png",
			L"UI",
			L"Deck",
			1);
		FAILED_CHECK_MSG_RETURN(hr, L"Deck", E_FAIL);


		// ���� ������
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