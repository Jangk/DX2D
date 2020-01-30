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
	D3DXVECTOR3 mouse = { (float)g_MousePos.x, (float)g_MousePos.y, 0 };
	m_tInfo.vDir = mouse - m_tInfo.vPos;
	m_tInfo.vPos += m_tInfo.vDir;
}

void Player::LateUpdate()
{
}

void Player::Render(HDC hDC)
{
	GameObject::UpdateRect();
	Rectangle(hDC, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
}

HRESULT Player::Initialize()
{
	m_tInfo.vPos = { 400.f, 300.f, 0.f }; // x, y, z
	m_tInfo.vDir = { 1.f, 1.f, 0.f };
	m_tInfo.fCX = 100;
	m_tInfo.fCY = 100;
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
