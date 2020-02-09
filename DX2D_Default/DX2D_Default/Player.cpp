#include "pch.h"
#include "Player.h"

Player::Player() : m_pKeyMgr(CKeyMgr::GetInstance())
{
	ZeroMemory(m_vOrigin, sizeof(m_vOrigin));
	ZeroMemory(m_vConvert, sizeof(m_vConvert));
}

Player::~Player()
{
	Release();
}

void Player::Update()
{
	if (m_pKeyMgr->KeyPressing(KEY_LEFT))
		m_fAngle += m_fSpeed;
	if (m_pKeyMgr->KeyPressing(KEY_RIGHT))
		m_fAngle -= m_fSpeed;
	if (m_pKeyMgr->KeyPressing(KEY_UP))
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	if (m_pKeyMgr->KeyPressing(KEY_DOWN))
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;
}

void Player::LateUpdate()
{
	D3DXMATRIX scale, rotate, translation;
	
	D3DXMatrixScaling(&scale, 1.0f, 1.0f, 1.0f);
	D3DXMatrixRotationZ(&rotate, D3DXToRadian(-m_fAngle));	// 회전 기준이 데카르트 좌표계라서 win좌표처럼 -로넣음
	D3DXMatrixTranslation(&translation, m_tInfo.vPos.x, m_tInfo.vPos.y, 0);
	m_tInfo.matWorld = scale * rotate * translation;

	// 이동 벡터를 변환
	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vConvert[i], &m_vOrigin[i], &m_tInfo.matWorld);
	// 방향 벡터를 변환.
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
}

void Player::Render()	
{
	
}

HRESULT Player::Initialize()
{
	m_tInfo.vPos	= { 400.f, 300.f, 0.f}; // x, y, z
	m_tInfo.vDir	= { 0.f, -1.f, 0.f };
	m_tInfo.vLook	= { 0.f, -1, 0 };
	m_tInfo.fCX		= 100;
	m_tInfo.fCY		= 100;
	m_fSpeed		= 5.0f;
	m_fAngle		= 0.f;

	
	m_vOrigin[0] = { -50, -50, 0 };
	m_vOrigin[1] = {  50, -50, 0 };
	m_vOrigin[2] = {  50,  50, 0 };
	m_vOrigin[3] = { -50,  50, 0 };
	
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	//return E_FAIL;
	return S_OK;
}

void Player::Release()
{
}

Player* Player::Create()
{
	Player* pInstance = new Player;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
