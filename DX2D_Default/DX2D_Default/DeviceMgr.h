#pragma once
class DeviceMgr
{
	DECLARE_SINGLETON(DeviceMgr)

private:
	DeviceMgr();
	~DeviceMgr();

public:
	HRESULT InitDevice();


private:
	LPDIRECT3D9 m_pSdk;
	LPDIRECT3DDEVICE9 m_pGraphicDev;
};

