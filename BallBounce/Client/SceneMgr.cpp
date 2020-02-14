#include "stdafx.h"
#include "SceneMgr.h"
#include "Logo.h"
#include "Stage.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Editor.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr)
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
		case SCENE_STAGE1:
			m_pScene = CStage::Create();
			break;
		case SCENE_STAGE2:
			m_pScene = CStage2::Create();
			break;
		case SCENE_STAGE3:
			m_pScene = CStage3::Create();
			break;
		case SCENE_EDITOR:
			m_pScene = Editor::Create();
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
