#include "stdafx.h"
#include "Player.h"
#include "Mouse.h"

CPlayer::CPlayer()
	: m_fAngle(0.f), m_fSpeed(0.f),
	m_pKeyMgr(CKeyMgr::GetInstance()),
	m_pTimeMgr(CTimeMgr::GetInstance()),
	m_iCount(0)
{
}

CPlayer::~CPlayer()
{
	Release();
}

int CPlayer::Update()
{
	AfterImage();
	Input();
	if(!m_bIsMachine)
		Bounce();
	else
		m_tInfo.vPos.x += 7;

	if (m_tInfo.vPos.y > WINCY ||
		m_tInfo.vPos.x > WINCX ||
		m_tInfo.vPos.x < 0)
		m_bIsDead = true;
	UpdateTotalInfo();
	return S_OK;
}

void CPlayer::Render()
{
	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Ball", L"", 0);
	NULL_CHECK(pTexInfo);
	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;


	D3DXMatrixScaling(&matScale, 1, 1, 1);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		m_tInfo.vPos.z);
	m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matTrans));
	m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	for (int i = 0; i < 10; ++i)
	{
		D3DXMatrixTranslation(&matTrans,
			m_vAfterimage[i].x,
			m_vAfterimage[i].y,
			m_vAfterimage[i].z);
		m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matTrans));
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(100 - i*10, 255, 255, 255));
	}

}

void CPlayer::LateUpdate()
{
	D3DXMATRIX matScale, matRotZ, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f); // 다이렉트 크기행렬 함수
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(-m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f); // 다이렉트 이동행렬 함수

	m_tInfo.matWorld = matScale * matRotZ * matTrans;

	// 다이렉트 방향벡터 연산 함수. w값은 0이다.
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
}

HRESULT CPlayer::Initialize()
{
	D3DXMatrixIdentity(&m_tInfo.matWorld); // 다이렉트 항등행렬 함수
	m_tInfo.vPos	= { 400.f, 300.f, 0.f }; // x, y, z
	m_tInfo.vDir	= { 0.f, 0.f, 0.f };
	m_tInfo.vLook	= { 0.f, -1.f, 0.f };	
	m_fSpeed		= 1.f;
	m_fJumpForce	= 10.f;
	m_fJumpAcc		= 0;
	m_fMoveAcc		= 0;

	m_bIsCol		= false;
	m_bIsMachine	= false;
	m_bIsJump		= false;
	UpdateTotalInfo();

	m_vAfterImageIndex = 0;
	for (int i = 0; i < 10; ++i)
		m_vAfterimage[i] = { 0,0,0 };
	return S_OK;
}

void CPlayer::Release()
{
}

CPlayer* CPlayer::Create()
{
	CPlayer* pInstance = new CPlayer;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CPlayer::Input()
{
	if (m_pKeyMgr->KeyPressing(KEY_LEFT))
	{
		m_bIsMachine = false;
		m_fMoveAcc -= m_fSpeed;
		if (m_fMoveAcc < -5)
			m_fMoveAcc = -5;
	}
	if (m_pKeyMgr->KeyPressing(KEY_RIGHT))
	{
		m_bIsMachine = false;
		m_fMoveAcc += m_fSpeed;
		if (m_fMoveAcc > 5)
			m_fMoveAcc = 5;
	}
	if(!m_bIsMachine)
		m_tInfo.vPos.x += m_fMoveAcc ;
}

void CPlayer::Bounce()
{
	// 착지할 때
	if (m_bIsCol)
	{
		m_bIsCol = false;
		m_fJumpAcc = 0.5;
	}
	
	
	// y = 힘 * 가속도 * sin(90) - 중력(9.8) * 가속도^2 * 0.5
	float fLeftVal = m_fJumpForce * m_fJumpAcc;
	float fRightVal = GRAVITY * m_fJumpAcc * m_fJumpAcc * 0.5f;

	m_tInfo.vPos.y -= fLeftVal - fRightVal;
	m_fJumpAcc += 0.1f;
	if (m_fJumpAcc > 3.f)		// 가속도 최대치 제한
		m_fJumpAcc = 3.f;
}

void CPlayer::AfterImage()
{
	++m_vAfterImageIndex;
	if (m_vAfterImageIndex >= 10)
		m_vAfterImageIndex = 0;
	m_vAfterimage[m_vAfterImageIndex] = m_tInfo.vPos;
}

void CPlayer::SetColX()
{
	m_bIsMachine = false;
	m_fMoveAcc *= -1;
}

void CPlayer::SetColY(BLOCK_TYPE type)
{
	switch (type)
	{
	case BLOCK_NORMAL:
		m_bIsCol = true;
		m_bIsJump = false;
		m_fJumpForce = 10;
		break;
	case BLOCK_BROKEN:
		m_bIsCol = true;
		m_bIsJump = false;
		m_fJumpForce = 10;
		break;
	case BLOCK_JUMP:
		m_bIsCol = true;
		m_bIsJump = true;
		m_fJumpForce = 12;			// 임의 점프값
		break;
	case BLOCK_MACHINE:
		m_bIsMachine = true;
		m_bIsJump = false;
		m_fJumpForce = 10;
		m_fMoveAcc = 0;
		break;
	case BLOCK_BOMB:
		m_bIsDead = true;
		break;
	default:
		break;
	}
	if (m_bIsCol)
		m_bIsMachine = false;
}

void CPlayer::SetRespawn(D3DXVECTOR3 respawnPos)
{
	m_bIsDead = false;
	m_tInfo.vPos = respawnPos;
	m_fJumpAcc = 0.5f;
	m_fMoveAcc = 0.0f;
	
}

bool CPlayer::GetIsDead()
{
	return m_bIsDead;
}

void CPlayer::SetPos(float x, float y, float z)
{
	m_tInfo.vPos = { x, y, z };
}

void CPlayer::UpdateTotalInfo()
{
	const TEX_INFO* pTexInfo = m_pTextureMgr->GetTexInfo(L"Ball", L"", 0);
	NULL_CHECK(pTexInfo);
	m_TotalInfo.vPos = m_tInfo.vPos;
	m_TotalInfo.fCX = pTexInfo->tImgInfo.Width;
	m_TotalInfo.fCY = pTexInfo->tImgInfo.Height;
	m_TotalInfo.m_Rect.left		= m_TotalInfo.vPos.x - m_TotalInfo.fCX * 0.5f;
	m_TotalInfo.m_Rect.top		= m_TotalInfo.vPos.y - m_TotalInfo.fCY * 0.5f;
	m_TotalInfo.m_Rect.right	= m_TotalInfo.vPos.x + m_TotalInfo.fCX * 0.5f;
	m_TotalInfo.m_Rect.bottom	= m_TotalInfo.vPos.y + m_TotalInfo.fCY * 0.5f;
}