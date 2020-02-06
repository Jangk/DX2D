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
	D3DXMatrixRotationZ(&rotate, D3DXToRadian(-m_fAngle));	// ȸ�� ������ ��ī��Ʈ ��ǥ��� win��ǥó�� -�γ���
	D3DXMatrixTranslation(&translation, m_tInfo.vPos.x, m_tInfo.vPos.y, 0);
	m_tInfo.matWorld = scale * rotate * translation;

	// �̵� ���͸� ��ȯ
	for (int i = 0; i < 4; ++i)
		D3DXVec3TransformCoord(&m_vConvert[i], &m_vOrigin[i], &m_tInfo.matWorld);
	// ���� ���͸� ��ȯ.
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
}

void Player::Render(HDC hDC)	
{
	GameObject::UpdateRect();
	MoveToEx(hDC, (int)m_vConvert[0].x, (int)m_vConvert[0].y, nullptr);
	LineTo(hDC, (int)m_vConvert[1].x, (int)m_vConvert[1].y);
	LineTo(hDC, (int)m_vConvert[2].x, (int)m_vConvert[2].y);
	LineTo(hDC, (int)m_vConvert[3].x, (int)m_vConvert[3].y);
	LineTo(hDC, (int)m_vConvert[0].x, (int)m_vConvert[0].y);

	for (int i = 0; i < 2; ++i)
		Ellipse(hDC, int(m_vConvert[i].x - 10.f), int(m_vConvert[i].y - 10.f),
			int(m_vConvert[i].x + 10.f), int(m_vConvert[i].y + 10.f));

	TCHAR szBuf[64] = L"";
	swprintf_s(szBuf, L"����: %0.1f", m_fAngle);
	RECT rc = { 100, 100, 200, 200 };
	DrawText(hDC, szBuf, lstrlen(szBuf), &rc, DT_NOCLIP);
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
