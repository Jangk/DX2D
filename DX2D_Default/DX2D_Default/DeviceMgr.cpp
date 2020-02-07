#include "pch.h"
#include "DeviceMgr.h"

IMPLEMENT_SINGLETON(DeviceMgr)

DeviceMgr::DeviceMgr()
{

}

DeviceMgr::~DeviceMgr()
{
	Release();
}

LPDIRECT3DDEVICE9 DeviceMgr::GetDevice() const
{
	return m_pGraphicDev;
}

LPD3DXSPRITE DeviceMgr::GetSprite() const
{
	return m_pSprite;
}

HRESULT DeviceMgr::InitDevice(DISPLAY_MODE eMode)
{	
	// 장치 초기화
	// 1. IDirect3D9 객체 생성
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	NULL_CHECK_MSG_RETURN(m_pSDK, L"Direct3DCreate9 Failed", E_FAIL);

	// 2. IDirect3D9 객체를 통해서 장치를 조사한다.
	D3DCAPS9 d3dcaps;		// 장치 특성 확인용
	ZeroMemory(&d3dcaps, sizeof(D3DCAPS9));

	// HAL (Hardware Abstraction Layer, 하드웨어 추상 계층)
	HRESULT hr = m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dcaps);
	FAILED_CHECK_MSG_RETURN(hr, L"GetDeviceCaps Failed", E_FAIL);

	// 2-1. 현재 장치가 버텍스 프로세싱을 지원하는지 조사.
	// 버텍스 프로세싱: 정점 변환 + 조명 연산
	DWORD vp = 0;

	// 하드웨어가 버텍스 프로세싱을 지원 하는가 확인
	if (d3dcaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// 3. IDirect3D9 객체를 통해서 IDirect3DDevice9 객체를 생성한다.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth			= WINCX;
	d3dpp.BackBufferHeight			= WINCY;
	d3dpp.BackBufferFormat			= D3DFMT_A8R8G8B8;		// 알파8비트,rgb 각각 8비트씩
	d3dpp.BackBufferCount			= 1;


	// 멀티 샘플링 사양많이 먹어서 끔
	d3dpp.MultiSampleType			= D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality		= 0;

	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD; // 스왑체인 방식(백버퍼, 프론트버퍼 교대로 )
	d3dpp.hDeviceWindow				= g_hWnd;
	d3dpp.Windowed					= eMode; // TRUE: 창모드, FALSE: 전체화면 모드
	d3dpp.EnableAutoDepthStencil	= TRUE;
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;

	/* FullScreen_RefreshRateInHz must be zero for Windowed mode */ // 전체화면이 아니면 0으로 넣을것.
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// 게임 주사율  (D3DPRESENT_RATE_DEFAULT는 모니터 주사율)
	d3dpp.PresentationInterval		 = D3DPRESENT_INTERVAL_IMMEDIATE;

	hr = m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp, &m_pGraphicDev);
	FAILED_CHECK_MSG_RETURN(hr, L"CreateDevice Failed", E_FAIL);


	// m_pSprite 생성
	hr = D3DXCreateSprite(m_pGraphicDev, &m_pSprite);
	FAILED_CHECK_MSG_RETURN(hr, L"D3DXCreateSprite Failed", E_FAIL);


	// TestOnly
	InitVertex();
	return S_OK;
}

void DeviceMgr::Render_Begin()
{
	// 화면을 지운다.
	m_pGraphicDev->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 
						 D3DCOLOR_ARGB(255,0,0,255), 1.0f, 0);


	// Render 시작
	if(SUCCEEDED(m_pGraphicDev->BeginScene()));
	{
		// 정점 버퍼를 디바이스에 연결
		m_pGraphicDev->SetStreamSource(0, m_VB, 0, sizeof(CUSTOMVERTEX));
		// FVF 설정
		m_pGraphicDev->SetFVF(D3DFVF_CUSTOMVERTEX);
		// Draw
		m_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	}
	// D3DXSPRITE_ALPHABLEND 를 넣어야 투명한 부분 이미지화 가능
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void DeviceMgr::Render_End()
{
	m_pSprite->End();

	// Render 끝
	m_pGraphicDev->EndScene();
	
	// 백 버퍼를 전면 버퍼로 (화면 출력
	m_pGraphicDev->Present(nullptr, nullptr, nullptr, nullptr);
}

void DeviceMgr::Release()
{	// 메모리 해제 순서는 생성한 순서의 역순으로 해야된다.
	// shared_ptr이라 ref count가 0이 되야 메모리 해제.
	if(m_pSprite->Release())
		::MessageBox(0, L"Sprite Error", 0, 0);
	if (m_VB->Release())
		::MessageBox(0, L"Vertex Buffer Release Error", 0, 0);
	if(m_pGraphicDev->Release())
		::MessageBox(0, L"GraphicDev Release Error", 0, 0);
	if(m_pSDK->Release())
		::MessageBox(0, L"SDK Release Error", 0, 0);
}

void DeviceMgr::InitVertex()
{
	CUSTOMVERTEX vertexes[] =
	{
		{150.f,  50.f, 0.5f, 1.0f, 0xffff0000},
		{250.f, 250.f, 0.5f, 1.0f, 0xffffff00},
		{ 50.f, 250.f, 0.5f, 1.0f, 0xff00ffff}
	};

	// D3DFVF_CUSTOMVERTEX는 struct에 내가 직접 define 정의한것.
	m_pGraphicDev->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX,
									  D3DPOOL_DEFAULT, &m_VB, NULL);

	VOID* pVertices = nullptr;
	// 정점버퍼에 lock을 걸어 포인터를 얻어옴.
	//이부분 외않대지
	m_VB->Lock(0, sizeof(vertexes), (void**)vertexes, 0);
	//memcpy_s(pVertices, sizeof(pVertices), vertexes, sizeof(vertexes));
	m_VB->Unlock();
	 
}

