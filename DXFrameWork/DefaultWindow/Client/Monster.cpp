#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
}

int CMonster::Update()
{
	m_tFrame.fCurFrame += m_tFrame.fMaxFrame * m_pTimeMgr->GetDelta()/* * 20.f*/;

	if (m_tFrame.fMaxFrame <= m_tFrame.fCurFrame)
		m_tFrame.fCurFrame = 0.f;

	return 0;
}

void CMonster::LateUpdate()
{
}

void CMonster::Render()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Cultist", L"Idle", (int)m_tFrame.fCurFrame);
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMatrixScaling(&m_tInfo.matScale, 1, 1, 1);
	D3DXMatrixTranslation(&m_tInfo.matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 1);
	m_tInfo.matWorld = m_tInfo.matScale * m_tInfo.matTrans;
	m_pDeviceMgr->GetSprite()->SetTransform(&m_tInfo.matWorld);
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CMonster::Initialize()
{
	m_tInfo.vPos = { 800.f, 300.f, 0 };
	m_tFrame.fCurFrame = 0.f;
	m_tFrame.fMaxFrame = 40.f;

	return S_OK;
}

void CMonster::Release()
{
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
