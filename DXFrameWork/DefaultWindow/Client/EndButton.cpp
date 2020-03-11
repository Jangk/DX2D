#include "stdafx.h"
#include "EndButton.h"
#include "Mouse.h"


CEndButton::CEndButton() :
	m_bIsRender(true),
	m_bIsPicking(false)
{
}

CEndButton::~CEndButton()
{
	Release();
}

int CEndButton::Update()
{
	if (m_bIsRender)
	{
		if (m_pGameMgr->IsPickingObject(*this))
			m_bIsPicking = true;
		else
			m_bIsPicking = false;

		if (m_bIsPicking && m_pKeyMgr->KeyDown(KEY_LBUTTON))
			m_bIsRender = false;
	}
	return 0;
}

void CEndButton::LateUpdate()
{
}

void CEndButton::Render()
{
	float fCenterX;
	float fCenterY;
	if (!m_bIsRender)
		return;

	if (m_bIsPicking)
	{
		const TEX_INFO* pTexInfo;
		pTexInfo = m_pTextureMgr->GetTexInfo(L"UI", L"endTurnButtonGlow", 1);
		NULL_CHECK(pTexInfo);

		m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(m_tInfo.fCenterX, m_tInfo.fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		const TEX_INFO* pTexInfo;
		pTexInfo = m_pTextureMgr->GetTexInfo(L"UI", L"endTurnButton", 1);
		NULL_CHECK(pTexInfo);

		m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(m_tInfo.fCenterX, m_tInfo.fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}


	// 폰트
	swprintf_s(m_szText, L"턴 종료");
	D3DXMATRIX mat1, mat2, mat3;
	D3DXMatrixScaling(&mat1, 1.5f, 1.5f, 1.f);
	D3DXMatrixTranslation(&mat2, m_tInfo.vPos.x -50 , m_tInfo.vPos.y - 15, 1);
	mat3 = mat1* mat2;
	m_pDeviceMgr->GetSprite()->SetTransform(&mat3);
	m_pDeviceMgr->GetFont()->DrawText(
		m_pDeviceMgr->GetSprite(),
		m_szText,
		lstrlen(m_szText),
		nullptr,
		0,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CEndButton::Initialize()
{
	const TEX_INFO* pTexInfo	= m_pTextureMgr->GetTexInfo(L"UI", L"endTurnButton", 1);
	m_tInfo.vPos				= { WINCX - 150, WINCY - 200, 0 };
	m_tInfo.fCenterX			= (float)pTexInfo->tImgInfo.Width  * 0.5f;
	m_tInfo.fCenterY			= (float)pTexInfo->tImgInfo.Height * 0.5f;
	D3DXMatrixScaling(&m_tInfo.matScale, 1, 1, 1);
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 1);
	m_tInfo.matWorld			= m_tInfo.matScale* m_tInfo.matTrans;
	return S_OK;
}

void CEndButton::Release()
{
}

CEndButton * CEndButton::Create()
{
	CEndButton* pInstance = new CEndButton;
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}