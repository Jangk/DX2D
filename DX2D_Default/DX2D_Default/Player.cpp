#include "pch.h"
#include "Player.h"

Player::Player() :m_fAngle(0)
{
}

Player::~Player()
{
	Release();
}

void Player::Update()
{
	POINT mpt;
	::GetCursorPos(&mpt);
	::ScreenToClient(g_hWnd, &mpt);
	D3DXVECTOR3 mouse = {(float)mpt.x, (float)mpt.y, 0 };


	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_tInfo.vPos += m_tInfo.vDir * m_fSpeed;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_tInfo.vPos -= m_tInfo.vDir * m_fSpeed;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_fAngle += m_fSpeed;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_fAngle -= m_fSpeed;

	//if (m_fAngle < -360 || m_fAngle > 360)
	//	m_fAngle = 0;


	for (int i = 0; i < 4; ++i)
	{
		m_vConvert[i].x = m_vOrigin[i].x *  cosf(m_fAngle) 
						- m_vOrigin[i].y * -sinf(m_fAngle);
		m_vConvert[i].y = m_vOrigin[i].x * -sinf(m_fAngle) 
						- m_vOrigin[i].y *  cosf(m_fAngle);
		m_vConvert[i] = m_vOrigin[i] + m_tInfo.vPos;
	}


	m_tInfo.vDir.x = m_tInfo.vLook.x * cosf(m_fAngle)
				   - m_tInfo.vLook.y * -sinf(m_fAngle);
	m_tInfo.vDir.y = m_tInfo.vLook.x * -sinf(m_fAngle)
				   - m_tInfo.vLook.y * cosf(m_fAngle);
}

void Player::LateUpdate()
{
}

void Player::Render(HDC hDC)	
{
	GameObject::UpdateRect();
	
	MoveToEx(hDC, m_vConvert[0].x, m_vConvert[0].y, nullptr);
	for(int i =1; i<4; ++i)
		LineTo(hDC, m_vConvert[i].x, m_vConvert[i].y);
	LineTo(hDC, m_vConvert[0].x, m_vConvert[0].y);


	TCHAR szBuf[64] = L"";
	swprintf_s(szBuf, L"°¢µµ: %0.1f", m_fAngle);
	RECT rc = { 100, 100, 200, 200 };
	DrawText(hDC, szBuf, lstrlen(szBuf), &rc, DT_NOCLIP);
}

HRESULT Player::Initialize()
{
	m_tInfo.vPos	= { 400.f, 300.f, 0.f }; // x, y, z
	m_tInfo.vDir	= { 0.f, 0.f, 0.f };
	m_tInfo.vLook	= { 0.f, -1, 0 };
	m_tInfo.fCX		= 100;
	m_tInfo.fCY		= 100;
	m_fSpeed		= 5.0f;
	m_fAngle		= 0.f;

	
	m_vOrigin[0].x = - 50;
	m_vOrigin[0].y = - 50;
	m_vOrigin[1].x = + 50;
	m_vOrigin[1].y = - 50;
	m_vOrigin[2].x = + 50;
	m_vOrigin[2].y = + 50;
	m_vOrigin[3].x = - 50;
	m_vOrigin[3].y = + 50;
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
