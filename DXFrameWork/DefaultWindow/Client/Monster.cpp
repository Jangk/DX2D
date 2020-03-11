#include "stdafx.h"
#include "Monster.h"
#include "HPBar.h"


CMonster::CMonster()
{
}

CMonster::~CMonster()
{
	Release();
}

int CMonster::Update()
{
	m_HPBar->Update();
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta() * 0.5f;

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
		m_tFrame.fCurFrame = 0.f;

	if (m_CharacterInfo.iCurHP <= 0)
		return DEAD_OBJ;
	return 0;
}

void CMonster::LateUpdate()
{
	m_HPBar->LateUpdate();
}

void CMonster::Render()
{
	m_HPBar->Render();
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Cultist", L"Idle", (int)m_tFrame.fCurFrame);
	NULL_CHECK(pTexInfo);

	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(m_tInfo.fCenterX, m_tInfo.fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CMonster::Initialize()
{
	m_tInfo.vPos = { 800.f, 550.f, 0 };
	m_tFrame.fCurFrame = 0.f;
	m_tFrame.fMaxFrame = 40.f;


	D3DXMatrixScaling(&m_tInfo.matScale, 1, 1, 1);
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 1);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	
	
	// Ä³¸¯ÅÍ 
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Cultist", L"Idle", (int)m_tFrame.fCurFrame);
	NULL_CHECK_RETURN(pTexInfo, E_FAIL);
	

	m_CharacterInfo.iMaxHP		= 70;
	m_CharacterInfo.iCurHP		= m_CharacterInfo.iMaxHP;
	m_tInfo.fCenterX			= (float)pTexInfo->tImgInfo.Width  * 0.5f;
	m_tInfo.fCenterY			= (float)pTexInfo->tImgInfo.Height * 0.5f;

	m_HPBar = CHPBar::Create(this);
	return S_OK;
}

void CMonster::Release()
{
	SafeDelete<CHPBar*>(m_HPBar);
}

CMonster * CMonster::Create()
{
	CMonster* pInstance = new CMonster;
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}


