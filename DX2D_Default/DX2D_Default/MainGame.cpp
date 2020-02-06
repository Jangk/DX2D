#include "pch.h"
#include "Player.h"
#include "MainGame.h"

MainGame::MainGame() : m_pPlayer(nullptr), m_pKeyMgr(CKeyMgr::GetInstance()), m_pDeviceMgr(DeviceMgr::GetInstance())
{
}

MainGame::~MainGame()
{
	Release();
}

void MainGame::Update()
{
	m_pPlayer->Update();
	m_pKeyMgr->Update();
}

void MainGame::LateUpdate()
{
	m_pPlayer->LateUpdate();
}

void MainGame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	m_pDeviceMgr->Render_Begin();
	m_pDeviceMgr->Render_End();
}

HRESULT MainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	m_pPlayer = Player::Create();
	NULL_CHECK_MSG_RETURN(m_pPlayer, L"Player Create Failed", E_FAIL);

	DeviceMgr::GetInstance()->InitDevice(MODE_FULL);

	return S_OK;
}

void MainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);
	SafeDelete(m_pPlayer);
}

MainGame* MainGame::Create()
{
	MainGame* pInstance = new MainGame;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
