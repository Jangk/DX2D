#pragma once
class CDeviceMgr
{
	DECLARE_SINGLETON(CDeviceMgr)

private:
	CDeviceMgr();
	~CDeviceMgr();

public:
	LPDIRECT3DDEVICE9 GetDevice() const;
	LPD3DXSPRITE GetSprite() const;
	LPD3DXFONT GetFont() const;

public:
	HRESULT InitDevice(DISPLAY_MODE eMode);
	void Render_Begin();
	void Render_End();
	void Release();

private:
	// IDirect3D9의 포인터
	// IDirect3D9: 장치를 검증하고 IDirect3DDevice9을 생성하는 COM객체.
	LPDIRECT3D9			m_pSDK;

	// IDirect3DDevice9의 포인터
	// IDirect3DDevice9: 그래픽 카드를 제어하기 위한 COM객체.
	LPDIRECT3DDEVICE9	m_pGraphicDev;

	// ID3DXSprite의 포인터
	// ID3DXSprite: DirectX에서 2D 텍스처를 손쉽게 렌더링하도록 도와주는 COM객체.
	LPD3DXSPRITE m_pSprite;

	// ID3DXFont의 포인터
	// ID3DXFont: DirectX에서 2D 폰트를 손쉽게 렌더링하도록 도와주는 COM객체.
	// 다이렉트 폰트
	LPD3DXFONT m_pFont;

	// COM (Component Object Model)
	// 부품 조립하듯 프로그래밍 하자!
	// 마이크로소프트에서 제시한 프로그래밍 모델.
};

