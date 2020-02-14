#include "stdafx.h"
#include "DeviceMgr.h"

IMPLEMENT_SINGLETON(CDeviceMgr)

CDeviceMgr::CDeviceMgr()
{
}


CDeviceMgr::~CDeviceMgr()
{
	Release();
}

LPDIRECT3DDEVICE9 CDeviceMgr::GetDevice() const
{
	return m_pGraphicDev;
}

LPD3DXSPRITE CDeviceMgr::GetSprite() const
{
	return m_pSprite;
}

LPD3DXFONT CDeviceMgr::GetFont() const
{
	return m_pFont;
}

HRESULT CDeviceMgr::InitDevice(DISPLAY_MODE eMode)
{
	// ��ġ �ʱ�ȭ

	// 1. IDirect3D9 ��ü ����
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	NULL_CHECK_MSG_RETURN(m_pSDK, L"Direct3DCreate9 Failed", E_FAIL);

	// 2. IDirect3D9 ��ü�� ���ؼ� ��ġ�� �����Ѵ�.
	D3DCAPS9 d3dcaps;
	ZeroMemory(&d3dcaps, sizeof(D3DCAPS9));

	// HAL (Hardware Abstraction Layer, �ϵ���� �߻� ����)
	HRESULT hr = m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dcaps);
	FAILED_CHECK_MSG_RETURN(hr, L"GetDeviceCaps Failed", E_FAIL);

	// 2-1. ���� ��ġ�� ���ؽ� ���μ����� �����ϴ��� ����.
	// ���ؽ� ���μ���: ���� ��ȯ + ���� ����
	DWORD vp = 0;

	if (d3dcaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;	

	// 3. IDirect3D9 ��ü�� ���ؼ� IDirect3DDevice9 ��ü�� �����Ѵ�.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth = WINCX;
	d3dpp.BackBufferHeight = WINCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD; // ����ü�� ���
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = eMode; // TRUE: â���, FALSE: ��üȭ�� ���
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	/* FullScreen_RefreshRateInHz must be zero for Windowed mode */
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	hr = m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp, &m_pGraphicDev);
	FAILED_CHECK_MSG_RETURN(hr, L"CreateDevice Failed", E_FAIL);

	// m_pSprite ����
	hr = D3DXCreateSprite(m_pGraphicDev, &m_pSprite);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateSprite Failed", E_FAIL);

	// m_pFont ����
	D3DXFONT_DESC tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESC));

	tFontInfo.Width = 10;
	tFontInfo.Height = 20;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"consolas");

	hr = D3DXCreateFontIndirect(m_pGraphicDev, &tFontInfo, &m_pFont);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateFontIndirect Failed", E_FAIL);

	return S_OK;
}

void CDeviceMgr::Render_Begin()
{
	// �ĸ���� ����
	m_pGraphicDev->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);

	// �ĸ���ۿ� �׸��⸦ ����
	m_pGraphicDev->BeginScene();

	// ��������Ʈ �׸���!
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDeviceMgr::Render_End()
{
	// ��������Ʈ �� �׷Ⱦ�!
	m_pSprite->End();

	// �ĸ���ۿ� �׸��⸦ ��ħ
	m_pGraphicDev->EndScene();

	// ȭ�鿡 ���
	m_pGraphicDev->Present(nullptr, nullptr, nullptr, nullptr);
}

void CDeviceMgr::Release()
{
	if(m_pFont->Release())
		::MessageBox(0, L"m_pFont Release Failed", L"System Error", MB_OK);
	if(m_pSprite->Release())
		::MessageBox(0, L"m_pSprite Release Failed", L"System Error", MB_OK);
	if (m_pGraphicDev->Release())
		::MessageBox(0, L"m_pGraphicDev Release Failed", L"System Error", MB_OK);
	if(m_pSDK->Release())
		::MessageBox(0, L"m_pSDK Release Failed", L"System Error", MB_OK);
}
