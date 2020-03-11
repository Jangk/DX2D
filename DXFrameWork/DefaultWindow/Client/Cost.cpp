#include "stdafx.h"
#include "Cost.h"
#include "Player.h"


CCost::CCost()
{
}


CCost::~CCost()
{
}

int CCost::Update()
{
	return 0;
}

void CCost::LateUpdate()
{
}

void CCost::Render()
{
	const TEX_INFO* pTexInfo;
	float fCenterX;
	float fCenterY;
	pTexInfo = m_pTextureMgr->GetTexInfo(L"UI", L"Cost", 1);
	NULL_CHECK(pTexInfo);

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(m_tInfo.fCenterX, m_tInfo.fCenterY, 0.2f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


	// ÆùÆ®
	swprintf_s(m_szCost, L"%d/%d", m_Player->GetCharacterInfo().iCurCost, m_Player->GetCharacterInfo().iMaxCost);
	D3DXMATRIX mat1, mat2, mat3;
	D3DXMatrixScaling(&mat1, 2, 2, 1);
	D3DXMatrixTranslation(&mat2, m_tInfo.vPos.x - 25 , m_tInfo.vPos.y-20, 0.1f);
	mat3 =  mat1* mat2;
	m_pDeviceMgr->GetSprite()->SetTransform(&mat3);
	m_pDeviceMgr->GetFont()->DrawText(
		m_pDeviceMgr->GetSprite(),
		m_szCost,
		lstrlen(m_szCost),
		nullptr,
		0,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CCost::Initialize()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"UI", L"Cost", 1);
	m_Player			= dynamic_cast<CPlayer*>(*m_pObjectMgr->GetInstance()->GetGameObject(OBJECT_PLAYER).begin());
	m_tInfo.fCenterX	= pTexInfo->tImgInfo.Width * 0.5f;
	m_tInfo.fCenterY	= pTexInfo->tImgInfo.Height * 0.5f;
	m_tInfo.vPos		= {100, WINCY - 200, 0 };
	D3DXMatrixScaling(&m_tInfo.matScale, 1, 1, 1);
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.8f);
	m_tInfo.matWorld	= m_tInfo.matScale* m_tInfo.matTrans;
	return S_OK;
}

void CCost::Release()
{
}

CCost* CCost::Create()
{
	CCost* pInstance = new CCost;
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}