#include "pch.h"
#include "Player.h"
#include "MainGame.h"
#include "SingleTexture.h"

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

	// ��� ������ �� ���̿��� ���� ȣ��
	const TEX_INFO* pTexInfo = m_pSingleTex->GetTexInfo();
	NULL_CHECK(pTexInfo);
	
	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;
	
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture,
		NULL, 
		&D3DXVECTOR3(0, 0, 1),
		&D3DXVECTOR3(0, 0, 1), 
		D3DCOLOR_XRGB(255, 255, 255));
	

	m_pDeviceMgr->Render_End();
}

HRESULT MainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	m_pPlayer = Player::Create();
	NULL_CHECK_MSG_RETURN(m_pPlayer, L"Player Create Failed", E_FAIL);

	HRESULT hr = DeviceMgr::GetInstance()->InitDevice(MODE_WIN);
	FAILED_CHECK_MSG_RETURN(hr, L"����̽� �ʱ�ȭ ����", E_FAIL);

	m_pSingleTex = SingleTexture::Create(
		m_pDeviceMgr->GetDevice(), L"../Texture/Cube.png");
	NULL_CHECK_MSG_RETURN(m_pSingleTex, L"Cube LoadTexture Failed", E_FAIL);

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
