#include "stdafx.h"
#include "MainGame.h"


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
