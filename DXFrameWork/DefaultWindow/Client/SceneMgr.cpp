#include "stdafx.h"
#include "SceneMgr.h"
#include "Logo.h"
#include "Stage.h"
#include "CharSelect.h"
#include "WorldMap.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr),
	m_pDeviceMgr(CDeviceMgr::GetInstance()),
	m_pTextureMgr(CTextureMgr::GetInstance())
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

HRESULT CSceneMgr::SceneChange(SCENE_TYPE eCurType, SCENE_TYPE eNextType)
{
	if (eCurType != eNextType)
	{
		SafeDelete(m_pScene);

		switch (eNextType)
		{
		case SCENE_LOGO:
			m_pScene = CLogo::Create();
			break;
		case SCENE_CHARECTER_SELECTE:
			m_pScene = CCharSelect::Create();
			break;
		case SCENE_WORLD_MAP:
			m_pScene = CWorldMap::Create();
			break;
		case SCENE_STAGE:
			m_pScene = CStage::Create();
			break;
		default:
			break;
		}

		NULL_CHECK_RETURN(m_pScene, E_FAIL);
	}

	return S_OK;
}

HRESULT CSceneMgr::InitCard()
{
	LPDIRECT3DDEVICE9 pGraphicDev = m_pDeviceMgr->GetDevice();
	NULL_CHECK_MSG_RETURN(pGraphicDev, L"pGraphicDev is null", E_FAIL);


	// 카드 이미지 
	HRESULT hr = m_pTextureMgr->LoadTexture(
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

int CSceneMgr::Update()
{
	int iEvent = m_pScene->Update();

	return iEvent;
}

void CSceneMgr::LateUpdate()
{
	m_pScene->LateUpdate();
}

void CSceneMgr::Render()
{
	m_pScene->Render();
}

void CSceneMgr::Release()
{
	SafeDelete(m_pScene);
}
