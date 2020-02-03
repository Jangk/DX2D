#include "pch.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	Release();
}

void Player::Update()
{
	POINT pt;
	::GetCursorPos(&pt);
	::ScreenToClient(g_hWnd, &pt);
	D3DXVECTOR3 mouse = {(float)pt.x, (float)pt.y, 0 };

	// 벡터 내적으로 구하기.
	m_tInfo.vDir = mouse - m_tInfo.vPos;
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	float fCos = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);
	float radian =  acosf(fCos);
	if (mouse.y > m_tInfo.vPos.y)
		radian *= -1;
	
	m_tInfo.vPos.x += cosf(radian);
	m_tInfo.vPos.y -= sinf(radian);
}

void Player::LateUpdate()
{
}

void Player::Render(HDC hDC)
{
	GameObject::UpdateRect();
	Rectangle(hDC, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);

	MoveToEx(hDC, m_tInfo.vPos.x, m_tInfo.vPos.y, nullptr);
	LineTo(hDC, m_tInfo.vPos.x + cosf(m_Angle * 3.14 / 180) * 100, 
				m_tInfo.vPos.y + sinf(m_Angle * 3.14 / 180) * 100);
	// 글자
	TCHAR szBuf[64] = L"";
	swprintf_s(szBuf, L"각도: %0.1f", m_Angle);
	RECT rc = { 100, 100, 200, 200 };
	DrawText(hDC, szBuf, lstrlen(szBuf), &rc, DT_NOCLIP);
}

HRESULT Player::Initialize()
{
	m_tInfo.vPos	= { 400.f, 300.f, 0.f }; // x, y, z
	m_tInfo.vDir	= { 1.f, 1.f, 0.f };
	m_tInfo.vLook	= { 1.f, 0, 0 };
	m_tInfo.fCX		= 100;
	m_tInfo.fCY		= 100;
	m_fSpeed		= 5.0f;
	m_Angle			= 0.f;
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
