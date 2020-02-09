#include "pch.h"
#include "Tile.h"

Tile::Tile() : m_pTextureMgr(TextureMgr::GetInstance()), m_pDeviceMgr(DeviceMgr::GetInstance())
{
}

Tile::~Tile()
{
}

void Tile::ChangeImage(int iImageIndex)
{
	m_iImageIndex = iImageIndex;
}

void Tile::Update()
{
}

void Tile::LateUpdate()
{
}

void Tile::Render()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Terrain", L"Tile", m_iImageIndex);
	NULL_CHECK(pTexInfo);

	D3DXMATRIX matScale, matRotZ, matTrans, matWorld;
	
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(0.f));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.vPos.z);
	
	matWorld = matScale * matRotZ * matTrans;
	

	m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
	m_pDeviceMgr->GetSprite()->Draw(
		pTexInfo->pTexture,									/* IDirect3DTexture9�� ������ */
		nullptr,											/* ��¿���, nullptr�� ���� ��ü ��� */
		&D3DXVECTOR3(m_tInfo.fCX/2, m_tInfo.fCY/2, 0.f),	/* �ؽ�ó�� �߽��� */
		nullptr,											/* ȭ�� ���� �ؽ�ó ��� ��ġ */
		D3DCOLOR_ARGB(255, 255, 255, 255)					/* ������� */);
	
	
}

HRESULT Tile::Initialize()
{
	m_tInfo.vPos	= { 400.f, 300.f, 0.f }; // x, y, z
	m_tInfo.vDir	= { 0.f, -1.f, 0.f };
	m_tInfo.vLook	= { 0.f, -1, 0 };
	m_tInfo.fCX		= 100;
	m_tInfo.fCY		= 100;
	m_fSpeed		= 0.0f;
	m_fAngle		= 0.f;

	m_iImageIndex	= 2;			// ��� �̹��� �ε�����ȣ
	
	
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Terrain", L"Tile", m_iImageIndex);
	//NULL_CHECK_RETURN(pTexInfo);

	m_tInfo.fCX = pTexInfo->tImgInfo.Width;
	m_tInfo.fCY = pTexInfo->tImgInfo.Height;

	return S_OK;
}

void Tile::Release()
{
}

Tile* Tile::Create()
{
	Tile* pInstance = new Tile;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}
