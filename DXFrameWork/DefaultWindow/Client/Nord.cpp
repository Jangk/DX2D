#include "stdafx.h"
#include "Nord.h"
#include "Mouse.h"


CNord::CNord() : 
	m_pKeyMgr(CKeyMgr::GetInstance()),
	m_eNord(NORD_MONSTER),
	m_bIsPicking(false)
{
}

CNord::~CNord()
{
}

int CNord::Update()
{
	m_bIsPicking = IsPicking();
	if (m_bIsPicking && m_pKeyMgr->KeyDown(KEY_LBUTTON))
	{	// 현재 전부 스테이지 씬
		switch (m_eNord)
		{
		case NORD_CHEST:
			CSceneMgr::GetInstance()->SceneChange(SCENE_WORLD_MAP, SCENE_STAGE);
			break;
		case NORD_ELITE:
			CSceneMgr::GetInstance()->SceneChange(SCENE_WORLD_MAP, SCENE_STAGE);
			break;
		case NORD_EVENT:
			CSceneMgr::GetInstance()->SceneChange(SCENE_WORLD_MAP, SCENE_STAGE);
			break;
		case NORD_MONSTER:
			CSceneMgr::GetInstance()->SceneChange(SCENE_WORLD_MAP, SCENE_STAGE);
			break;
		case NORD_REST:
			CSceneMgr::GetInstance()->SceneChange(SCENE_WORLD_MAP, SCENE_STAGE);
			break;
		case NORD_SHOP:
			CSceneMgr::GetInstance()->SceneChange(SCENE_WORLD_MAP, SCENE_STAGE);
			break;
		}
	}
	return 0;
}

void CNord::LateUpdate()
{
}

void CNord::Render()
{
	const TEX_INFO* pTexInfo;

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


	// 노드 아웃라인
	if (m_bIsPicking)
	{
		wstring str = L"Outline";
		strState += str;
		pTexInfo = m_pTextureMgr->GetTexInfo(L"WorldMap", strState, 1);
		NULL_CHECK(pTexInfo);

		D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x,
			m_tInfo.vPos.y - CScrollMgr::GetInstance()->GetScrollPos().y,
			0.5);
		m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
		m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(m_tInfo.fCenterX, m_tInfo.fCenterY, 0.f),
			nullptr, D3DCOLOR_ARGB(128, 0, 0, 0));
	}


	// 노드
	pTexInfo = m_pTextureMgr->GetTexInfo(L"WorldMap", strState, 1);
	NULL_CHECK(pTexInfo);

	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x ,
		m_tInfo.vPos.y - CScrollMgr::GetInstance()->GetScrollPos().y,
		0);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(m_tInfo.fCenterX, m_tInfo.fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CNord::Initialize()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"WorldMap", L"monster", 1);

	m_tInfo.fCenterX = (float)pTexInfo->tImgInfo.Width  * 0.5f;
	m_tInfo.fCenterY = (float)pTexInfo->tImgInfo.Height * 0.5f;
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

bool CNord::IsPicking()
{
	float fHalfCX;
	float fHalfCY;
	float mouseX;
	float mouseY;

	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"WorldMap", L"chest", 1);
	fHalfCX = pTexInfo->tImgInfo.Width * 0.5f;
	fHalfCY = pTexInfo->tImgInfo.Height* 0.5f;
	mouseX = CMouse::GetMousePos().x - CScrollMgr::GetInstance()->GetScrollPos().x;
	mouseY = CMouse::GetMousePos().y + CScrollMgr::GetInstance()->GetScrollPos().y;

	// 점 ( 직선의 방정식이 아니면 y 반대로 안해도된다)
	D3DXVECTOR3 vPoint[4] =
	{	// 
		D3DXVECTOR3(m_tInfo.vPos.x - fHalfCX, m_tInfo.vPos.y - fHalfCY, 0.f),
		D3DXVECTOR3(m_tInfo.vPos.x + fHalfCX, m_tInfo.vPos.y - fHalfCY, 0.f),
		D3DXVECTOR3(m_tInfo.vPos.x + fHalfCX, m_tInfo.vPos.y + fHalfCY, 0.f),
		D3DXVECTOR3(m_tInfo.vPos.x - fHalfCX, m_tInfo.vPos.y + fHalfCY, 0.f)
	};

	if (vPoint[0].x  < mouseX && vPoint[1].x > mouseX &&
		vPoint[0].y < mouseY && vPoint[3].y > mouseY)
		return true;
	return false;
}


