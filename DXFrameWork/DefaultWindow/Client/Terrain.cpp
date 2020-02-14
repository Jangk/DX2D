#include "stdafx.h"
#include "Terrain.h"
#include "Mouse.h"
#include "ScrollMgr.h"

CTerrain::CTerrain()
	: m_pKeyMgr(CKeyMgr::GetInstance())
{
}


CTerrain::~CTerrain()
{
	Release();
}

int CTerrain::GetTileIndex(const D3DXVECTOR3& vPos)
{
	for (int i = 0; i < (int)m_vecTile.size(); ++i)
	{
		if (IsPicking(vPos, i))
			return i;
	}
	
	return -1;
}

int CTerrain::Update()
{
	// 초당 100씩 움직인다.
	float fMoveSpeed = 100.f * m_pTimeMgr->GetDelta();

	if (0.f > CMouse::GetMousePos().x)
		CScrollMgr::MoveScrollPos(D3DXVECTOR3(-fMoveSpeed, 0.f, 0.f));
	if (0.f > CMouse::GetMousePos().y)
		CScrollMgr::MoveScrollPos(D3DXVECTOR3(0.f, -fMoveSpeed, 0.f));
	if ((float)WINCX < CMouse::GetMousePos().x)
		CScrollMgr::MoveScrollPos(D3DXVECTOR3(fMoveSpeed, 0.f, 0.f));
	if ((float)WINCY < CMouse::GetMousePos().y)
		CScrollMgr::MoveScrollPos(D3DXVECTOR3(0.f, fMoveSpeed, 0.f));
	
	if (m_pKeyMgr->KeyDown(KEY_LBUTTON))
		TileChange(CMouse::GetMousePos() + CScrollMgr::GetScrollPos(), 3);

	return NO_EVENT;
}

void CTerrain::LateUpdate()
{
}

void CTerrain::Render()
{
	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		pTexInfo = m_pTextureMgr->GetTexInfo(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);
		NULL_CHECK_CONTINUE(pTexInfo);

		D3DXMatrixScaling(&matScale,
			m_vecTile[i]->vSize.x,
			m_vecTile[i]->vSize.y,
			m_vecTile[i]->vSize.z);
		D3DXMatrixTranslation(&matTrans,
			m_vecTile[i]->vPos.x - CScrollMgr::GetScrollPos().x,
			m_vecTile[i]->vPos.y - CScrollMgr::GetScrollPos().y,
			m_vecTile[i]->vPos.z);		

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matTrans));
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, 
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

HRESULT CTerrain::Initialize()
{
	m_vecTile.reserve(TILEX * TILEY);

	TILE_INFO* pTile = nullptr;
	float fX = 0.f, fY = 0.f;

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			fX = (j* TILECX) + (i % 2) * (TILECX * 0.5f);
			fY = i * (TILECY * 0.5f);

			pTile = new TILE_INFO;
			pTile->vPos = { fX, fY, 0.f };
			pTile->vSize = { 1.f, 1.f, 0.f };
			pTile->byDrawID = 2;
			pTile->byOption = 0;

			m_vecTile.push_back(pTile);
		}
	}

	return S_OK;
}

void CTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<TILE_INFO*>);
	m_vecTile.clear();
}

void CTerrain::TileChange(const D3DXVECTOR3& vPos, const BYTE& byDrawID, const BYTE& byOption)
{
	int iIndex = GetTileIndex(vPos);

	if (-1 == iIndex)
		return;

	m_vecTile[iIndex]->byDrawID = byDrawID;
	m_vecTile[iIndex]->byOption = byOption;
}

bool CTerrain::IsPicking(const D3DXVECTOR3& vPos, int iIndex)
{
	// 내적을 이용한 방식 (데카르트 기준)
	// 마름모 꼭지점 설정 12시, 3시, 6시, 9시 순서
	D3DXVECTOR3 vPoint[4] =
	{
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + TILECY * 0.5f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + TILECX * 0.5f, m_vecTile[iIndex]->vPos.y, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - TILECY * 0.5f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - TILECX * 0.5f, m_vecTile[iIndex]->vPos.y, 0.f)
	};

	// 각 꼭지점으로부터 시계방향으로 방향벡터들을 구함.
	D3DXVECTOR3 vDir[4] =
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3],
	};

	// 위에서 구한 방향벡터들의 각 법선벡터들을 구한다.
	D3DXVECTOR3 vNormal[4] = {};

	for (int i = 0; i < 4; ++i)
		D3DXVec3Cross(&vNormal[i], &D3DXVECTOR3(0.f, 0.f, 1.f), &vDir[i]);

	// 각 꼭지점에서부터 마우스위치로의 방향벡터를 구한다.
	D3DXVECTOR3 vMouseDir[4] =
	{
		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};

	// vMouseDir과 vNormal을 각각 내적해서 모두 둔각(음수)이 나오면 TRUE!
	for (int i = 0; i < 4; ++i)
	{
		if (0 < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
			return false;
	}

	return true;
}

CTerrain* CTerrain::Create()
{
	CTerrain* pInstance = new CTerrain;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
