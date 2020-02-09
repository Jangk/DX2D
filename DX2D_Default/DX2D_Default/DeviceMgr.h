#pragma once
class DeviceMgr
{
	DECLARE_SINGLETON(DeviceMgr)

private:
	DeviceMgr();
	~DeviceMgr();
public : 
	LPDIRECT3DDEVICE9 GetDevice() const;
	LPD3DXSPRITE GetSprite() const;

public:
	HRESULT InitDevice(DISPLAY_MODE eMode);
	void Render_Begin();
	void Render_End();
	void Release();

private:
	LPDIRECT3D9			m_pSDK;
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	
	// 2d 이미지를 띄우기 위한 객체
	LPD3DXSPRITE		m_pSprite;
};

