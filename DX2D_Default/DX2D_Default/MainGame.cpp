#include "pch.h"
#include "Player.h"
#include "MainGame.h"
#include "SingleTexture.h"
#include "MultiTexture.h"


#include "Tile.h"

MainGame::MainGame() : m_pKeyMgr(CKeyMgr::GetInstance()), m_pDeviceMgr(DeviceMgr::GetInstance())
						, m_pTextureMgr(TextureMgr::GetInstance())
{

}

MainGame::~MainGame()
{
	Release();
}

void MainGame::ColMouse()
{
	POINT pt;
	INFO  objInfo;
	D3DXVECTOR3 linePoint[4];
	float x1;
	float y1;
	float x2;
	float y2;
	float posY[4];
	
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	
	for (auto iter : m_VecTile)
	{
		objInfo = iter->GetInfo();
		linePoint[0] = D3DXVECTOR3(objInfo.vPos.x - objInfo.fCX * 0.5f, objInfo.vPos.y, 1);
		linePoint[1] = D3DXVECTOR3(objInfo.vPos.x, objInfo.vPos.y - objInfo.fCY * 0.5f, 1);
		linePoint[2] = D3DXVECTOR3(objInfo.vPos.x + objInfo.fCX * 0.5f, objInfo.vPos.y, 1);
		linePoint[3] = D3DXVECTOR3(objInfo.vPos.x, objInfo.vPos.y + objInfo.fCY * 0.5f, 1);

		if (objInfo.vPos.x - objInfo.fCX * 0.5f <= pt.x &&
			pt.x <= objInfo.vPos.x)
		{
			x1 = linePoint[0].x;
			y1 = linePoint[0].y;
			x2 = linePoint[1].x;
			y2 = linePoint[1].y;
			posY[0] = (y2 - y1) / (x2 - x1) * (pt.x - x1) + y1;

			x1 = linePoint[3].x;
			y1 = linePoint[3].y;
			x2 = linePoint[0].x;
			y2 = linePoint[0].y;
			posY[1] = (y2 - y1) / (x2 - x1) * (pt.x - x1) + y1;
			if (posY[0] <= pt.y && posY[1] >= pt.y)
				iter->ChangeImage(3);
		}

		if (objInfo.vPos.x <= pt.x &&
			pt.x <= objInfo.vPos.x + objInfo.fCX * 0.5f)
		{
			x1 = linePoint[1].x;
			y1 = linePoint[1].y;
			x2 = linePoint[2].x;
			y2 = linePoint[2].y;
			posY[2] = (y2 - y1) / (x2 - x1) * (pt.x - x1) + y1;

			x1 = linePoint[2].x;
			y1 = linePoint[2].y;
			x2 = linePoint[3].x;
			y2 = linePoint[3].y;
			posY[3] = (y2 - y1) / (x2 - x1) * (pt.x - x1) + y1;
			if (posY[2] <= pt.y && posY[3] >= pt.y)
				iter->ChangeImage(3);
		}
	}
}

void MainGame::Update()
{
	m_pKeyMgr->Update();
	for (auto iter : m_VecTile)
		iter->ChangeImage(2);
	ColMouse();
	
}

void MainGame::LateUpdate()
{
}

void MainGame::Render()
{
	m_pDeviceMgr->Render_Begin();

	// 모든 렌더는 이 사이에서 렌더 호출
	for (auto iter : m_VecTile)
		iter->Render();

	m_pDeviceMgr->Render_End();
}

HRESULT MainGame::Initialize()
{
	HRESULT hr = DeviceMgr::GetInstance()->InitDevice(MODE_WIN);
	FAILED_CHECK_MSG_RETURN(hr, L"디바이스 초기화 에러", E_FAIL);

	m_pTextureMgr->Initialize();

	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Terrain", L"Tile", 2);
	//NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;


	Tile* temp;
	for (int i = 0; i < (WINCY / fCenterY) + 1; ++i)
	{
		for (int j = 0; j < (WINCX / fCenterX) +1; ++j)
		{
			temp = Tile::Create();
			if(i %2 == 0)
				temp->SetPos(fCenterX *j, fCenterY*i, 0);
			else
				temp->SetPos(fCenterX * j - fCenterX/2, fCenterY * i, 0);
			m_VecTile.push_back(temp);
		}
	}
	return S_OK;
}

void MainGame::Release()
{
	m_pKeyMgr->DestroyInstance();
	m_pTextureMgr->DestroyInstance();
	m_pDeviceMgr->DestroyInstance();
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

