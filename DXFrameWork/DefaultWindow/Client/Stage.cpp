#include "stdafx.h"
#include "Stage.h"
#include "Terrain.h"
#include "Card.h"
#include "AttackCard.h"
#include "Card.h"
#include "Mouse.h"
#include "Player.h"
#include "Monster.h"
#include "TopPanel.h"
#include "Cost.h"
#include "EndButton.h"


CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

int CStage::Update()
{
	m_pObjectMgr->Update();
	m_pGameMgr->Update();
	return NO_EVENT;
}

void CStage::LateUpdate()
{
	m_pObjectMgr->LateUpdate();
}

void CStage::Render()
{
	// ¹è°æ
	D3DXMATRIX matScale, matTrans,matWorld;
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Stage", L"Background", 1);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&matScale, 1, 1, 1);
	D3DXMatrixTranslation(&matTrans, WINCX*0.5f, WINCY*0.5f, 1);
	matWorld = matScale * matTrans;
	m_pDeviceMgr->GetSprite()->SetTransform(&matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pObjectMgr->Render();
	m_pGameMgr->RenderState();
}

HRESULT CStage::Initialize()
{
	if(m_pObjectMgr->GetGameObject(OBJECT_PLAYER).size() == 0)
		m_pObjectMgr->AddObject(OBJECT_PLAYER, CPlayer::Create());
	m_pObjectMgr->AddObject(OBJECT_MONSTER, CMonster::Create());
	m_pObjectMgr->AddObject(OBJECT_UI, CTopPanel::Create());
	m_pObjectMgr->AddObject(OBJECT_UI, CTopPanel::Create());
	m_pObjectMgr->AddObject(OBJECT_UI, CCost::Create());
	m_pObjectMgr->AddObject(OBJECT_UI, CEndButton::Create());
	m_pGameMgr->Initialize();
	return S_OK;
}

void CStage::Release()
{
	m_pObjectMgr->DeleteGruop(OBJECT_UI);
	m_pObjectMgr->DeleteGruop(OBJECT_MONSTER);
}

CStage* CStage::Create()
{
	CStage* pInstance = new CStage;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

