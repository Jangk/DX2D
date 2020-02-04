#include "pch.h"
#include "Player.h"

Player::Player() :m_fAngle(0), m_pKeyMgr(CKeyMgr::GetInstance())
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
	//과제   구현. 아래
	if (m_pKeyMgr->KeyPressing(KEY_LEFT))
		m_fAngle += m_fSpeed;
	if (m_pKeyMgr->KeyPressing(KEY_RIGHT))
		m_fAngle -= m_fSpeed;
	if (m_pKeyMgr->KeyPressing(KEY_UP))
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	if (m_pKeyMgr->KeyPressing(KEY_DOWN))
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;

	//if (m_fAngle <= -360 || m_fAngle >= 360)
	//	m_fAngle = 0;
}

void Player::LateUpdate()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			m_Matrix.m[i][j] = 0;
	}
	//for (int i = 0; i < 4; ++i)
	//{
	//	m_vConvert[i].x = m_vOrigin[i].x *  cosf(D3DXToRadian(m_fAngle)) 
	//					- m_vOrigin[i].y * -sinf(D3DXToRadian(m_fAngle));
	//	m_vConvert[i].y = m_vOrigin[i].x * -sinf(D3DXToRadian(m_fAngle)) 
	//					+ m_vOrigin[i].y *  cosf(D3DXToRadian(m_fAngle));
	//	m_vConvert[i] += m_tInfo.vPos;
	//}
	//
	//m_tInfo.vDir.x = m_tInfo.vLook.x *  cosf(D3DXToRadian(m_fAngle))
	//			   - m_tInfo.vLook.y * -sinf(D3DXToRadian(m_fAngle));
	//m_tInfo.vDir.y = m_tInfo.vLook.x * -sinf(D3DXToRadian(m_fAngle))
	//			   + m_tInfo.vLook.y *  cosf(D3DXToRadian(m_fAngle));
	//
	//D3DXVec4Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
}

void Player::Render(HDC hDC)	
{
	GameObject::UpdateRect();
	MoveToEx(hDC, (int)m_vConvert[0].x, (int)m_vConvert[0].y, nullptr);
	LineTo(hDC, (int)m_vConvert[1].x, (int)m_vConvert[1].y);
	MoveToEx(hDC, (int)m_vConvert[0].x, (int)m_vConvert[0].y, nullptr);
	LineTo(hDC, (int)m_vConvert[1].x, (int)m_vConvert[1].y);
	LineTo(hDC, (int)m_vConvert[2].x, (int)m_vConvert[2].y);
	LineTo(hDC, (int)m_vConvert[3].x, (int)m_vConvert[3].y);
	LineTo(hDC, (int)m_vConvert[0].x, (int)m_vConvert[0].y);
	
	for (int i = 0; i < 2; ++i)
		Ellipse(hDC, int(m_vConvert[i].x - 10.f), int(m_vConvert[i].y - 10.f),
			int(m_vConvert[i].x + 10.f), int(m_vConvert[i].y + 10.f));


	TCHAR szBuf[64] = L"";
	swprintf_s(szBuf, L"각도: %0.1f", m_fAngle);
	RECT rc = { 100, 100, 200, 200 };
	DrawText(hDC, szBuf, lstrlen(szBuf), &rc, DT_NOCLIP);
}

HRESULT Player::Initialize()
{
	m_tInfo.vPos	= { 400.f, 300.f, 0.f, 1.f }; // x, y, z, w
	m_tInfo.vDir	= { 0.f, -1.f, 0.f, 0.f };
	m_tInfo.vLook	= { 0.f, -1, 0, 0.f };
	m_tInfo.fCX		= 100;
	m_tInfo.fCY		= 100;
	m_fSpeed		= 5.0f;
	m_fAngle		= 0.f;

	
	m_vOrigin[0] = { -50, -50, 0, 1 };
	m_vOrigin[1] = {  50, -50, 0, 1 };
	m_vOrigin[2] = {  50,  50, 0, 1 };
	m_vOrigin[3] = { -50,  50, 0, 1 };
	
	for (auto i : m_vConvert)
		i = { 0, 0, 0, 1 };

	 D3DXMatrixIdentity(&m_Matrix);
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
