#include "stdafx.h"
#include "Terrain.h"
#include "Mouse.h"

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
	if (m_pKeyMgr->KeyDown(KEY_LBUTTON))
		TileChange(CMouse::GetMousePos(), 3);

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
			m_vecTile[i]->vPos.x,
			m_vecTile[i]->vPos.y,
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
	// ������ ������ (��ī��Ʈ ����)
	// 0 = ax + b - y: ���� ���� a, b�� �� x, y�� ����ϰ� �ִ�.
	// 0 > ax + b - y: ���� ���� a, b���� �� x, y�� ���� �ִ�.
	// 0 < ax + b - y: ���� ���� a, b���� �� x, y�� �Ʒ��� �ִ�.

	// ����(a) 4�� ����.
	float fGradient[4] =
	{
		(TILECY * 0.5f) / (TILECX * 0.5f),
		-(TILECY * 0.5f) / (TILECX * 0.5f),
		(TILECY * 0.5f) / (TILECX * 0.5f),
		-(TILECY * 0.5f) / (TILECX * 0.5f)
	};

	// y����(b)�� ���ϱ� ���ؼ��� �Ʒ����� �������� �����ؾ� ��.
	// 0 = ax + b - y	
	// ���� 4���� ���� ����ϰ� �ִ� �� 4���� ����. (12��, 3��, 6��, 9��)
	D3DXVECTOR3 vPoint[4] =
	{
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + TILECY * 0.5f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + TILECX * 0.5f, m_vecTile[iIndex]->vPos.y, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - TILECY * 0.5f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - TILECX * 0.5f, m_vecTile[iIndex]->vPos.y, 0.f),
	};

	// y���� 4�� ����.
	// b = -ax + y
	float fB[4] = 
	{
		-fGradient[0] * vPoint[0].x + vPoint[0].y,
		-fGradient[1] * vPoint[1].x + vPoint[1].y,
		-fGradient[2] * vPoint[2].x + vPoint[2].y,
		-fGradient[3] * vPoint[3].x + vPoint[3].y
	};

	// 0 = ax + b - y: ���� ���� a, b�� �� x, y�� ����ϰ� �ִ�.
	// 0 > ax + b - y: ���� ���� a, b���� �� x, y�� ���� �ִ�.
	// 0 < ax + b - y: ���� ���� a, b���� �� x, y�� �Ʒ��� �ִ�.
	return (0 < fGradient[0] * vPos.x + fB[0] - vPos.y &&
		0 < fGradient[1] * vPos.x + fB[1] - vPos.y &&
		0 > fGradient[2] * vPos.x + fB[2] - vPos.y &&
		0 > fGradient[3] * vPos.x + fB[3] - vPos.y);
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

void CTerrain::SetPos(float x, float y, float z)
{
	// ���� �ʿ����.
}

void CTerrain::UpdateTotalInfo()
{
	// ���� �ʿ����.
}
