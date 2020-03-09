#include "stdafx.h"
#include "Nord.h"


CNord::CNord() : 
	m_eNord(NORD_MONSTER),
	m_bIsPicking(true)
{
}

CNord::~CNord()
{
}

int CNord::Update()
{
	return 0;
}

void CNord::LateUpdate()
{
}

void CNord::Render()
{
	const TEX_INFO* pTexInfo;
	float fCenterX;
	float fCenterY;


	wstring strState;
	switch (m_eNord)
	{
	case NORD_CHEST:
		strState = L"chest";
		break;
	case NORD_ELITE:
		strState = L"elite";
		break;
	case NORD_EVENT:
		strState = L"event";
		break;
	case NORD_MONSTER:
		strState = L"monster";
		break;
	case NORD_REST:
		strState = L"rest";
		break;
	case NORD_SHOP:
		strState = L"shop";
		break;
	}

	// 노드
	pTexInfo = m_pTextureMgr->GetTexInfo(L"WorldMap", strState, 1);
	NULL_CHECK(pTexInfo);

	fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&m_tInfo.matScale, 1, 1, 1);
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x - CScrollMgr::GetInstance()->GetScrollPos().x,
											 m_tInfo.vPos.y - CScrollMgr::GetInstance()->GetScrollPos().y,
											 m_tInfo.vPos.z);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(0, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));



	// 노드 아웃라인
	if (m_bIsPicking)
	{
		TCHAR str[MIN_STR];
		wprintf(str, "%s", L"outline");
		pTexInfo = m_pTextureMgr->GetTexInfo(L"WorldMap", strState, 1);
		NULL_CHECK(pTexInfo);

		fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
		fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

		m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(0, fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

HRESULT CNord::Initialize()
{
	D3DXMatrixScaling(&m_tInfo.matScale, 1, 1, 1);
	return S_OK;
}

void CNord::Release()
{
}

CNord* CNord::Create()
{
	CNord* pInstance = new CNord;
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CNord::SetNord(NORD_TYPE eType)
{
	m_eNord = eType;
}


