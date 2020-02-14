#include "stdafx.h"
#include "Block.h"

int Block::Update()
{
	UpdateTotalInfo();
	if(m_bIsDead)
		return DEAD_OBJ;
	return 0;
}

void Block::LateUpdate()
{
}

void Block::Render()
{
	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Terrain", L"Block", m_tInfo.byDrawID);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale,
		m_tInfo.vSize.x,
		m_tInfo.vSize.y,
		m_tInfo.vSize.z);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		m_tInfo.vPos.z);

	m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matTrans));
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT Block::Initialize()
{
	m_eBlockType		= BLOCK_NORMAL;
	m_tInfo.vPos		= { 100, 100, 0 };
	m_tInfo.vSize		= { 1,1,1 };
	m_tInfo.byDrawID	= 0;
	m_tInfo.byOption	= 0;
	UpdateTotalInfo();
	return S_OK;
}

void Block::Release()
{

}

void Block::SetBlock(BLOCK_TYPE eType)
{
	m_eBlockType = eType;
	m_tInfo.byDrawID = eType;
}

BLOCK_TYPE Block::GetBlockType()
{
	return m_eBlockType;
}

TILE_INFO Block::GetInfo()
{
	return m_tInfo;
}

void Block::SetSaveInfo(SAVE_INFO saveinfo)
{
	m_tInfo = saveinfo.tInfo;
	m_eBlockType = saveinfo.eBlockType;
}

void Block::SetPos(float x, float y, float z)
{
	m_tInfo.vPos = { x,y,z };
}

Block* Block::Create()
{
	Block* pInstance = new Block;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void Block::UpdateTotalInfo()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Terrain", L"Block", 0);
	NULL_CHECK(pTexInfo);
	m_TotalInfo.vPos			= m_tInfo.vPos;
	m_TotalInfo.fCX				= pTexInfo->tImgInfo.Width;
	m_TotalInfo.fCY				= pTexInfo->tImgInfo.Height;
	m_TotalInfo.m_Rect.left		= m_TotalInfo.vPos.x - m_TotalInfo.fCX * 0.5f;
	m_TotalInfo.m_Rect.top		= m_TotalInfo.vPos.y - m_TotalInfo.fCY * 0.5f;
	m_TotalInfo.m_Rect.right	= m_TotalInfo.vPos.x + m_TotalInfo.fCX * 0.5f;
	m_TotalInfo.m_Rect.bottom	= m_TotalInfo.vPos.y + m_TotalInfo.fCY * 0.5f;
}
