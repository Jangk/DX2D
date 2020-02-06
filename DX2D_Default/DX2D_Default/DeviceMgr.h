#pragma once
class DeviceMgr
{
	DECLARE_SINGLETON(DeviceMgr)

private:
	DeviceMgr();
	~DeviceMgr();

public:
	HRESULT InitDevice(DISPLAY_MODE eMode);
	void Render_Begin();
	void Render_End();
	void Release();

public:
	// TestOnly
	void InitVertex();
private:
	LPDIRECT3D9			m_pSDK;
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	// 2d 이미지를 띄우기 위한 객체
	LPD3DXSPRITE		m_pSprite;
	

	// TestOnly
	IDirect3DVertexBuffer9 *m_VB;
};

