#include "stdafx.h"
#include "SceneMgr.h"
#include "Logo.h"
#include "Stage.h"
#include "CharSelect.h"
#include "WorldMap.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr),
	m_bIsFirst(true)
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
		if (m_bIsFirst)
		{
			m_pWorldMap = CWorldMap::Create();
			m_bIsFirst  = false;
		}

		if(m_pScene != m_pWorldMap)
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
			m_pScene = m_pWorldMap;					// 월드맵은 지우지않고 계속 재활용할것.
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
